#include "State.h"

#include <QPen>
#include <QPainter>

State::State(QWidget* parent, quint16 rx, quint16 ry) :
    QWidget(parent),
    m_rx(rx),
    m_ry(ry)
{

}

void State::paintEvent(QPaintEvent*)
{
    QPen pen;
    pen.setColor(QColor(Qt::red));
    pen.setWidth(1);

    QPainter painter(this);

    painter.setPen(pen);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawEllipse(QPoint(40, 40), 20, 20);

    painter.drawEllipse(QPoint(80, 80), 20, 20);

    painter.drawEllipse(QPoint(120, 190), 20, 20);

    painter.drawLines(QVector<QPoint>{ {40, 40}, {80, 80}, {80, 80}, {120, 190} });

    painter.drawText(60, 60, "dwed");
}
