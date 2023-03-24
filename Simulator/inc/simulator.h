#ifndef __INCLUDE_CLASS_SIMULATOR_H_
#define __INCLUDE_CLASS_SIMULATOR_H_

#include "simulator_window.h"
#include "simulator_timer.h"
#include "simulator_random_data.h"
#include "simulator_event.h"

class simulator
{
private:
    simulator_key_event_queue       m_key_event_queue;
    simulator_random_data           m_random_data;
    simulator_window                m_window;

public:
    explicit                        simulator(void);
    virtual                         ~simulator(void);
    virtual void                    init(void);
    virtual void                    deinit(void);
    bool                            prolog(void);
    simulator_window&               window(int32_t window_id);
    simulator_random_data&          random(void);
};

#endif // __INCLUDE_CLASS_LVPP_SIMULATOR_H_
