#include <bp/bp.h>
#include <bp/gl_window.h>
#include <stdexcept>

using namespace std;

namespace bp
{
    bool gl_window::glew_inited = false;

    void gl_window::realize()
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, m_gl_version.major);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, m_gl_version.minor);
        window::realize();

        m_gl_context = SDL_GL_CreateContext(m_window);
        if(m_gl_context == nullptr)
        {
            string err_str(SDL_GetError());
            throw runtime_error("Unable to realize window: " + err_str);
        }

        if(m_vsync)
        {
            int err = SDL_GL_SetSwapInterval(1);
            if(err)
            {
                string err_str(SDL_GetError());
                warning << "Unable to set vsync: " << err_str << endmsg;
            }
        }

        if(glew_inited) return;
        glewExperimental = GL_TRUE;
        GLenum glew_err = glewInit();
        if(glew_err != GLEW_OK)
        {
            string error_str((const char*)glewGetErrorString(glew_err));
            throw runtime_error("Could not initialize GLEW: " + error_str);
        }
        glew_inited = true;
    }

    void gl_window::close()
    {
        if(m_gl_context) SDL_GL_DeleteContext(m_gl_context);
        window::close();
    }
}
