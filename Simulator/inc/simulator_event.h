#ifndef __INCLUDE_CLASS_KEY_EVENT_H_
#define __INCLUDE_CLASS_KEY_EVENT_H_

#include "SDL.h"
#include <queue>

typedef enum _sim_key_event_
{
    sim_key_release = 0,
    sim_key_press,
}sim_key_act_t;

class simulator_key_event
{
private:
    int                             m_key_code;
    sim_key_act_t                   m_key_event;

public:
    explicit                        simulator_key_event(void);
    explicit                        simulator_key_event(int code, sim_key_act_t event);
    explicit                        simulator_key_event(const simulator_key_event& source);
    virtual                         ~simulator_key_event(void);
    void                            set_code(int key_code);
    void                            set_event(sim_key_act_t event);
    int                             code(void) const;
    sim_key_act_t                   event(void) const;
};

typedef std::queue<simulator_key_event> simulator_key_event_queue;

#endif // __INCLUDE_CLASS_KEY_EVENT_H_
