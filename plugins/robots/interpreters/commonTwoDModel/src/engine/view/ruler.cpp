#include "ruler.h"
#include "src/engine/model/constants.h"

#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsView>
#include <QtCore/QtMath>

#include <qrkernel/settingsManager.h>

#include <QtCore/QDebug>

using namespace twoDModel::view;

Ruler::Ruler(QWidget *parent)
	: QFrame(parent)
{
}

Ruler::~Ruler()
{
}

void Ruler::paintEvent(QPaintEvent *event)
{
	QFrame::paintEvent(event);
	QPainter painter(this);
	int const gridSize = qReal::SettingsManager::value("2dGridCellSize").toInt();
	QRectF const sceneRect = mView->mapToScene(mView->viewport()->geometry()).boundingRect();
	int coordinateX = (qCeil(sceneRect.left() / gridSize)) * gridSize;
	int coordinateY = (qCeil(sceneRect.top() / gridSize)) * gridSize;

	for (; coordinateX < sceneRect.right(); coordinateX += gridSize){
		painter.drawText(QPointF(mView->mapFromScene(QPointF(coordinateX, 0)).x(), 15),
			QString::number(coordinateX / pixelsInCm));
	}

	for (; coordinateY < sceneRect.bottom(); coordinateY += gridSize){
		painter.drawText(QPointF(5, mView->mapFromScene(QPointF(0, coordinateY)).y()),
			QString::number(coordinateY / pixelsInCm));
	}
}

void Ruler::setScene (QGraphicsView *scene)
{
	mView = scene;
}
