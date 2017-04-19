#ifndef STATE_H
#define STATE_H

#include <QtGlobal>
#include <QPoint>
#include "Utils.h"

class State
{
public:
    using Self   = State;
    using Ptr    = Utils::Ptr<Self>;
    using Shared = Utils::SharedPtr<Self>;
    
    State();
    NO_COPY_NO_MOVE(State);

    bool isPainted() const;
    const QPoint& getPaintLocation() const;
    quint32 getGuid() const;

    void paintedAt(const QPoint& location);

private:
    QPoint  m_paintLocation;
    quint32 m_guid;
};

#endif // STATE_H

