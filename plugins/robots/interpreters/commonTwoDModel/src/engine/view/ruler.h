#pragma once

#include <QtWidgets/QFrame>

class QGraphicsView;

namespace twoDModel {
namespace view {

class Ruler : public QFrame
{
	Q_OBJECT

public:
	explicit Ruler(QWidget *parent = 0);
	~Ruler();

	void setScene(QGraphicsView *scene);

private:
	void paintEvent(QPaintEvent *event) override;
	QGraphicsView *mView;
};

}
}
