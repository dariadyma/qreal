#pragma once

#include <QtCore/QObject>

#include <qrkernel/ids.h>

#include <qrgui/mainwindow/projectManager/projectManagementInterface.h>
#include <qrgui/mainwindow/mainWindowInterpretersInterface.h>
#include <qrgui/toolPluginInterface/usedInterfaces/graphicalModelAssistInterface.h>
#include <qrgui/toolPluginInterface/usedInterfaces/logicalModelAssistInterface.h>

#include <interpreterBase/blocks/blockParserInterface.h>

namespace interpreterCore {
namespace interpreter {

class InterpreterInterface : public QObject
{
	Q_OBJECT

public:
	virtual ~InterpreterInterface() {}

	virtual qReal::IdList providedBlocks() const = 0;

	// TODO: Unneeded.
	virtual interpreterBase::blocks::BlockParserInterface &parser() const = 0;

public slots:
	virtual void interpret() = 0;
};

}
}