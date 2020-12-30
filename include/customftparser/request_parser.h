#include <regex>

#include "request.h"

namespace FTP
{
    const std::regex FTP_REQUEST_COMMAND_REGEX(R"(^(\w+))"); // captures: command
    const std::regex FTP_REQUEST_SPACING1_REGEX(R"(^([^\S\r\n]*))"); // captures: the space between the command and its arguments
    const std::regex FTP_REQUEST_ARGUMENTS_LINENDING_REGEX(R"(^([^\n\r]*)(\r\n|\n))"); // captures: command arguments , line ending

    enum class RequestParserState
    {
            UNKNOWN = 0,
            REQUEST_COMMAND_PARSED = 1,
            REQUEST_SPACING1_PARSED = 2,
            REQUEST_ARGUMENTS_PARSED = 3,
            REQUEST_LINEENDING_PARSED = 4,
            REQUEST_PARSED = 5,
    };

    class RequestParser
    {
        public:
            RequestParser() = default;
            RequestParserState state();
            void process_segment(std::vector<uint8_t> &segment);
            void process_segments(std::vector<std::vector<uint8_t>> &segments);
            std::vector<std::reference_wrapper<Request>> requests();

        private:
            RequestParserState _state = RequestParserState::UNKNOWN;
            std::string data{}; // "data" is the data at index "index" of the processed stream (the collection of segments)
            uint64_t index = 0;

            std::vector<std::unique_ptr<Request>> _requests{};
    };
}