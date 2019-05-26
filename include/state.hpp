#ifndef STATE_HPP
#define STATE_HPP

namespace ttc {

class State {
public:
    State() = default;
    virtual ~State() = default;
    State(const State &) = delete;
    State &operator=(State const &) = delete;
    State(State &&) = delete;
    State &operator=(State &&) = delete;

    virtual void init() = 0;
    virtual void handle_input() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(float interpolation) = 0;
    virtual void pause() {}
    virtual void resume() {}
};

} // namespace ttc

#endif // STATE_HPP
