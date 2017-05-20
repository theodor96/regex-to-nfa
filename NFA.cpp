#include <string>
#include "NFA.h"

#include <QDebug>

detail::NFAImpl::NFAImpl() :
    vertex(),
    transitions(),
    final_state()
{
}

int detail::NFAImpl::get_vertex_count() const
{
    return vertex.size();
}

void detail::NFAImpl::set_vertex(int no_vertex)
{
    for(int i = 0; i < no_vertex; i++)
    {
        vertex.push_back(i);
    }
}

void detail::NFAImpl::set_transition(int vertex_from, int vertex_to, char trans_symbol)
{
    trans new_trans;
    new_trans.vertex_from = vertex_from;
    new_trans.vertex_to = vertex_to;
    new_trans.trans_symbol = trans_symbol;
    transitions.push_back(new_trans);
}

void detail::NFAImpl::set_final_state(int fs)
{
    final_state = fs;
}

int detail::NFAImpl::get_final_state() const
{
    return final_state;
}

void detail::NFAImpl::display()
{
    for (std::size_t i = 0; i < transitions.size(); ++i)
    {
        trans new_trans = transitions.at(i);
        qDebug() << new_trans.vertex_from + 1 << " to " << new_trans.vertex_to + 1 << " via " << new_trans.trans_symbol;
    }

    qDebug() << "Initial state: 1";
    qDebug() << "Final state: " << (transitions.size() > 1 ? (get_final_state() + 1) : 1);
}

detail::NFAImpl detail::concat(NFAImpl a, NFAImpl b)
{
    NFAImpl result;
    result.set_vertex(a.get_vertex_count() + b.get_vertex_count());
    std::size_t i;
    trans new_trans;

    for(i = 0; i < a.transitions.size(); i++)
    {
        new_trans = a.transitions.at(i);
        result.set_transition(new_trans.vertex_from, new_trans.vertex_to, new_trans.trans_symbol);
    }

    result.set_transition(a.get_final_state(), a.get_vertex_count(), '^');

    for(i = 0; i < b.transitions.size(); i++)
    {
        new_trans = b.transitions.at(i);
        result.set_transition(new_trans.vertex_from + a.get_vertex_count(),
                               new_trans.vertex_to + a.get_vertex_count(),
                               new_trans.trans_symbol);
    }

    result.set_final_state(a.get_vertex_count() + b.get_vertex_count() - 1);

    return result;
}

detail::NFAImpl detail::kleene(NFAImpl a)
{
    NFAImpl result;
    std::size_t i;
    trans new_trans;

    result.set_vertex(a.get_vertex_count() + 2);
    result.set_transition(0, 1, '^');

    for(i = 0; i < a.transitions.size(); i++)
    {
        new_trans = a.transitions.at(i);
        result.set_transition(new_trans.vertex_from + 1, new_trans.vertex_to + 1, new_trans.trans_symbol);
    }

    result.set_transition(a.get_vertex_count(), a.get_vertex_count() + 1, '^');
    result.set_transition(a.get_vertex_count(), 1, '^');
    result.set_transition(0, a.get_vertex_count() + 1, '^');

    result.set_final_state(a.get_vertex_count() + 1);

    return result;
}

detail::NFAImpl detail::or_selection(std::vector<NFAImpl> selections, int no_of_selections)
{
    NFAImpl result;
    int vertex_count = 2;
    int i;
    std::size_t j;
    NFAImpl med;
    trans new_trans;

    for(i = 0; i < no_of_selections; i++)
    {
        vertex_count += selections.at(i).get_vertex_count();
    }

    result.set_vertex(vertex_count);

    int adder_track = 1;

    for(i = 0; i < no_of_selections; i++)
    {
        result.set_transition(0, adder_track, '^');
        med = selections.at(i);
        for(j = 0; j < med.transitions.size(); j++)
        {
            new_trans = med.transitions.at(j);
            result.set_transition(new_trans.vertex_from + adder_track, new_trans.vertex_to + adder_track, new_trans.trans_symbol);
        }
        adder_track += med.get_vertex_count();

        result.set_transition(adder_track - 1, vertex_count - 1, '^');
    }

    result.set_final_state(vertex_count - 1);

    return result;
}

detail::NFAImpl detail::re_to_nfa(std::string re)
{
    std::stack<char> operators;
    std::stack<NFAImpl> operands;
    char op_sym;
    int op_count;
    char cur_sym;

    for(std::string::iterator it = re.begin(); it != re.end(); ++it) {
        cur_sym = *it;
        if(cur_sym != '(' && cur_sym != ')' && cur_sym != '*' && cur_sym != '|' && cur_sym != '.') {
            NFAImpl new_sym;
            new_sym.set_vertex(2);
            new_sym.set_transition(0, 1, cur_sym);
            new_sym.set_final_state(1);
            operands.push(new_sym);
        } else {
            if(cur_sym == '*') {
                NFAImpl star_sym = operands.top();
                operands.pop();
                operands.push(kleene(star_sym));
            } else if(cur_sym == '.') {
                operators.push(cur_sym);
            } else if(cur_sym == '|') {
                operators.push(cur_sym);
            } else if(cur_sym == '(') {
                operators.push(cur_sym);
            } else {
                op_count = 0;
                op_sym = operators.top();
                if(op_sym == '(') continue;
                do {
                    operators.pop();
                    op_count++;
                } while(operators.top() != '(');
                operators.pop();
                NFAImpl op1;
                NFAImpl op2;
                std::vector<NFAImpl> selections;
                if(op_sym == '.') {
                    for(int i = 0; i < op_count; i++) {
                        op2 = operands.top();
                        operands.pop();
                        op1 = operands.top();
                        operands.pop();
                        operands.push(concat(op1, op2));
                    }
                } else if(op_sym == '|'){
                    selections.assign(op_count + 1, NFAImpl());
                    int tracker = op_count;
                    for(int i = 0; i < op_count + 1; i++) {
                        selections.at(tracker) = operands.top();
                        tracker--;
                        operands.pop();
                    }
                    operands.push(or_selection(selections, op_count+1));
                } else
                {

                }
            }
        }
    }

    if (operands.empty())
    {
        NFAImpl result;
        result.set_vertex(1);
        result.set_final_state(1);

        return result;
    }

    return operands.top();
}

const NFA::StateList& NFA::getStateList() const
{
    return vertex;
}

const NFA::TransitionList NFA::getTransitionList() const
{
    return transitions;
}

NFA::State NFA::getFinalState() const
{
    return final_state;
}

NFA NFA::FromRegex(const std::string& regex)
{
    auto nfaImpl = detail::re_to_nfa(regex);
    nfaImpl.display();
    auto nfa = static_cast<NFA*>(&nfaImpl);
    return *nfa;
}

NFA::NFA() : NFAImpl()
{
    static_assert(sizeof(detail::NFAImpl) == sizeof(NFA),
                  "NFA class must not extend NFAImpl with any additional data");
}
