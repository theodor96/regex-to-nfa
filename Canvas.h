#ifndef CANVAS_H
#define CANVAS_H

#include <QDialog>
#include "AutomatonWidget.h"
#include "NFA.h"
#include "Utils.h"

class QPushButton;

class Canvas : public QDialog
{
public:
    SMART_ALIASES(Canvas);
    NO_COPY_NO_MOVE(Canvas);

    Canvas(const NFA&);

private:
    QPushButton*         m_closeBtn;
    QPushButton*         m_refreshBtn;
    AutomatonWidget::Ptr m_automaton;

    void setupStates(const NFA::StateList& stateList, NFA::State finalState) const;
    void setupTransitions(const NFA::TransitionList& transitionList) const;
};

#endif // CANVAS_H
