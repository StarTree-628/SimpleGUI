#include "simulator.h"
#include "console_log.h"

simulator::simulator(void)
: m_key_event_queue()
, m_random_data(500)
, m_window(128, 64, m_key_event_queue)
{
    DBG_LOG("Simulator object created.");
}

simulator::~simulator(void)
{
    deinit();
    DBG_LOG("Simulator object destroyed.");
}

void simulator::init(void)
{
    do
    {
        // Initialize SDL2 engine.
        if(0 != ::SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER))
        {
            ERR_LOG("SDL init failed: %s\n", SDL_GetError());
            break;
        }
        ERR_LOG("Initialize windows.");
        if(false == m_window.init())
        {
            ERR_LOG("Initialize main window failed: %s\n", SDL_GetError());
            break;
        }

        m_random_data.set_range(1, 100);
        m_random_data.start();
    }
    while(false);
}

void simulator::deinit(void)
{
    m_random_data.stop();
    m_window.deinit();
    ::SDL_Quit();
}

bool simulator::prolog(void)
{
    m_window.prolog();

    return false;
}

simulator_window& simulator::window(int32_t window_id)
{
    return m_window;
}

simulator_random_data& simulator::random(void)
{
    return m_random_data;
}
