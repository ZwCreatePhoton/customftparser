#include <cassert>
#include "customftparser/reply_parser.h"

namespace FTP
{
    ReplyParserState ReplyParser::state()
    {
        return _state;
    }

    void ReplyParser::process_segments(std::vector<std::vector<uint8_t>> &segments)
    {
        for (auto &segment : segments)
            process_segment(segment);
    }

    std::vector<std::reference_wrapper<Reply>> ReplyParser::replys()
    {
        std::vector<std::reference_wrapper<Reply>> reps{};
        for (auto &rp : _replys)
            reps.emplace_back(*rp);
        return reps;
    }

    void ReplyParser::process_segment(std::vector<uint8_t> &segment)
    {
        if (segment.empty()) // connection closed
        {
            if (_replys.empty() && data.empty())
            {
                // Connection closed before there was any data to parse
                ;
            }
            else if (_replys.empty() && !data.empty())
            {
                ;
            }
            else if (!_replys.empty() && data.empty())
            {
                ;
            }
            else // !message.empty() && !data.empty()
            {
                ;
            }
            return;
        }

        std::smatch match = std::smatch();
        data += std::string(segment.begin(), segment.end());

        // There are 0 replies or all replies previously parsed are complete ; we are ready to parse a new reply
        if (state() == ReplyParserState::UNKNOWN || (!_replys.empty() && state() == ReplyParserState::REPLY_PARSED))
        {
            match = std::smatch();
            if (std::regex_search(data, match, FTP_REPLY_CODE_REGEX))
            {
                // we found a reply
                std::string code = match.str(1);
                _replys.push_back(std::make_unique<Reply>());
                _replys[_replys.size()-1]->code(code);
                _replys[_replys.size()-1]->offset = index;
                _state = ReplyParserState::REPLY_CODE_PARSED;
            }
            else
            {
                return;
            }
            // We have just finished parsing the code of the reply
            index += match.position() + match.length();
            data.erase(0, match.position() + match.length());
        }

        // There is at least 1 reply
        // The parsing of all but the last one are complete
        Reply &current_reply = *_replys[_replys.size()-1];

        assert(state() != ReplyParserState::UNKNOWN);
        assert(state() < ReplyParserState::REPLY_MESSAGE_PARSED);

        if (state() == ReplyParserState::REPLY_CODE_PARSED)
        {
            match = std::smatch();
            if (std::regex_search(data, match, FTP_REPLY_SPACING1_REGEX))
            {
                std::string spacing = match.str(1);
                _replys[_replys.size()-1]->spacing1(spacing);
                _state = ReplyParserState ::REPLY_SPACING1_PARSED;
                index += match.position() + match.length();
                data.erase(0, match.position() + match.length());
            }
            else
            {
                return;
            }
        }

        if (state() == ReplyParserState::REPLY_SPACING1_PARSED)
        {
            match = std::smatch();
            if (std::regex_search(data, match, FTP_REPLY_MESSAGE_LINENDING_REGEX))
            {
                std::string message = match.str(1);
                std::string lineending = match.str(2);
                _replys[_replys.size()-1]->message(message);
                _replys[_replys.size()-1]->lineending(lineending);
                _state = ReplyParserState::REPLY_PARSED;
                index += match.position() + match.length();
                data.erase(0, match.position() + match.length());
            }
            else
            {
                return;
            }
        }
    }
}
