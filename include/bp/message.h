#ifndef BP_MESSAGE_H_
#define BP_MESSAGE_H_

#include <sstream>

namespace bp
{
    /*
     * Destination messages could be pushed to.
     * Use MESSAGE_DESTINATION_STREAM to push to an output stream.
     * Use MESSAGE_DESTINATION_LOGFILE to push to a logfile.
     * Use MESSAGE_DESTINATION_MESSAGEBOX to display a small window with the
     * message.
     * Use MESSAGE_DESTINATION_SUPRESS to ignore message.
     */
    enum message_destination
    {
        MESSAGE_DESTINATION_STREAM,
        MESSAGE_DESTINATION_LOGFILE,
        MESSAGE_DESTINATION_MESSAGEBOX,
        MESSAGE_DESTINATION_SUPRESS
    };

    /*
     * A stream class to output messages.
     */
    class message_stream : public std::stringstream
    {
    public:
        /*
         * Default constructor.
         * Messages are suppressed by default.
         */
        message_stream() :
            m_dst(MESSAGE_DESTINATION_SUPRESS),
            m_stream(nullptr)
        {}

        /*
         * Constructor that takes an output stream to push messages to.
         * The title is pushed before the messages.
         */
        message_stream(std::string title, std::ostream* s) :
            m_dst(MESSAGE_DESTINATION_STREAM),
            m_title(title),
            m_stream(s)
        {}

        /*
         * Constructor that takes path to a logfile to push messages to.
         * The title is pushed before the messages.
         */
        message_stream(std::string title, const std::string& logfile) :
            m_dst(MESSAGE_DESTINATION_LOGFILE),
            m_title(title),
            m_stream(nullptr),
            m_logfile(logfile)
        {}

        /*
         * Constructor that set up a stream to open messageboxes.
         * The title is used as a title to the messagebox window.
         */
        message_stream(std::string title) :
            m_dst(MESSAGE_DESTINATION_MESSAGEBOX),
            m_title(title),
            m_stream(nullptr)
        {}

        /*
         * Display the accumulated message.
         */
        void push();

        /*
         * Operations that can be performed with the operator <<.
         */
        enum class operation
        {
            PUSH
        };

        /*
         * Get and set properties
         */

        inline void destination(message_destination dst)
        {
            m_dst = dst;
        }
        inline message_destination destination() const
        {
            return m_dst;
        }

        inline void title(const std::string& title)
        {
            m_title = title;
        }
        inline const std::string& title() const
        {
            return m_title;
        }

        inline void stream(std::ostream* s)
        {
            m_stream = s;
            if(s) m_dst = MESSAGE_DESTINATION_STREAM;
            else m_dst = MESSAGE_DESTINATION_SUPRESS;
        }
        inline const std::ostream* stream() const
        {
            return m_stream;
        }

        inline void logfile(std::string path)
        {
            m_logfile = path;
            m_dst = MESSAGE_DESTINATION_LOGFILE;
        }
        inline const std::string& logfile() const
        {
            return m_logfile;
        }

    private:
        message_destination m_dst;
        std::string m_title;
        std::ostream* m_stream;
        std::string m_logfile;
    };

    std::ostream& operator <<(std::ostream& s, message_stream::operation op);

    const message_stream::operation endmsg = message_stream::operation::PUSH;
    extern message_stream info;
    extern message_stream debug;
    extern message_stream warning;
    extern message_stream error;
}

#endif
