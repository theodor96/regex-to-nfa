#include <QPushButton>
#include <QtMath>
#include "Canvas.h"
#include "StateWidget.h"
#include "TransitionWidget.h"

Canvas::Canvas(const NFA& nfa) :
    QDialog(),
    m_closeBtn(new QPushButton(this)),
    m_automaton(new AutomatonWidget(this))
{
    // setup the canvas
    this->setWindowTitle("NFA Computation Result");
    this->setFixedSize(550, 580);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    
    // setup the close button
    m_closeBtn->setText("Close ");
    m_closeBtn->move(220, 540);

    // close the canvas on close button push
    this->connect(m_closeBtn, &QPushButton::clicked, this, &QWidget::close);

    // setup the automaton widget
    setupStates(nfa.getStateList(), nfa.getFinalState());
    setupTransitions(nfa.getTransitionList());
}

void Canvas::setupStates(const NFA::StateList& stateList, NFA::State finalState) const
{
    QPoint location(30, 30);
    std::vector<QPoint> locationList;

    // checks if current location would be a good one
    auto isSuitable = [&locationList, &location]
    {
        for (const auto& itr : locationList)
        {
            if (Utils::DistanceBetweenPoints(itr, location) < 70)
            {
                return false;
            }
        }

        return true;
    };

    // proposes a new location for a state
    auto findNew = [&location]
    {
        location = QPoint(Utils::getRandomBetween(40, 480),
                          Utils::getRandomBetween(40, 480));
    };

    // iterate through the list of states and create widgets for them
    // then add the widget to the automaton
    for (auto itr : stateList)
    {
        auto state = StateWidget::Ptr(new StateWidget(m_automaton.get()));
        state->setGuid(itr + 1);

        if (itr == finalState)
        {
            state->markAsFinal();
        }

        while (!isSuitable())
        {
            findNew();
        }

        locationList.push_back(location);
        state->setLocation(location);

        m_automaton->addState(std::move(state));
    }
}

void Canvas::setupTransitions(const NFA::TransitionList& transitionList) const
{
    // todo
}
