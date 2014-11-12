#include "abstractItemView.h"
using namespace graphicsUtils;

AbstractView::AbstractView(QWidget * parent) : QGraphicsView(parent)
{
}

void AbstractView::zoomIn()
{
	scale(1.5,1.5);
	emit zoomChanged();
}

void AbstractView::zoomOut()
{
	scale(0.66,0.66);
	emit zoomChanged();
}

void AbstractView::wheelEvent(QWheelEvent *event)
{
	QGraphicsView::wheelEvent(event);
	if (event->buttons() == Qt::MidButton) {
		if (event->delta() >= 0)
			zoomOut();
		else
			zoomIn();
	}
}

void AbstractView::scrollContentsBy(int dx, int dy)
{
	QGraphicsView::scrollContentsBy(dx, dy);
	emit contentsRectChanged();
}

void AbstractView::keyPressEvent(QKeyEvent *event)
{
	QGraphicsView::keyPressEvent(event);
	if (event->matches(QKeySequence::Delete))
		emit deleteItem();
}
