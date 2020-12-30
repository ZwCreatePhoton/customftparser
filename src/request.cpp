#include "customftparser/request.h"

std::string FTP::Request::command()
{
    return _command;
}

std::string FTP::Request::spacing1()
{
    return _spacing1;
}

std::string FTP::Request::arguments()
{
    return _arguments;
}

std::string FTP::Request::lineending()
{
    return _lineending;
}

void FTP::Request::command(std::string &cmd)
{
    _command = cmd;
}

void FTP::Request::spacing1(std::string &spacing)
{
    _spacing1 = spacing;
}

void FTP::Request::arguments(std::string &args)
{
    _arguments = args;
}

void FTP::Request::lineending(std::string &ending)
{
    _lineending = ending;
}

std::string FTP::Request::serialized()
{
    return _command + _spacing1 + _arguments + _lineending;
}
