#include "State.h"

State::State(quint32 guid) :
    m_paintLocation{},
    m_guid(guid)
{

}

quint32 State::getGuid() const
{
    return m_guid;
}

bool State::isPainted() const
{
    return !m_paintLocation.isNull();
}
const QPoint& State::getPaintLocation() const
{
    return m_paintLocation;
}
