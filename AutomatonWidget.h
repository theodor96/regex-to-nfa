#ifndef AUTOMATONWIDGET_H
#define AUTOMATONWIDGET_H

#include <QWidget>
#include <QSize>
#include "StateWidget.h"
#include "TransitionWidget.h"
#include "Utils.h"

class Canvas;
class QPaintEvent;

class AutomatonWidget : public QWidget
{
public:
    SMART_ALIASES(AutomatonWidget);
    NO_COPY_NO_MOVE(AutomatonWidget);

    using StateList      = std::vector<StateWidget::Shared>;
    using TransitionList = std::vector<TransitionWidget::Shared>;

    AutomatonWidget(Canvas* canvas);

    void refresh();
    void addState(StateWidget::Ptr state);
    void addTransition(TransitionWidget::Ptr transition);

    bool isUpdateNeeded() const;
    const StateList& getStateList() const;
    const TransitionList& getTransitionList() const;

    QSize sizeHint() const override;

private:
    bool           m_isUpdateNeeded;
    StateList      m_stateList;
    TransitionList m_transitionList;
};

#endif // AUTOMATONWIDGET_H
