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
    using Self   = AutomatonWidget;
    using Ptr    = Utils::Ptr<Self>;
    using Shared = Utils::SharedPtr<Self>;

    AutomatonWidget(Canvas* canvas);
    NO_COPY_NO_MOVE(AutomatonWidget);

    using StateList      = std::vector<StateWidget::Ptr>;
    using TransitionList = std::vector<TransitionWidget::Ptr>;

    void addState(StateWidget::Ptr state);
    void addTransition(TransitionWidget::Ptr transition);

    const StateList& getStateList() const;
    const TransitionList& getTransitionList() const;

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    StateList      m_stateList;
    TransitionList m_transitionList;
};

#endif // AUTOMATONWIDGET_H
