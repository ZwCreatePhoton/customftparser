#pragma once

class Token
{
    public:
        Token() = default;
        [[nodiscard]] virtual std::string serialized() = 0;
        uint64_t offset = 0;
};
