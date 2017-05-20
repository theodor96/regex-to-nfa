#include <QPainter>
#include <QFont>
#include "AutomatonWidget.h"
#include "Canvas.h"

AutomatonWidget::AutomatonWidget(Canvas* canvas) :
    QWidget(canvas),
    m_isUpdateNeeded(false),
    m_stateList(),
    m_transitionList()
{

}

void AutomatonWidget::refresh()
{
    m_isUpdateNeeded = true;

    for (const auto& stateItr : m_stateList)
    {
        stateItr->repaint();
    }

    for (const auto& transitionItr : m_transitionList)
    {
        transitionItr->repaint();
    }

    m_isUpdateNeeded = false;
}

void AutomatonWidget::addState(StateWidget::Ptr state)
{
    m_stateList.push_back(std::move(state));
}

void AutomatonWidget::addTransition(TransitionWidget::Ptr transition)
{
    m_transitionList.push_back(std::move(transition));
}

bool AutomatonWidget::isUpdateNeeded() const
{
    return m_isUpdateNeeded;
}

const AutomatonWidget::StateList& AutomatonWidget::getStateList() const
{
    return m_stateList;
}

const AutomatonWidget::TransitionList& AutomatonWidget::getTransitionList() const
{
    return m_transitionList;
}

QSize AutomatonWidget::sizeHint() const
{
    return
    {
        1450,
        800
    };
}

void AutomatonWidget::paintEvent(QPaintEvent*)
{
    QFont font;
    font.setPixelSize(25);

    QPainter painter(this);
    painter.setFont(font);
    painter.drawText(8, 33, QString::fromUtf8("\u2192"));
}
