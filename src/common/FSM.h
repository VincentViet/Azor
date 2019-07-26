//
// Created by vice on 26/07/2019.
//

#ifndef AZOR_SRC_COMMON_FSM_H_
#define AZOR_SRC_COMMON_FSM_H_

#include <stack>
#include <functional>

class Entity;

typedef std::function<void(Entity*)> FSM_state;
// Stack-Based Finite-State Machines
class FSM
{
    std::stack<FSM_state> m_stack;

 public:
    FSM() = default;
    ~FSM() = default;

    FSM_state       popState();
    void            pushState(const FSM_state& state);
    FSM_state&      getCurrentState();
};

#endif //AZOR_SRC_COMMON_FSM_H_
