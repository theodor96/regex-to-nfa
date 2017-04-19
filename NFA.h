#ifndef NFA_H
#define NFA_H

#include <vector>
#include <stack>
#include <type_traits>
#include "Utils.h"

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

		NFAImpl() 
		{
	
		}

		int get_vertex_count()
		{
			return vertex.size();
		}

		void set_vertex(int no_vertex)
		{
			for(int i = 0; i < no_vertex; i++)
			{
				vertex.push_back(i);
			}
		}

		void set_transition(int vertex_from, int vertex_to, char trans_symbol)
		{
			trans new_trans;
			new_trans.vertex_from = vertex_from;
			new_trans.vertex_to = vertex_to;
			new_trans.trans_symbol = trans_symbol;
			transitions.push_back(new_trans);
		}

		void set_final_state(int fs) 
		{
			final_state = fs;
		}

		int get_final_state()
		{
			return final_state;
		}

		//--------------------
		// to delete
		// ---------------------
		void display()
		{
			trans new_trans;
			std::cout<<"\n";
			for(int i = 0; i < transitions.size(); i++)
			{
				new_trans = transitions.at(i);
				std::cout<<"q"<<new_trans.vertex_from<<" --> q"<<new_trans.vertex_to<<" : Symbol - "<<new_trans.trans_symbol<<endl;
			}
			std::cout<<"\nThe final state is q"<<get_final_state()<<endl;
		}
	   //--------------------
		// to delete
		// ---------------------
	};

	NFAImpl concat(NFAImpl a, NFAImpl b)
	{
		NFAImpl result;
		result.set_vertex(a.get_vertex_count() + b.get_vertex_count());
		int i;
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

	NFAImpl kleene(NFA a)
	{
		NFAImpl result;
		int i;
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

	NFAImpl or_selection(std::vector<NFAImpl> selections, int no_of_selections)
	{
		NFAImpl result;
		int vertex_count = 2;
		int i, j;
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

	NFAImpl re_to_nfa(string re)
	{
		std::stack<char> operators;
		std::stack<NFAImpl> operands;
		char op_sym;
		int op_count;
		char cur_sym;
	
		for(string::iterator it = re.begin(); it != re.end(); ++it) {
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
					char c;
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
						selections.assign(op_count + 1, NFA());
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

		return operands.top();
	}
}

class NFA : public detail::NFAImpl
{
public:
	NO_COPY_NO_MOVE(NFA);
	
	static NFA FromRegex(const std::string& regex)
	{
		return static_cast<NFA>(detail::re_to_nfa(regex));
	}
	
private:
	NFA() : NFAImpl()
	{
		static_assert(sizeof(detail::NFAImpl) == sizeof(NFA),
					     "NFA class must not extend NFAImpl with additional data");
	}
}

#endif // NFA_H

