#ifndef NFA_H
#define NFA_H

#include <vector>
#include <stack>
#include <type_traits>

namespace detail
{
	struct trans
	{
		int vertex_from;
		int vertex_to;
		char trans_symbol;
	};

	class NFAImpl
	{
    public:
		std::vector<int> vertex;
		std::vector<trans> transitions;
		int final_state;

        NFAImpl();
        int get_vertex_count() const;
        int get_final_state() const;

        void set_vertex(int no_vertex);
        void set_transition(int vertex_from, int vertex_to, char trans_symbol);
        void set_final_state(int fs);

        void display();
	};

    NFAImpl concat(NFAImpl a, NFAImpl b);
    NFAImpl kleene(NFAImpl a);
    NFAImpl or_selection(std::vector<NFAImpl> selections, int no_of_selections);
    NFAImpl re_to_nfa(std::string re);
}

class NFA : private detail::NFAImpl
{
public:
    using State     = int;
    using StateList = std::vector<State>;
    using TransitionList = std::vector<detail::trans>;

    const StateList& getStateList() const;
    const TransitionList getTransitionList() const;
    State getFinalState() const;
	
    static NFA FromRegex(const std::string& regex);
	
private:
    NFA();
    NFA(const NFA&) = default; // copying is necessary in NFA::FromRegex
};

#endif // NFA_H
