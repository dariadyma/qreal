#include "model.h"
#include <QtCore/QDebug>
#include <QtGui/QPolygon>

using namespace qReal;
using namespace model;

Model::Model(EditorManager const &editorManager)
		: mEditorManager(editorManager)
{
	mClient = new client::Client();
	rootItem = new ModelTreeItem(ROOT_ID, NULL);
	init();
}

Model::~Model()
{
	cleanupTree(rootItem);
	treeItems.clear();
	delete mClient;
}

void Model::init()
{
	treeItems.insert(ROOT_ID, rootItem);
	mClient->setProperty(ROOT_ID, "Name", ROOT_ID.toString());
	loadSubtreeFromClient(rootItem);
}

Qt::ItemFlags Model::flags( const QModelIndex &index ) const
{
	if (index.isValid()) {
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled
			| Qt::ItemIsDropEnabled | Qt::ItemIsEnabled;
	} else {
		return Qt::NoItemFlags;
	}
}

QVariant Model::data(QModelIndex const &index, int role) const
{
	if (index.isValid()) {
		ModelTreeItem *item = static_cast<ModelTreeItem*>(index.internalPointer());
		Q_ASSERT(item);
		switch (role) {
			case Qt::DisplayRole:
			case Qt::EditRole:
				return mClient->property(item->id(), "Name");
			case roles::idRole: {
				return item->id().toVariant();
			}
			case roles::positionRole:
				return mClient->property(item->id(), positionPropertyName(item));
			case roles::fromRole:
				return mClient->property(item->id(), "from");
			case roles::toRole:
				return mClient->property(item->id(), "to");
			case roles::fromPortRole:
				return mClient->property(item->id(), "fromPort");
			case roles::toPortRole:
				return mClient->property(item->id(), "toPort");
			case roles::configurationRole:
				return mClient->property(item->id(), configurationPropertyName(item));
		}
		if (role >= roles::customPropertiesBeginRole) {
			QString selectedProperty = findPropertyName(item->id(), role);
			return mClient->property(item->id(), selectedProperty);
		}
		Q_ASSERT(role < Qt::UserRole);
		return QVariant();
	} else {
		return QVariant();
	}
}

bool Model::setData(QModelIndex const &index, QVariant const &value, int role)
{
	if (index.isValid()) {
		ModelTreeItem *item = static_cast<ModelTreeItem*>(index.internalPointer());
		switch (role) {
			case Qt::DisplayRole:
			case Qt::EditRole:
				mClient->setProperty(item->id(), "Name", value);
				return true;
			case roles::positionRole:
				mClient->setProperty(item->id(), positionPropertyName(item), value);
				return true;
			case roles::configurationRole:
				mClient->setProperty(item->id(), configurationPropertyName(item), value);
				return true;
			case roles::fromRole:
				mClient->setProperty(item->id(), "from", value);
				return true;
			case roles::toRole:
				mClient->setProperty(item->id(), "to", value);
				return true;
			case roles::fromPortRole:
				mClient->setProperty(item->id(), "fromPort", value);
				return true;
			case roles::toPortRole:
				mClient->setProperty(item->id(), "toPort", value);
				return true;
		}
		if (role >= roles::customPropertiesBeginRole) {
			QString selectedProperty = findPropertyName(item->id(), role);
			mClient->setProperty(item->id(), selectedProperty, value);
			return true;
		}
		Q_ASSERT(role < Qt::UserRole);
		return false;
	} else {
		return false;
	}
}

PropertyName Model::findPropertyName(Id const &id, int const role) const
{
	// В случае свойства, описанного в самом элементе, роль - просто
	// порядковый номер свойства в списке свойств. Этого соглашения
	// надо всюду придерживаться, а то роли "поедут".
	QStringList properties = mEditorManager.getPropertyNames(id.type());
	Q_ASSERT(role - roles::customPropertiesBeginRole < properties.count());
	return properties[role - roles::customPropertiesBeginRole];
}

QVariant Model::headerData( int section, Qt::Orientation orientation, int role ) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole && section == 0 ) {
		return QVariant("Name");
	} else {
		return QVariant();
	}
}

int Model::rowCount( const QModelIndex &parent ) const
{
	ModelTreeItem *parentItem;
	if (parent.isValid()) {
		parentItem = static_cast<ModelTreeItem*>(parent.internalPointer());
	} else {
		parentItem = rootItem;
	}
	return parentItem->children().size();
}

int Model::columnCount( const QModelIndex &parent ) const
{
	Q_UNUSED(parent)
	return 1;
}

bool Model::removeRows( int row, int count, const QModelIndex &parent )
{
	if (parent.isValid()) {
		ModelTreeItem *parentItem = static_cast<ModelTreeItem*>(parent.internalPointer());
		if (parentItem->children().size() < row + count) {
			return false;
		} else {
			for (int i = row; i < row + count; i++) {
				removeModelItems(parentItem->children().at(i));
			}
			return true;
		}
	} else {
		return false;
	}
}

PropertyName Model::pathToItem(ModelTreeItem const *item) const
{
	if (item != rootItem) {
		PropertyName path;
		do {
			item = item->parent();
			path = item->id().toString() + PATH_DIVIDER + path;
		} while (item!=rootItem);
		return path;
	}
	else
		return ROOT_ID.toString();
}

void Model::removeConfigurationInClient( ModelTreeItem *item )
{
	mClient->removeProperty(item->id(), positionPropertyName(item));
	mClient->removeProperty(item->id(), configurationPropertyName(item));
}

QModelIndex Model::index( ModelTreeItem *item )
{
	if (item!=rootItem) {
		return createIndex(item->row(),0,item);
	} else {
		return QModelIndex();
	}
}

void Model::removeModelItems( ModelTreeItem *root )
{
	foreach (ModelTreeItem *child, root->children()) {
		removeModelItems(child);
		int childRow = child->row();
		beginRemoveRows(index(root),childRow,childRow);
		removeConfigurationInClient(child);
		child->parent()->removeChild(child);
		treeItems.remove(child->id(),child);
		if (treeItems.count(child->id())==0) {
			mClient->removeChild(root->id(),child->id());
		}
		delete child;
		endRemoveRows();
	}
}

QModelIndex Model::index( int row, int column, const QModelIndex &parent ) const
{
	ModelTreeItem *parentItem;
	if (parent.isValid()) {
		parentItem = static_cast<ModelTreeItem*>(parent.internalPointer());
	} else {
		parentItem = rootItem;
	}
	if (parentItem->children().size()<=row) {
		return QModelIndex();
	}
	ModelTreeItem *item = parentItem->children().at(row);
	return createIndex(row,column,item);
}

QModelIndex Model::parent( const QModelIndex &index ) const
{
	if (index.isValid()) {
		ModelTreeItem *item = static_cast<ModelTreeItem*>(index.internalPointer());
		ModelTreeItem *parentItem = item->parent();
		if ((parentItem==rootItem)||(parentItem==NULL)) {
			return QModelIndex();
		} else{
			return createIndex(parentItem->row(),0,parentItem);
		}
	} else {
		return QModelIndex();
	}
}

Qt::DropActions Model::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction | Qt::LinkAction;
}

QStringList Model::mimeTypes() const
{
	QStringList types;
	types.append(DEFAULT_MIME_TYPE);
	return types;
}

QMimeData* Model::mimeData( const QModelIndexList &indexes ) const
{
	QByteArray data;
	QDataStream stream(&data, QIODevice::WriteOnly);
	foreach (QModelIndex index, indexes) {
		if (index.isValid()) {
			ModelTreeItem *item = static_cast<ModelTreeItem*>(index.internalPointer());
			stream << item->id().toString();
			stream << pathToItem(item);
			stream << mClient->property(item->id(), "Name");
			stream << mClient->property(item->id(), positionPropertyName(item)).toPointF();
		} else {
			stream << ROOT_ID.toString();
			stream << QString();
			stream << ROOT_ID.toString();
			stream << QPointF();
		}
	}
	QMimeData *mimeData = new QMimeData();
	mimeData->setData(DEFAULT_MIME_TYPE, data);
	return mimeData;
}

bool Model::dropMimeData( const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent )
{
	Q_UNUSED(row)
	Q_UNUSED(column)
	if (action == Qt::IgnoreAction) {
		return true;
	} else {
		ModelTreeItem *parentItem;
		if (parent.isValid()) {
			parentItem = static_cast<ModelTreeItem*>(parent.internalPointer());
		} else {
			parentItem = rootItem;
		}
		QByteArray dragData = data->data(DEFAULT_MIME_TYPE);
		QDataStream stream(&dragData, QIODevice::ReadOnly);
		QString idString;
		PropertyName pathToItem;
		QString name;
		QPointF position;
		stream >> idString;
		stream >> pathToItem;
		stream >> name;
		stream >> position;
		IdType id = Id::loadFromString(idString);
		Q_ASSERT(id.idSize() == 4);  // Бросать в модель мы можем только конкретные элементы.

		return addElementToModel(parentItem,id,pathToItem,name,position,action) != NULL;
	}
}

ModelTreeItem *Model::addElementToModel( ModelTreeItem *parentItem, const IdType &id,
		const PropertyName &oldPathToItem, const QString &name, const QPointF &position, Qt::DropAction action )
{
	Q_UNUSED(oldPathToItem)
	Q_UNUSED(action)

	int newRow = parentItem->children().size();
	beginInsertRows(index(parentItem),newRow,newRow);
		ModelTreeItem *item = new ModelTreeItem(id, parentItem);
		parentItem->addChild(item);
		treeItems.insert(id,item);
		mClient->addChild(parentItem->id(),id);
		mClient->setProperty(id, "Name", name);
		mClient->setProperty(id, "from", ROOT_ID.toVariant());
		mClient->setProperty(id, "to", ROOT_ID.toVariant());
		mClient->setProperty(id, "fromPort", 0.0);
		mClient->setProperty(id, "toPort", 0.0);
		mClient->setProperty(id, positionPropertyName(item), position);
		mClient->setProperty(id, configurationPropertyName(item), QVariant(QPolygon()));

		QStringList properties = mEditorManager.getPropertyNames(id.type());
		foreach (QString property, properties) {
			// Здесь должна быть инициализация значениями по умолчанию
			// (а ещё лучше, если не здесь). Считать этот код временным хаком,
			// пока нет системы типов.
			mClient->setProperty(id, property, "");
		}
	endInsertRows();
	return item;
}

void Model::loadSubtreeFromClient(ModelTreeItem * const parent)
{
	foreach (IdType childId, mClient->children(parent->id())) {
		PropertyName path = pathToItem(parent);
		ModelTreeItem *child = loadElement(parent, childId);
		loadSubtreeFromClient(child);
	}
}

ModelTreeItem *Model::loadElement(ModelTreeItem *parentItem, const IdType &id)
{
	int newRow = parentItem->children().size();
	beginInsertRows(index(parentItem), newRow, newRow);
		ModelTreeItem *item = new ModelTreeItem(id, parentItem);
		parentItem->addChild(item);
		treeItems.insert(id, item);
	endInsertRows();
	return item;
}

QPersistentModelIndex Model::rootIndex()
{
	return index(rootItem);
}

PropertyName Model::positionPropertyName(ModelTreeItem const *item) const
{
	return "position + " + pathToItem(item);
}

PropertyName Model::configurationPropertyName(ModelTreeItem const *item) const
{
	return "configuration + " + pathToItem(item);
}

void Model::exterminate()
{
	mClient->exterminate();
	cleanupTree(rootItem);
	treeItems.clear();
	init();
}

void Model::cleanupTree(ModelTreeItem *root)
{
	foreach (ModelTreeItem *childItem, root->children())
	{
		cleanupTree(childItem);
		delete childItem;
	}
	root->clearChildren();
}
