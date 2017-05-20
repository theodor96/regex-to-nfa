#include <QPen>
#include <QPainter>
#include "StateWidget.h"
#include "AutomatonWidget.h"

StateWidget::StateWidget(AutomatonWidget* parent) :
    QWidget(parent),
    m_location(),
    m_guid(InvalidGuid),
    m_isFinal(false)
{

}

StateWidget::Guid StateWidget::getGuid() const
{
    return m_guid;
}

const QPoint& StateWidget::getLocation() const
{
    return m_location;
}

bool StateWidget::isFinal() const
{
    return m_isFinal;
}

void StateWidget::setGuid(Guid guid)
{
    m_guid = guid;
}

void StateWidget::setLocation(const QPoint& location)
{
    m_location = location;
}

void StateWidget::markAsFinal()
{
    m_isFinal = true;
}

QSize StateWidget::sizeHint() const
{
    return
    {
        530,
        530
    };
}

void StateWidget::paintEvent(QPaintEvent*)
{
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);

    QPainter painter(this);
    painter.setPen(pen);
    painter.drawText(m_location, QString::number(m_guid));

    QPoint ellipseLocation;
    ellipseLocation.setY(m_location.y() - 5);
    if (m_guid < 10)
    {
        ellipseLocation.setX(m_location.x() + 4);
    }
    else if (m_guid < 100)
    {
        ellipseLocation.setX(m_location.x() + 8);
    }
    else if (m_guid < 1000)
    {
        ellipseLocation.setX(m_location.x() + 12);
    }
    else
    {
        ellipseLocation.setX(m_location.x() + 16);
    }

    if (m_isFinal)
    {
        pen.setWidth(4);
        painter.setPen(pen);
    }

    // x-wise radius should be dynamic depending on the width of the guid
    painter.drawEllipse(ellipseLocation, m_guid < 10 ? 14 : m_guid < 100 ? 17 : m_guid < 1000 ? 20 : 23, 14);
}
