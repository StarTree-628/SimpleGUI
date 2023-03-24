#ifndef __INCLUDE_CLASS_SIMULATOR_RANDOM_DATA_H_
#define __INCLUDE_CLASS_SIMULATOR_RANDOM_DATA_H_

#include "simulator_timer.h"
#include <random>
#include <memory>

class simulator_random_data : public simulator_timer
{
private:
    std::default_random_engine      m_random_engine;
    int                             m_random_val;
    bool                            m_is_update;
    int                             m_range_min;
    int                             m_range_max;

protected:
    virtual void                    init_random_engine(void);
    virtual void                    on_timer_triggered(void);

public:
    explicit                        simulator_random_data(void);
    explicit                        simulator_random_data(uint32_t interval);
    virtual                         ~simulator_random_data(void);
    void                            set_range(int range_min, int range_max);
    bool                            is_update(void) const;
    int                             value(void);
};

#endif // __INCLUDE_CLASS_SIMULATOR_RANDOM_DATA_H_
