#ifndef TRANSITIONWIDGET_H
#define TRANSITIONWIDGET_H

#include <QWidget>
#include <QSize>
#include "StateWidget.h"
#include "Utils.h"

class AutomatonWidget;
class StateWidget;
class QPaintEvent;

class TransitionWidget : public QWidget
{
public:
    using Self        = TransitionWidget;
    using Ptr         = Utils::Ptr<Self>;
    using Shared      = Utils::SharedPtr<Self>;
    using ConstPtr    = Utils::Ptr<const Self>;
    using ConstShared = Utils::SharedPtr<const Self>;

    TransitionWidget(AutomatonWidget* parent);
    NO_COPY_NO_MOVE(TransitionWidget);

    using Symbol = QChar;

    void setFrom(const StateWidget::ConstShared& from);
    void setTo(const StateWidget::ConstShared& to);
    void setSymbol(Symbol symbol);

    const StateWidget::ConstShared& getFrom() const;
    const StateWidget::ConstShared& getTo() const;
    Symbol getSymbol() const;

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    StateWidget::ConstShared m_from;
    StateWidget::ConstShared m_to;
    Symbol m_symbol;
};

#endif // TRANSITIONWIDGET_H
