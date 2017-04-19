#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <QWidget>
#include <unordered_map>
#include "State.h"

class Canvas;

// hiding some implementation details
namespace detail
{
    typedef char                                       Symbol;
    typedef std::vector<State::Ptr>                    StateList;
    typedef std::pair<State*, Symbol>                  TransSource;
    typedef State*                                     TransDest;
    typedef std::unordered_map<TransSource, TransDest> TransitionMap;
}

// lets specialize std::hash and std::equal_to for our new TransSource type used as Key in std::unordered_map
namespace std
{
    template<>
    struct hash<detail::TransSource>
    {
        size_t operator()(const detail::TransSource& source) const
        {
            return hash<detail::TransSource::first_type>{}(source.first) ^ (hash<detail::TransSource::second_type>{}(source.second) << 1);
        }
    };

    template<>
    struct equal_to<detail::TransSource>
    {
      bool operator()(const detail::TransSource& lhs, const detail::TransSource& rhs) const
      {
        return lhs.first == rhs.first && lhs.second == rhs.second;
      }
    };
}

class Automaton : public QWidget
{
public:
    typedef Automaton             Self;
    typedef std::unique_ptr<Self> Ptr;
    typedef std::shared_ptr<Self> SharedPtr;

    using   Symbol = detail::Symbol;

    Automaton(Canvas* canvas);
    Automaton(const Automaton&) = delete;
    Automaton& operator=(const Automaton&) = delete;
    Automaton(Automaton&&) = delete;
    Automaton& operator=(Automaton&&) = delete;

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    bool isPaintLocationSuitable(const QPoint& location) const;
    QPoint getRandomPaintLocation() const;
    QPoint findNewStatePaintLocation() const;

    detail::StateList     m_states;
    detail::TransitionMap m_transitions;
};

#endif // AUTOMATON_H

