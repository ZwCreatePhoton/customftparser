#include <regex>

#include "reply.h"

namespace FTP
{
    const std::regex FTP_REPLY_CODE_REGEX(R"(^(\d+))"); // captures: code
    const std::regex FTP_REPLY_SPACING1_REGEX(R"(^([^\S\r\n]*))"); // captures: the space between the code and its message
    const std::regex FTP_REPLY_MESSAGE_LINENDING_REGEX(R"(^([^\n\r]*)(\r\n|\n))"); // captures: reply message , line ending

    enum class ReplyParserState
    {
            UNKNOWN = 0,
            REPLY_CODE_PARSED = 1,
            REPLY_SPACING1_PARSED = 2,
            REPLY_MESSAGE_PARSED = 3,
            REPLY_LINEENDING_PARSED = 4,
            REPLY_PARSED = 5
    };

    class ReplyParser
    {
        public:
            ReplyParser() = default;
            ReplyParserState state();
            void process_segment(std::vector<uint8_t> &segment);
            void process_segments(std::vector<std::vector<uint8_t>> &segments);
            std::vector<std::reference_wrapper<Reply>> replys();

        private:
            ReplyParserState _state = ReplyParserState::UNKNOWN;
            std::string data{}; // "data" is the data at index "index" of the processed stream (the collection of segments)
            uint64_t index = 0;

            std::vector<std::unique_ptr<Reply>> _replys{};
    };
}
