#ifndef BP_WINDOW_H_
#define BP_WINDOW_H_

#include <SDL2/SDL.h>
#include <string>

namespace bp
{
    /*
     * Wrapper for an SDL_Window.
     */
    class window
    {
    public:
        /*
         * Default constructor that set up the default window properties.
         */
        window() :
            m_window(nullptr),
            m_id(0),
            m_title("window"),
            m_x(SDL_WINDOWPOS_UNDEFINED),
            m_y(SDL_WINDOWPOS_UNDEFINED),
            m_width(640),
            m_height(480),
            m_window_flags(0),
            m_realized(false)
        {
        }

        virtual ~window()
        {
            close();
        }

        /*
         * Initialize and show the window.
         */
        virtual void realize();

        /*
         * Close the window.
         */
        virtual void close();

        /*
         * Set window properties.
         */
        void title(std::string title);
        void position(int x, int y);
        void size(int width, int height);
        void bordered(bool bordered);
        void fullscreen(bool fullscreen);

        /*
         * The following changes nothing if window is already shown.
         */
        void flags(Uint32 flags)
        {
            m_window_flags |= flags;
        }

        void resizable(bool r)
        {
            if(r) m_window_flags |= SDL_WINDOW_RESIZABLE;
            else m_window_flags &= ~SDL_WINDOW_RESIZABLE;
        }

        /*
         * Get window properties.
         */
        Uint32 id() const
        {
            return m_id;
        }

        const std::string& title() const
        {
            return m_title;
        }

        Uint32 flags() const
        {
            return m_window_flags;
        }

        SDL_Window* handle()
        {
            return m_window;
        }

        bool shown() const
        {
            return m_realized;
        }

        int width() const
        {
            return m_width;
        }

        int width()
        {
            if(m_realized) SDL_GetWindowSize(m_window, &m_width, &m_height);
            return m_width;
        }

        int height() const
        {
            return m_height;
        }

        int height()
        {
            if(m_realized) SDL_GetWindowSize(m_window, &m_width, &m_height);
            return m_height;
        }

    protected:
        /*
         * Window handle
         */
        SDL_Window* m_window;

        /*
         * Window id for use with events
         */
        Uint32 m_id;

        /*
         * Window properties
         */
        std::string m_title;
        int m_x, m_y;
        int m_width, m_height;
        Uint32 m_window_flags;

        /*
         * Whether or not the window is shown.
         */
        bool m_realized;
    };
}

#endif

