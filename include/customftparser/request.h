#include <string>

#include "token.h"

namespace FTP
{
    enum class Command
    {
            UNKNOWN,
            PASV,
            PORT
    };

    Command ParseCommand(std::string command);

    class Request : public Token
    {
        public:
            Request() = default;
            [[nodiscard]] std::string command();
            [[nodiscard]] std::string spacing1();
            [[nodiscard]] std::string arguments();
            [[nodiscard]] std::string lineending();

            void command(std::string &cmd);
            void spacing1(std::string &spacing);
            void arguments(std::string &args);
            void lineending(std::string &ending);

            [[nodiscard]] std::string serialized() override;

        private:
            std::string _command{};
            std::string _spacing1{};
            std::string _arguments{};
            std::string _lineending{};
    };
}