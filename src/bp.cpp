#include <bp/bp.h>
#include <iostream>
#include <fstream>

using namespace std;

namespace bp
{
    static const int INIT_FLAGS = SDL_INIT_VIDEO;

    int init()
    {
        int err = SDL_Init(INIT_FLAGS);
        if(err)
        {
            string err_str(SDL_GetError());
            error << "Unable to initialize SDL application: " << err_str << endmsg;
            return 1;
        }
        return 0;
    }

    void quit()
    {
        SDL_Quit();
    }
}
