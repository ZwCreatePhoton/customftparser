#include <cassert>
#include "customftparser/request_parser.h"

namespace FTP
{
    RequestParserState RequestParser::state()
    {
        return _state;
    }

    void RequestParser::process_segments(std::vector<std::vector<uint8_t>> &segments)
    {
        for (auto &segment : segments)
            process_segment(segment);
    }

    std::vector<std::reference_wrapper<Request>> RequestParser::requests()
    {
        std::vector<std::reference_wrapper<Request>> reqs{};
        for (auto &rp : _requests)
            reqs.emplace_back(*rp);
        return reqs;
    }

    void RequestParser::process_segment(std::vector<uint8_t> &segment)
    {
        if (segment.empty()) // connection closed
        {
            if (_requests.empty() && data.empty())
            {
                // Connection closed before there was any data to parse
                ;
            }
            else if (_requests.empty() && !data.empty())
            {
                ;
            }
            else if (!_requests.empty() && data.empty())
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

        // There are 0 requests or all requests previously parsed are complete ; we are ready to parse a new request
        if (state() == RequestParserState::UNKNOWN || (!_requests.empty() && state() == RequestParserState::REQUEST_PARSED))
        {
            match = std::smatch();
            if (std::regex_search(data, match, FTP_REQUEST_COMMAND_REGEX))
            {
                // we found a request
                std::string command = match.str(1);
                _requests.push_back(std::make_unique<Request>());
                _requests[_requests.size()-1]->command(command);
                _requests[_requests.size()-1]->offset = index;
                _state = RequestParserState::REQUEST_COMMAND_PARSED;
            }
            else
            {
                return;
            }
            // We have just finished parsing the command of the request
            index += match.position() + match.length();
            data.erase(0, match.position() + match.length());
        }

        // There is at least 1 request
        // The parsing of all but the last one are complete
        Request &current_request = *_requests[_requests.size()-1];

        assert(state() != RequestParserState::UNKNOWN);
        assert(state() < RequestParserState::REQUEST_ARGUMENTS_PARSED);

        if (state() == RequestParserState::REQUEST_COMMAND_PARSED)
        {
            match = std::smatch();
            if (std::regex_search(data, match, FTP_REQUEST_SPACING1_REGEX))
            {
                std::string spacing = match.str(1);
                _requests[_requests.size()-1]->spacing1(spacing);
                _state = RequestParserState::REQUEST_SPACING1_PARSED;
                index += match.position() + match.length();
                data.erase(0, match.position() + match.length());
            }
            else
            {
                return;
            }
        }

        if (state() == RequestParserState::REQUEST_SPACING1_PARSED)
        {
            match = std::smatch();
            if (std::regex_search(data, match, FTP_REQUEST_ARGUMENTS_LINENDING_REGEX))
            {
                std::string arguments = match.str(1);
                std::string lineending = match.str(2);
                _requests[_requests.size()-1]->arguments(arguments);
                _requests[_requests.size()-1]->lineending(lineending);
                _state = RequestParserState::REQUEST_PARSED;
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
