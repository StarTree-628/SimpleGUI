#include "simulator.h"
#include "console_log.h"

#define ZOOM_SCALE      (2)

simulator_touch_state::simulator_touch_state(void)
: m_pos_x(0)
, m_pos_y(0)
, m_pressed(false)
{

}

simulator_touch_state::~simulator_touch_state(void)
{

}

simulator_key_state::simulator_key_state(void)
: m_keycode(SDL_SCANCODE_UNKNOWN)
, m_pressed(false)
{

}

simulator_key_state::~simulator_key_state(void)
{

}

simulator_window::simulator_window(int width, int height, simulator_key_event_queue& key_event_queue)
: m_width(width)
, m_height(height)
, m_window_handle(nullptr)
, m_texture(nullptr)
, m_renderer(nullptr)
, m_exit(false)
, m_initialized(false)
, m_key_event_queue(key_event_queue)
{
    DBG_LOG("Window created.");
    memset(&m_event, 0x00, sizeof(SDL_Event));
}

simulator_window::~simulator_window(void)
{
    deinit();
}

bool simulator_window::init(void)
{
    // Use SDL2 screen with 24-bit RGB-888 format color.
    // Confirm paint buffer create done and continue.
    // Create and initialize SDL instance.
    do
    {
        // Allocate simulator texture paint buffer.
        size_t paint_buffer_size = m_width * m_height * SIMULATOR_COLOR_BYTES;
        m_paint_buffer = new uint8_t[paint_buffer_size];
        if(nullptr == m_paint_buffer)
        {
            ERR_LOG("Allocate paint buffer failed.");
            break;
        }

        m_window_handle = SDL_CreateWindow("Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width * ZOOM_SCALE, m_height * ZOOM_SCALE, SDL_WINDOW_OPENGL);
        if(nullptr == m_window_handle)
        {
            ERR_LOG("SDL create window failed: %s\n", SDL_GetError());
            break;
        }
        m_renderer = SDL_CreateRenderer(m_window_handle, 0, SDL_RENDERER_SOFTWARE);
        if(nullptr == m_renderer)
        {
            ERR_LOG("SDL create renderer failed: %s\n", SDL_GetError());
            break;
        }
        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGB24, // NOTE: Use 24-bit RGB-888 format color.
                    SDL_TEXTUREACCESS_TARGET, m_width, m_height);
        if(nullptr == m_texture)
        {
            ERR_LOG("create texture failed: %s\n", SDL_GetError());
            break;
        }
        // Initialize texture for background.
        SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
        SDL_RenderPresent(m_renderer);
        // SDL instance initialize done.
        m_initialized = true;
    }
    while(false);

    return m_initialized;
}

void simulator_window::deinit(void)
{
    if(m_initialized)
    {
        if(nullptr != m_window_handle)
        {
            SDL_DestroyWindow(m_window_handle);
            m_window_handle = nullptr;
        }
        if(nullptr != m_renderer)
        {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
        }
        if(nullptr != m_texture)
        {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
        m_initialized = false;
    }
}

bool simulator_window::prolog(void)
{
    bool has_event = true;

    if(m_initialized)
    {
        if(SDL_PollEvent(&m_event))
        {
            switch(m_event.type)
            {
                case SDL_QUIT:
                {
                    m_exit = true;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    m_touch_state.m_pos_x = m_event.motion.x;
                    m_touch_state.m_pos_y = m_event.motion.y;
                    m_touch_state.m_pressed = true;
                    break;
                }
                case SDL_MOUSEMOTION:
                {
                    m_touch_state.m_pos_x = m_event.motion.x;
                    m_touch_state.m_pos_y = m_event.motion.y;
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                {
                    m_touch_state.m_pos_x = m_event.motion.x;
                    m_touch_state.m_pos_y = m_event.motion.y;
                    m_touch_state.m_pressed = false;
                    break;
                }
                case SDL_KEYDOWN:
                {
                    m_key_event_queue.emplace(m_event.key.keysym.scancode, sim_key_press);
                    if(SDL_SCANCODE_P == m_event.key.keysym.scancode)
                    {
                        snapshot();
                    }
                    break;
                }
                case SDL_KEYUP:
                {
                    m_key_event_queue.emplace(m_event.key.keysym.scancode, sim_key_release);
                    break;
                }
                default:
                {
                    // INF_LOG("No event process for 0x%04X.", event.type);
                    /* do nothing. */
                    has_event = false;
                }
            }
        }
    }
    return has_event;
}

void simulator_window::paint_pixel(int pos_x, int pos_y, uint8_t red, uint8_t green, uint8_t blue)
{
    if(m_paint_buffer)
    {
        m_paint_buffer[(pos_y * m_width + pos_x) * SIMULATOR_COLOR_BYTES + 0] = red;
        m_paint_buffer[(pos_y * m_width + pos_x) * SIMULATOR_COLOR_BYTES + 1] = green;
        m_paint_buffer[(pos_y * m_width + pos_x) * SIMULATOR_COLOR_BYTES + 2] = blue;
    }
}

void simulator_window::paint_pixel(int pos_x, int pos_y, uint32_t color_hex)
{
    if(m_paint_buffer)
    {
        m_paint_buffer[(pos_y * m_width + pos_x) * SIMULATOR_COLOR_BYTES + 0] = (color_hex >> 16) & 0xFF;
        m_paint_buffer[(pos_y * m_width + pos_x) * SIMULATOR_COLOR_BYTES + 1] = (color_hex >> 8) & 0xFF;
        m_paint_buffer[(pos_y * m_width + pos_x) * SIMULATOR_COLOR_BYTES + 2] = color_hex & 0xFF;
    }
}

void simulator_window::clear_paint(void)
{
    ::memset(m_paint_buffer, 0x00, sizeof(uint8_t)*(m_width * m_height * SIMULATOR_COLOR_BYTES));
}

void simulator_window::sync_paint_buffer(void)
{
    /* Sync paint buffer content to screens. */
    SDL_UpdateTexture(m_texture, NULL, m_paint_buffer, m_width * SIMULATOR_COLOR_BYTES);
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
}

bool simulator_window::exit(void)
{
    return m_exit;
}

int simulator_window::width(void) const
{
    return m_width;
}

int simulator_window::height(void) const
{
    return m_height;
}

int simulator_window::get_touch_pos_x(void) const
{
    return m_touch_state.m_pos_x;
}

int simulator_window::get_touch_pos_y(void) const
{
    return m_touch_state.m_pos_y;
}

bool simulator_window::get_touch_pressed(void) const
{
    return m_touch_state.m_pressed;
}

simulator_key_event_queue& simulator_window::key_event(void)
{
    return m_key_event_queue;
}

void simulator_window::snapshot(void)
{
    SDL_Surface *sshot = SDL_CreateRGBSurface(0, m_width*ZOOM_SCALE, m_height*ZOOM_SCALE, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(m_renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    SDL_SaveBMP(sshot, "screenshot.bmp");
    SDL_FreeSurface(sshot);
}
