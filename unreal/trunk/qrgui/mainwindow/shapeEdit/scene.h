#pragma once

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "arch.h"

class Scene : public QGraphicsScene
{
	Q_OBJECT
public:
	Scene(QObject *parent = 0);
private slots:
	void drawLine();
	void drawEllipse();
	void drawArc();
	void clearScene();
private:
	bool mWaitLine;
	bool mWaitEllipse;
	bool mWaitArch;
	int mCount;
	QGraphicsLineItem *mLine;
	QGraphicsEllipseItem *mEllipse;
	Arch *mArch;
	qreal mX1;
	qreal mX2;
	qreal mY1;
	qreal mY2;

	void setX1andY1(QGraphicsSceneMouseEvent *event);
	void setX2andY2(QGraphicsSceneMouseEvent *event);
	void reshapeLine( QGraphicsSceneMouseEvent *event);
	void reshapeEllipse( QGraphicsSceneMouseEvent *event);

	virtual void mousePressEvent( QGraphicsSceneMouseEvent *event);
	virtual void mouseMoveEvent( QGraphicsSceneMouseEvent *event);
	virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
};