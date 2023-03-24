#include "simulator_event.h"

simulator_key_event::simulator_key_event(void)
: m_key_code(SDL_SCANCODE_UNKNOWN)
, m_key_event(sim_key_release)
{

}

simulator_key_event::simulator_key_event(int code, sim_key_act_t event)
: m_key_code(code)
, m_key_event(event)
{

}

simulator_key_event::simulator_key_event(const simulator_key_event& source)
: m_key_code(source.m_key_code)
, m_key_event(source.m_key_event)
{

}

simulator_key_event::~simulator_key_event(void)
{

}

void simulator_key_event::set_code(int key_code)
{
    m_key_code = key_code;
}

void simulator_key_event::set_event(sim_key_act_t event)
{
    m_key_event = event;
}

int simulator_key_event::code(void) const
{
    return m_key_code;
}

sim_key_act_t simulator_key_event::event(void) const
{
    return m_key_event;
}

