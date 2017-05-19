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
    using Self        = AutomatonWidget;
    using Ptr         = Utils::Ptr<Self>;
    using Shared      = Utils::SharedPtr<Self>;
    using ConstPtr    = Utils::Ptr<const Self>;
    using ConstShared = Utils::SharedPtr<const Self>;

    AutomatonWidget(Canvas* canvas);
    NO_COPY_NO_MOVE(AutomatonWidget);

    using StateList      = std::vector<StateWidget::Shared>;
    using TransitionList = std::vector<TransitionWidget::Shared>;

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
