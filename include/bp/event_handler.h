#ifndef BP_EVENT_HANDLER_H_
#define BP_EVENT_HANDLER_H_

#include <SDL2/SDL.h>
#include <vector>
#include <functional>
#include <utility>

namespace bp
{
    /*
     * Handle events by either extending this class or add callbacks.
     */
    class event_handler
    {
    public:
        event_handler();
        virtual ~event_handler();

        /*
         * Wait for and handle a single event.
         */
        void wait_event();

        /*
         * Poll all events and handle them.
         */
        void poll_events();

        /*
         * Handle a single SDL event.
         */
        virtual void handle_event(const SDL_Event* event);

        /*
         * Quit callback.
         * Is called when a user attempts to close the last open window.
         */
        virtual void quit();

        /*
         * Window close callback.
         * Is called when a user attempts to close a window.
         */
        virtual void window_close(Uint32 window_id);

        /*
         * Resize callback.
         * Is called whenever a window is resized.
         * Use window_id to identify which window is resized.
         */
        virtual void window_resize(Uint32 window_id, int width, int height);

        /*
         * Add callback functions for event callbacks.
         */
        void quit_callback(std::function<void()> f);
        void window_close_callback(Uint32 window_id,
                                   std::function<void()> f);
        void window_resize_callback(Uint32 window_id,
                                    std::function<void(int, int)> f);

    private:
        std::vector<std::function<void()>> quit_callbacks;
        std::vector<std::pair<Uint32, std::function<void()>>>
            window_close_callbacks;
        std::vector<std::pair<Uint32, std::function<void(int, int)>>>
            window_resize_callbacks;
    };
}

#endif
