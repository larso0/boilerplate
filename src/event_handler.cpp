#include <bp/event_handler.h>

namespace bp
{
    event_handler::event_handler()
    {
    }

    event_handler::~event_handler()
    {
    }

    void event_handler::wait_event()
    {
        SDL_Event event;
        if(SDL_WaitEvent(&event))
        {
            handle_event(&event);
        }
    }

    void event_handler::poll_events()
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            handle_event(&event);
        }
    }

    void event_handler::handle_event(const SDL_Event* event)
    {
        switch(event->type)
        {
        case SDL_QUIT:
            quit();
            break;
        case SDL_WINDOWEVENT:
            switch(event->window.type)
            {
            case SDL_WINDOWEVENT_CLOSE:
                window_close(event->window.windowID);
                break;
            case SDL_WINDOWEVENT_RESIZED:
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                window_resize(event->window.windowID, event->window.data1,
                              event->window.data2);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    void event_handler::quit()
    {
        for(auto f : quit_callbacks) f();
    }

    void event_handler::window_close(Uint32 window_id)
    {
        for(auto f : window_close_callbacks) f(window_id);
    }

    void event_handler::window_resize(Uint32 window_id, int width, int height)
    {
        for(auto f : window_resize_callbacks) f(window_id, width, height);
    }

    void event_handler::add_quit_callback(std::function<void()> f)
    {
        quit_callbacks.push_back(f);
    }

    void event_handler::add_window_close_callback(std::function<void(Uint32)> f)
    {
        window_close_callbacks.push_back(f);
    }

    void event_handler::add_window_resize_callback(
        std::function<void(Uint32, int, int)> f)
    {
        window_resize_callbacks.push_back(f);
    }
}
