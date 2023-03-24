#include "simulator_timer.h"
#include "console_log.h"

simulator_timer::simulator_timer(bool repeat)
: m_timer_id(0)
, m_interval(0)
, m_repeat(repeat)
, m_trigger(0)
{

}

simulator_timer::simulator_timer(uint32_t interval, bool repeat)
: m_timer_id(0)
, m_interval(interval)
, m_repeat(repeat)
, m_trigger(0)
{

}

simulator_timer::~simulator_timer(void)
{

}

uint32_t simulator_timer::simulator_timer_callback(uint32_t interval, void *param)
{
    uint32_t next_interval = 0;
    if(param)
    {
        simulator_timer* timer_obj = reinterpret_cast<simulator_timer*>(param);
        if(timer_obj)
        {
            ++timer_obj->m_trigger;
            timer_obj->on_timer_triggered();
            if(timer_obj->m_repeat)
            {
                next_interval = timer_obj->m_interval;
            }
        }
    }

    return next_interval;
}

void simulator_timer::on_timer_triggered(void)
{

}

bool simulator_timer::start(void)
{
    bool start_done = true;
    if(0 == m_timer_id)
    {
        if(m_interval)
        {
            m_timer_id = ::SDL_AddTimer(m_interval, simulator_timer_callback, this);
            if(0 == m_timer_id)
            {
                // Add timer failed.
                start_done = false;
            }
        }
        else
        {
            // Timer interval cannot be 0.
            start_done = false;
        }
    }

    return start_done;
}

void simulator_timer::stop(void)
{
    if(m_timer_id)
    {
        ::SDL_RemoveTimer(m_timer_id);
        m_timer_id = 0;
        m_trigger = 0;
    }
}

void simulator_timer::set_interval(uint32_t interval)
{
    m_interval = interval;
}

unsigned int simulator_timer::trigger_count(void) const
{
    return m_trigger;
}

void simulator_timer::reset_trigger(void)
{
    m_trigger = 0;
}

