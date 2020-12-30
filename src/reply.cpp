#include "customftparser/reply.h"


std::string FTP::Reply::code()
{
    return _code;
}

std::string FTP::Reply::spacing1()
{
    return _spacing1;
}

std::string FTP::Reply::message()
{
    return _message;
}

std::string FTP::Reply::lineending()
{
    return _lineending;
}

void FTP::Reply::code(std::string &code)
{
    _code = code;
}

void FTP::Reply::spacing1(std::string &spacing)
{
    _spacing1 = spacing;
}

void FTP::Reply::message(std::string &message)
{
    _message = message;
}

void FTP::Reply::lineending(std::string &ending)
{
    _lineending = ending;
}

std::string FTP::Reply::serialized()
{
    return _code + _spacing1 + _message + _lineending;
}
