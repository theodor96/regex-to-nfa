#include <QPushButton>
#include "Canvas.h"
#include "StateWidget.h"
#include "TransitionWidget.h"

Canvas::Canvas(const NFA& nfa) :
    QDialog(),
    m_closeBtn(new QPushButton(this)),
    m_refreshBtn(new QPushButton(this)),
    m_automaton(new AutomatonWidget(this))
{
    // setup the canvas
    this->setWindowTitle("NFA Computation Result");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    //this->showFullScreen();
    this->setFixedSize(1430, 850);
    
    // setup the close button
    m_closeBtn->setText("Close");
    m_closeBtn->move(1340, 810);

    // setup the refresh button
    m_refreshBtn->setText("Refresh");
    m_refreshBtn->move(1240, 810);

    // close the canvas on close button push
    this->connect(m_closeBtn, &QPushButton::clicked, this, &QWidget::close);

    // refresh the canvas on refresh btn push
    this->connect(m_refreshBtn, &QPushButton::clicked, [this]
    {
        m_automaton->refresh();
    });

    // setup the automaton widget
    setupStates(nfa.getStateList(), nfa.getFinalState());
    setupTransitions(nfa.getTransitionList());
}

void Canvas::setupStates(const NFA::StateList& stateList, NFA::State finalState) const
{
    QPoint proposedLocation(40, 30);

    // checks if current proposed location would be a good one
    auto isSuitable = [this, &proposedLocation]
    {
        for (const auto& state :  m_automaton->getStateList())
        {
            if (Utils::DistanceBetweenPoints(state->getLocation(), proposedLocation) < 120)
            {
                return false;
            }
        }

        return true;
    };

    // proposes a new location for a state
    auto findNew = [&proposedLocation]
    {
        proposedLocation = QPoint(Utils::getRandomBetween(40, 1390),
                                  Utils::getRandomBetween(40, 790));
    };

    // iterate through the list of states and create widgets for them
    // then add the widget to the automaton
    for (auto itr : stateList)
    {
        auto stateWidget = StateWidget::MakePtr(m_automaton.get());
        stateWidget->setGuid(itr + 1);

        if (itr  == finalState || stateList.size() == 1)
        {
            stateWidget->markAsFinal();
        }

        while (!isSuitable())
        {
            findNew();
        }

        stateWidget->setLocation(proposedLocation);
        m_automaton->addState(std::move(stateWidget));
    }
}

void Canvas::setupTransitions(const NFA::TransitionList& transitionList) const
{
    using TransitionEndpoints = std::pair<StateWidget::ConstShared, StateWidget::ConstShared>;

    auto findTransitionEndpoints = [this](NFA::State from, NFA::State to) -> TransitionEndpoints
    {
        TransitionEndpoints fromTo;
        for (const auto& state : m_automaton->getStateList())
        {
            if (state->getGuid() == from + 1)
            {
                fromTo.first = state;
            }
            else if (state->getGuid() == to + 1)
            {
                fromTo.second = state;
            }
        }

        return fromTo;
    };

    for (const auto& transition : transitionList)
    {
        auto fromTo = findTransitionEndpoints(transition.vertex_from, transition.vertex_to);
        auto transitionWidget = TransitionWidget::MakePtr(m_automaton.get());

        transitionWidget->setFrom(fromTo.first);
        transitionWidget->setTo(fromTo.second);
        transitionWidget->setSymbol(transition.trans_symbol);

        m_automaton->addTransition(std::move(transitionWidget));
    }
}
