#ifndef __INCLUDE_CLASS_SIMULATOR_WINDOW_H_
#define __INCLUDE_CLASS_SIMULATOR_WINDOW_H_

#include "SDL.h"
#include "simulator_event.h"

#define SIMULATOR_COLOR_BYTES   (3)

class simulator_touch_state
{
public:
                                    simulator_touch_state(void);
                                    ~simulator_touch_state(void);
    int                             m_pos_x;
    int                             m_pos_y;
    bool                            m_pressed;
};

class simulator_key_state
{
public:
    explicit                        simulator_key_state(void);
                                    ~simulator_key_state(void);
    int                             m_keycode;
    bool                            m_pressed;
};

class simulator_window
{
protected:
    int                             m_width;
    int                             m_height;
    uint8_t*                        m_paint_buffer;
    SDL_Window*                     m_window_handle;
    SDL_Texture*                    m_texture;
    SDL_Renderer*                   m_renderer;
    SDL_Event                       m_event;
    bool                            m_exit;
    bool                            m_initialized;
    simulator_touch_state           m_touch_state;
    simulator_key_event_queue&      m_key_event_queue;

public:
    explicit                        simulator_window(int width, int height, simulator_key_event_queue& key_event_queue);
    explicit                        simulator_window(const simulator_window& right) = delete;
    virtual                         ~simulator_window(void);
    bool                            init(void);
    void                            deinit(void);
    bool                            prolog(void);
    void                            paint_pixel(int pos_x, int pos_y, uint8_t red, uint8_t green, uint8_t blue);
    void                            paint_pixel(int pos_x, int pos_y, uint32_t color_hex);
    void                            clear_paint(void);
    void                            sync_paint_buffer(void);
    bool                            exit(void);
    int                             width(void) const;
    int                             height(void) const;
    int                             get_touch_pos_x(void) const;
    int                             get_touch_pos_y(void) const;
    bool                            get_touch_pressed(void) const;
    simulator_key_event_queue&      key_event(void);
    void                            snapshot(void);
};

#endif // __INCLUDE_CLASS_SIMULATOR_WINDOW_H_
