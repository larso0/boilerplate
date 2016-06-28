#ifndef BP_GL_WINDOW_H_
#define BP_GL_WINDOW_H_

#include "window.h"
#include <GL/glew.h>
#include <GL/gl.h>

namespace bp
{
    /*
     * Wrapper class for an OpenGL window and context.
     */
    class gl_window : public window
    {
    public:
        /*
         * Default constructor that set up OpenGL version.
         */
        gl_window() :
            m_gl_version({ 4, 5 }),
            m_gl_context(nullptr),
            m_vsync(true)
        {
            flags(SDL_WINDOW_OPENGL);
        }

        /*
         * Destructor
         */
        virtual ~gl_window()
        {
        }

        /*
         * Swap the front and back buffers.
         */
        void swap_buffers()
        {
            SDL_GL_SwapWindow(m_window);
        }

        /*
         * Switch to using the context for this window.
         * Use this to switch between several gl windows.
         */
        void make_current()
        {
            SDL_GL_MakeCurrent(m_window, m_gl_context);
        }

        /*
         * Set and get properties.
         */
        void gl_version(int major, int minor)
        {
            if(!m_realized) m_gl_version = { major, minor };
        }

        void vsync(bool vsync)
        {
            if(!m_realized) m_vsync = vsync;
        }

        bool vsync() const
        {
            return m_vsync;
        }

        void realize() override;
        void close() override;

    private:
        struct { int major, minor; } m_gl_version;
        SDL_GLContext m_gl_context;
        bool m_vsync;

        static bool glew_inited;
};
}

#endif
