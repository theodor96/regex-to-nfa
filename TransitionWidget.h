#ifndef TRANSITIONWIDGET_H
#define TRANSITIONWIDGET_H

#include <QWidget>
#include <QSize>
#include <array>
#include "StateWidget.h"
#include "Utils.h"

class AutomatonWidget;
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
    AutomatonWidget*         m_automaton;
    StateWidget::ConstShared m_from;
    StateWidget::ConstShared m_to;
    Symbol                   m_symbol;
    QPoint                   m_bezierPoint;
    Qt::GlobalColor          m_color;

    using QtColorStaticArray = std::array<Qt::GlobalColor, 6>;

    static constexpr QtColorStaticArray C_POSSIBLE_COLORS
    {
        {
            Qt::gray,
            Qt::red,
            Qt::green,
            Qt::blue,
            Qt::magenta,
            Qt::black
        }
    };
};

#endif // TRANSITIONWIDGET_H
