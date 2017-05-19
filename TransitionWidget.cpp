#include <QPen>
#include <QPainter>
#include <QtMath>
#include "TransitionWidget.h"
#include "AutomatonWidget.h"

TransitionWidget::TransitionWidget(AutomatonWidget* parent) :
    QWidget(parent),
    m_parent(parent)
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
    static bool alreadyPainted = false;

    if (!alreadyPainted || m_parent.lock()->isUpdateNeeded())
    {
        alreadyPainted = true;

        QPoint rangePoint(30, 30);
        QPoint middlePoint(Utils::getMiddlePointBetween(m_from->getLocation(), m_to->getLocation()));
        QPoint bezierPoint(Utils::getRandomPointBetween(middlePoint - rangePoint, middlePoint + rangePoint));

        QPainterPath bezierCurve;
        bezierCurve.moveTo(m_from->getLocation());
        bezierCurve.quadTo(bezierPoint, m_to->getLocation());

        QPen pen;
        pen.setColor(Qt::green);
        pen.setWidth(2);

        QPainter painter(this);
        painter.setPen(pen);
        painter.drawPath(bezierCurve);

        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawText(bezierPoint, m_symbol);
    }
}
