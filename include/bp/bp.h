#ifndef BP_BP_H_
#define BP_BP_H_

#include <SDL2/SDL.h>
#include "window.h"
#include "gl_window.h"
#include "message.h"
#include "shader.h"
#include "program.h"

namespace bp
{
    /*
     * Initialize the library.
     * Takes care of initializing SDL subsystems.
     * Returns 1 if there was an error, 0 otherwise.
     */
    int init();

    /*
     * Quit the library.
     */
    void quit();
}

#endif
