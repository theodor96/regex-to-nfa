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
    SMART_ALIASES(TransitionWidget);
    NO_COPY_NO_MOVE(TransitionWidget);

    using Symbol = QChar;

    TransitionWidget(AutomatonWidget* parent);

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

    AutomatonWidget*         m_automaton;
    StateWidget::ConstShared m_from;
    StateWidget::ConstShared m_to;
    Symbol                   m_symbol;
    QPoint                   m_bezierPoint;
    Qt::GlobalColor          m_color;
};

#endif // TRANSITIONWIDGET_H
