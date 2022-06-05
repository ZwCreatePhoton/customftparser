#include <memory>
#include <string>

#include "token.h"

namespace FTP
{
    uint16_t ParseCode(const std::string& code);

    class Reply : public Token
    {
        public:
            Reply() = default;

            [[nodiscard]] std::string code();

            [[nodiscard]] std::string spacing1();

            [[nodiscard]] std::string message();

            [[nodiscard]] std::string lineending();

            void code(std::string &code);

            void spacing1(std::string &spacing);

            void message(std::string &message);

            void lineending(std::string &ending);

            [[nodiscard]] std::string serialized() override;

        private:
            std::string _code{};
            std::string _spacing1{};
            std::string _message{};
            std::string _lineending{};
    };
}
