#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <QWidget>
#include "State.h"

class Canvas;

class Automaton : public QWidget
{
public:
    typedef Automaton Self;
    typedef std::unique_ptr<Self> Ptr;
    typedef std::shared_ptr<Self> SharedPtr;

    Automaton(Canvas* canvas);
    Automaton(const Automaton&) = delete;
    Automaton& operator=(const Automaton&) = delete;
    Automaton(Automaton&&) = delete;
    Automaton& operator=(Automaton&&) = delete;

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    typedef std::vector<State::Ptr> StateList;

    StateList m_states;
};

#endif // AUTOMATON_H
