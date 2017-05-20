#include <QPen>
#include <QPainter>
#include <QtMath>
#include "TransitionWidget.h"
#include "AutomatonWidget.h"

constexpr TransitionWidget::QtColorStaticArray TransitionWidget::C_POSSIBLE_COLORS;

TransitionWidget::TransitionWidget(AutomatonWidget* parent) :
    QWidget(parent),
    m_automaton(parent),
    m_from(),
    m_to(),
    m_symbol(),
    m_bezierPoint(),
    m_color()
{

}

void TransitionWidget::setFrom(const StateWidget::ConstShared& from)
{
    m_from = from;
}

void TransitionWidget::setTo(const StateWidget::ConstShared& to)
{
    m_to = to;
}

void TransitionWidget::setSymbol(Symbol symbol)
{
    m_symbol = symbol;
}

const StateWidget::ConstShared& TransitionWidget::getFrom() const
{
    return m_from;
}

const StateWidget::ConstShared& TransitionWidget::getTo() const
{
    return m_to;
}

TransitionWidget::Symbol TransitionWidget::getSymbol() const
{
    return m_symbol;
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
    if (m_automaton->isUpdateNeeded() || m_bezierPoint.isNull())
    {
        QPoint rangePoint(25, 25);
        QPoint middlePoint(Utils::getMiddlePointBetween(m_from->getLocation(), m_to->getLocation()));
        m_bezierPoint = QPoint(Utils::getRandomPointBetween(middlePoint - rangePoint, middlePoint + rangePoint));

        m_color = C_POSSIBLE_COLORS[Utils::getRandomBetween(QtColorStaticArray::size_type(0), C_POSSIBLE_COLORS.size() - 1)];
    }

    QPainterPath bezierCurve;
    bezierCurve.moveTo(m_from->getLocation());
    bezierCurve.quadTo(m_bezierPoint, m_to->getLocation());

    QPen pen;
    pen.setColor(m_color);
    pen.setWidth(2);

    QPainter painter(this);
    painter.setPen(pen);
    painter.drawPath(bezierCurve);
    painter.drawText(m_bezierPoint, m_symbol);
}
