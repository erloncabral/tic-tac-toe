#include "state_machine.hpp"

namespace ttc {

StateRef const &StateMachine::get_active_state() const
{
    return _states.top();
}

void StateMachine::add_state(StateRef new_state, bool const &is_replacing)
{
    _is_adding = true;
    _is_replacing = is_replacing;

    _new_state = std::move(new_state);
}

void StateMachine::remove_state()
{
    _is_removing = true;
}

void StateMachine::process_state_changes()
{
    if (_is_removing && !_states.empty()) {
        _states.pop();
        if (!_states.empty()) {
            _states.top()->resume();
        }
        _is_removing = false;
    }

    if (_is_adding) {
        if (!_states.empty()) {
            _is_replacing ? _states.pop() : _states.top()->pause();
        }
        _states.push(std::move(_new_state));
        _states.top()->init();
        _is_adding = false;
    }
}

} // namespace ttc
