#include <QPen>
#include <QPainter>
#include "TransitionWidget.h"
#include "AutomatonWidget.h"

TransitionWidget::TransitionWidget(AutomatonWidget* parent) :
    QWidget(parent)
{

}

QSize TransitionWidget::sizeHint() const
{
    return
    {
        530,
        530
    };
}

void TransitionWidget::paintEvent(QPaintEvent*)
{
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(2);

    QPainter painter(this);
    painter.setPen(pen);

    painter.drawArc(30, 30, 10, 10, 3, 5);
}
