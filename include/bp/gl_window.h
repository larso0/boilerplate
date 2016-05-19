#ifndef BP_GL_WINDOW_H_
#define BP_GL_WINDOW_H_

#include "window.h"
#include <GL/glew.h>
#include <GL/gl.h>

namespace bp
{
    /*
     * Wrapper class for an OpenGL window.
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
            window_flags(SDL_WINDOW_OPENGL);
        }

        /*
         * Destructor
         */
        virtual ~gl_window()
        {
        }

        /*
         * Swap the gl buffers.
         */
        inline void swap_buffers()
        {
            SDL_GL_SwapWindow(m_window);
        }

        /*
         * Set properties.
         */
        inline void gl_version(int major, int minor)
        {
            if(!m_realized) m_gl_version = { major, minor };
        }

        inline void use_vsync(bool vsync)
        {
            if(!m_realized) m_vsync = vsync;
        }

        /*
         * True if vsync is enabled, false otherwise.
         */
        inline bool vsync() const
        {
            return m_vsync;
        }

        void realize() override;
        void close() override;

    private:
        struct { int major, minor; } m_gl_version;
        SDL_GLContext m_gl_context;
        bool m_vsync;
};
}

#endif
