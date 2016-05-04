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
            m_shown(false)
        {}

        virtual ~window() { close(); }

        /*
         * Initialize and show the window.
         */
        virtual void show();

        /*
         * Close the window.
         */
        virtual void close();

        /*
         * Set window properties.
         */
        void set_title(std::string title);
        void set_position(int x, int y);
        void set_size(int width, int height);
        void set_bordered(bool bordered);
        void set_fullscreen(bool fullscreen);

        /*
         * The following changes nothing if window is already shown.
         */
        inline void set_window_flags(Uint32 flags) { m_window_flags = flags; }
        inline void enable_window_flags(Uint32 flags) { m_window_flags |= flags; }

        /*
         * Get window properties.
         */
        inline Uint32 id() const { return m_id; }
        inline const std::string& title() const { return m_title; }
        inline Uint32 window_flags() const { return m_window_flags; }
        inline SDL_Window* window_handle() { return m_window; }
        inline Uint32 window_id() { return m_id; }
        inline bool shown() const { return m_shown; }

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
        bool m_shown;
    };
}

#endif

