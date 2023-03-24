#ifndef __INCLUDE_CLASS_SIMULATOR_TIMER_H_
#define __INCLUDE_CLASS_SIMULATOR_TIMER_H_

#include "SDL.h"
#include <atomic>

class simulator_timer
{
private:
    SDL_TimerID                     m_timer_id;
    uint32_t                        m_interval;
    bool                            m_repeat;
    std::atomic_uint                m_trigger;

    static uint32_t                 simulator_timer_callback(uint32_t interval, void *param);

protected:
    virtual void                    on_timer_triggered(void);

public:
    explicit                        simulator_timer(bool repeat = true);
    explicit                        simulator_timer(uint32_t interval, bool repeat = true);
    virtual                         ~simulator_timer(void);
    bool                            start(void);
    void                            stop(void);
    void                            set_interval(uint32_t interval);
    unsigned int                    trigger_count(void) const;
    void                            reset_trigger(void);
};

#endif // __INCLUDE_CLASS_SIMULATOR_TIMER_H_
