#ifndef STATE_H
#define STATE_H

#include <QtGlobal>
#include <QPoint>
#include <memory>

class State
{
public:
    typedef State                 Self;
    typedef std::unique_ptr<Self> Ptr;
    typedef std::shared_ptr<Self> SharedPtr;

    State(quint32 guid);
    State(const State&) = delete;
    State& operator=(const State&) = delete;
    State(State&&) = delete;
    State& operator=(State&&) = delete;

    bool isPainted() const;
    const QPoint& getPaintLocation() const;
    quint32 getGuid() const;

    void paintedAt(const QPoint& location);

private:
    QPoint  m_paintLocation;
    quint32 m_guid;
};

#endif // STATE_H
