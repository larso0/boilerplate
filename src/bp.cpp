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
            message::push(message::LEVEL_ERROR,
                          "Unable to initialize SDL application: " + err_str);
            return 1;
        }
        return 0;
    }

    void quit()
    {
        SDL_Quit();
    }

    namespace message
    {
        static string logfiles[4] = { "info.log", "debug.log", "warning.log",
                                      "error.log" };
        static destination destinations[4] = { DESTINATION_MESSAGEBOX,
                                               DESTINATION_STDOUT,
                                               DESTINATION_STDERR,
                                               DESTINATION_STDERR };

        void set_destination(level lvl, destination dst)
        {
            destinations[lvl] = dst;
        }

        void set_logfile(level lvl, string logfile)
        {
            logfiles[lvl] = logfile;
        }

        static inline string lvl_to_str(level lvl)
        {
            switch(lvl)
            {
            case LEVEL_INFO:
                return "Information";
            case LEVEL_DEBUG:
                return "Debug information";
            case LEVEL_WARNING:
                return "Warning";
            default:
                return "Error";
            }
        }

        void push(level lvl, string msg)
        {
            switch(destinations[lvl])
            {
            case DESTINATION_STDOUT:
                cout << lvl_to_str(lvl) << ':' << endl << msg << endl;
                break;
            case DESTINATION_STDERR:
                cerr << lvl_to_str(lvl) << ':' << endl << msg << endl;
                break;
            case DESTINATION_LOGFILE:
                {
                    ofstream out(logfiles[lvl], ofstream::app);
                    out << lvl_to_str(lvl) << ':' << endl << msg << endl;
                }
                break;
            case DESTINATION_MESSAGEBOX:
                {
                Uint32 mbf;
                switch(lvl)
                {
                case LEVEL_INFO:
                case LEVEL_DEBUG:
                    mbf = SDL_MESSAGEBOX_INFORMATION;
                    break;
                case LEVEL_WARNING:
                    mbf = SDL_MESSAGEBOX_WARNING;
                    break;
                default:
                    mbf = SDL_MESSAGEBOX_ERROR;
                    break;
                }
                SDL_ShowSimpleMessageBox(mbf, lvl_to_str(lvl).c_str(),
                                         msg.c_str(), nullptr);
            }
                break;
            default:
                break;
            }
        }
    }

}
