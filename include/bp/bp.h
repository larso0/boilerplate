#ifndef BP_BP_H_
#define BP_BP_H_

#include <SDL2/SDL.h>
#include "window.h"
#include "gl_window.h"

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

    /*
     * Push messages to message boxes, standard output, standard error or to
     * log files.
     */
    namespace message
    {
        /*
         * What kinds of messages to push.
         * Use LEVEL_INFO for information to the user.
         * Use LEVEL_DEBUG for information to the developer.
         * Use LEVEL_DEBUG for information to the user/developer
         * about errors that are not fatal for the application.
         * Use LEVEL_ERROR for information to the user/developer
         * about errors that are fatal for the application.
         */
        enum level
        {
            LEVEL_INFO,
            LEVEL_DEBUG,
            LEVEL_WARNING,
            LEVEL_ERROR
        };

        /*
         * Destination messages could be pushed to.
         * Use DESTINATION_SUPRESS to ignore message.
         * Use DESTINATION_STDOUT to push to the standard output
         * stream.
         * Use DESTINATION_STDERR to push to the standard error
         * stream.
         * Use DESTINATION_LOGFILE to push to a logfile (use
         * set_message_logfile to change filename).
         * Use DESTINATION_MESSAGEBOX to display a small window with
         * the message.
         */
        enum destination
        {
            DESTINATION_SUPRESS,
            DESTINATION_STDOUT,
            DESTINATION_STDERR,
            DESTINATION_LOGFILE,
            DESTINATION_MESSAGEBOX
        };

        /*
         * Change the message destination for the given message level.
         */
        void set_destination(level lvl, destination dst);

        /*
         * Set the logfile to append messages of the given level to.
         * For messages to be pushed to the logfile, you need to set the messag
         * destination to LOGFILE for the given level.
         */
        void set_logfile(level lvl, std::string logfile);

        /*
         * Push a message with a given message level.
         */
        void push(level lvl, std::string msg);
    }
}

#endif
