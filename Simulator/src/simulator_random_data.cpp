#include "simulator_random_data.h"
#include "console_log.h"

simulator_random_data::simulator_random_data(void)
: simulator_timer(true)
, m_is_update(false)
, m_range_min(0)
, m_range_max(100)
{

}

simulator_random_data::simulator_random_data(uint32_t interval)
: simulator_timer(interval, true)
, m_is_update(false)
, m_range_min(0)
, m_range_max(100)
{

}

simulator_random_data::~simulator_random_data(void)
{

}

void simulator_random_data::init_random_engine(void)
{

}

void simulator_random_data::on_timer_triggered(void)
{
    std::uniform_int_distribution<int> distribution(m_range_min, m_range_max);
    m_random_val = distribution(m_random_engine);
    m_is_update = true;
}

void simulator_random_data::set_range(int range_min, int range_max)
{
    m_range_min = range_min;
    m_range_max = range_max;
}

bool simulator_random_data::is_update(void) const
{
    return m_is_update;
}

int simulator_random_data::value(void)
{
    m_is_update = false;
    return m_random_val;
}

