#pragma once

#include <QtWidgets/QGraphicsView>
#include <QtGui/QKeyEvent>

#include "../utilsDeclSpec.h"

namespace graphicsUtils
{

class QRUTILS_EXPORT AbstractView : public QGraphicsView
{
	Q_OBJECT
public:
	AbstractView(QWidget *parent = 0);

public slots:
	void zoomIn();
	void zoomOut();

signals:
	void deleteItem();
	void zoomChanged();
	void contentsRectChanged();

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
	void scrollContentsBy(int dx, int dy) override;
};
}
