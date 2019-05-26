#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <memory>
#include <stack>

#include "state.hpp"

namespace ttc {

using StateRef = std::unique_ptr<State>;

class StateMachine
{
private:
    std::stack<StateRef> _states;
    StateRef _new_state;
    bool _is_removing{};
    bool _is_adding{};
    bool _is_replacing{};

public:
    StateRef const &get_active_state() const;

    void add_state(StateRef new_state, bool const &is_replacing = true);
    void remove_state();
    void process_state_changes();
};

} // namespace ttc

#endif // STATE_MACHINE_HPP
