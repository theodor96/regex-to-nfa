#include <QPen>
#include <QPainter>
#include "Automaton.h"

Automaton::Automaton(Canvas* canvas) :
    QWidget(canvas),
    m_states()
{

}

QSize Automaton::sizeHint() const
{
    return
    {
        500,
        500
    };
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
