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
    using Self   = Canvas;
    using Ptr    = Utils::Ptr<Self>;
    using Shared = Utils::SharedPtr<Self>;
    
    Canvas(const NFA&);
    NO_COPY_NO_MOVE(Canvas);
    
private:
    QPushButton*         m_closeBtn;
    AutomatonWidget::Ptr m_automaton;

    void setupStates(const NFA::StateList& stateList, NFA::State finalState) const;
    void setupTransitions(const NFA::TransitionList& transitionList) const;
};

#endif // CANVAS_H

