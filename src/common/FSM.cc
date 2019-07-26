//
// Created by vice on 26/07/2019.
//

#include "FSM.h"
FSM_state FSM::popState()
{
    auto state = m_stack.top();
    m_stack.pop();
    return state;
}
void FSM::pushState(const FSM_state& state)
{
    m_stack.push(state);
}
FSM_state& FSM::getCurrentState()
{
    return m_stack.top();
}
