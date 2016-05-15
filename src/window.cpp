#include <bp/window.h>

#include <stdexcept>

using namespace std;

namespace bp
{
    void window::show()
    {
        if(m_shown) return;
        m_window = SDL_CreateWindow(m_title.c_str(), m_x, m_y, m_width,
                                    m_height,
                                    m_window_flags);
        if(m_window == nullptr)
        {
            string err_str(SDL_GetError());
            throw runtime_error("Unable to show window: " + err_str);
        }
        m_id = SDL_GetWindowID(m_window);
        m_shown = true;
    }

    void window::close()
    {
        if(m_shown)
        {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
            m_id = 0;
            m_shown = false;
        }
    }

    void window::title(std::string title)
    {
        if(m_shown) SDL_SetWindowTitle(m_window, title.c_str());
        m_title = title;
    }

    void window::position(int x, int y)
    {
        if(m_shown) SDL_SetWindowPosition(m_window, x, y);
        m_x = x;
        m_y = y;
    }

    void window::size(int width, int height)
    {
        if(m_shown) SDL_SetWindowSize(m_window, width, height);
        m_width = width;
        m_height = height;
    }

    void window::bordered(bool bordered)
    {
        if(m_shown) SDL_SetWindowBordered(m_window, (SDL_bool)bordered);
        else if(bordered) m_window_flags &= ~SDL_WINDOW_BORDERLESS;
        else m_window_flags |= SDL_WINDOW_BORDERLESS;
    }

    void window::fullscreen(bool fullscreen)
    {
        Uint32 flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
        if(m_shown) SDL_SetWindowFullscreen(m_window, fullscreen ? flag : 0);
        else if(fullscreen) m_window_flags |= flag;
        else m_window_flags &= ~flag;
    }
}
