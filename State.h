#ifndef STATE_H
#define STATE_H


class State
{
public:
    typedef State Self;
    typedef std::unique_ptr<Self> Ptr;
    typedef std::shared_ptr<Self> SharedPtr;

    State();
    State(const State&) = delete;
    State& operator=(const State&) = delete;
    State(State&&) = delete;
    State& operator=(State&&) = delete;
};

#endif // STATE_H
