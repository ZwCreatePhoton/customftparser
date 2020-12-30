#include <iostream>
#include <cassert>

#include "customftparser/request_parser.h"
#include "customftparser/reply_parser.h"

void test_request_parser1()
{
    std::string request_str = "USER myusername\r\n";
    auto parser = FTP::RequestParser();
    std::vector<uint8_t> segment(request_str.begin(), request_str.end());

    parser.process_segment(segment);

    auto requests = parser.requests();
    assert(requests.size() == 1);
    auto &request = requests[0].get();
    assert(request.command() == "USER");
    assert(request.spacing1() == " ");
    assert(request.arguments() == "myusername");
    assert(request.lineending() == "\r\n");
    assert(request.serialized() == request_str);
}

void test_request_parser2()
{
    std::string request_str = "SOMECOMMAND argument1 argument2\n";
    auto parser = FTP::RequestParser();
    std::vector<uint8_t> segment(request_str.begin(), request_str.end());

    parser.process_segment(segment);

    auto requests = parser.requests();
    assert(requests.size() == 1);
    auto &request = requests[0].get();
    assert(request.command() == "SOMECOMMAND");
    assert(request.spacing1() == " ");
    assert(request.arguments() == "argument1 argument2");
    assert(request.lineending() == "\n");
    assert(request.serialized() == request_str);
}

void test_request_parser3()
{
    std::string request_str1 = "SOMECOMMAND argument1 argument2\n";
    std::string request_str2 = "SOMEOTHERCOMMAND arg1 arg2\n";
    auto parser = FTP::RequestParser();
    std::vector<uint8_t> segment1(request_str1.begin(), request_str1.end());
    std::vector<uint8_t> segment2(request_str2.begin(), request_str2.end());
    parser.process_segment(segment1);

    parser.process_segment(segment2);

    auto requests = parser.requests();
    assert(requests.size() == 2);
    auto &request = requests[1].get();
    assert(request.command() == "SOMEOTHERCOMMAND");
    assert(request.spacing1() == " ");
    assert(request.arguments() == "arg1 arg2");
    assert(request.lineending() == "\n");
    assert(request.serialized() == request_str2);
}

void test_reply_parser1()
{
    std::string reply_str = "500 'AUTH GSSAPI': command not understood\r\n";
    auto parser = FTP::ReplyParser();
    std::vector<uint8_t> segment(reply_str.begin(), reply_str.end());

    parser.process_segment(segment);

    auto replys = parser.replys();
    assert(replys.size() == 1);
    auto &reply = replys[0].get();
    assert(reply.code() == "500");
    assert(reply.spacing1() == " ");
    assert(reply.message() == "'AUTH GSSAPI': command not understood");
    assert(reply.lineending() == "\r\n");
    assert(reply.serialized() == reply_str);
}

void test_reply_parser2()
{
    std::string reply_str = "227 Entering Passive Mode (10,2,8,240,7,166).\r\n";
    auto parser = FTP::ReplyParser();
    std::vector<uint8_t> segment(reply_str.begin(), reply_str.end());

    parser.process_segment(segment);

    auto replys = parser.replys();
    assert(replys.size() == 1);
    auto &reply = replys[0].get();
    assert(reply.code() == "227");
    assert(reply.spacing1() == " ");
    assert(reply.message() == "Entering Passive Mode (10,2,8,240,7,166).");
    assert(reply.lineending() == "\r\n");
    assert(reply.serialized() == reply_str);
}

void test_reply_parser3()
{
    std::string reply_str1 = "125 Data connection already open; Transfer starting.\r\n";
    std::string reply_str2 = "226 Transfer complete.\r\n";
    auto parser = FTP::ReplyParser();
    std::vector<uint8_t> segment1(reply_str1.begin(), reply_str1.end());
    std::vector<uint8_t> segment2(reply_str2.begin(), reply_str2.end());
    parser.process_segment(segment1);

    parser.process_segment(segment2);

    auto replys = parser.replys();
    assert(replys.size() == 2);
    auto &reply = replys[1].get();
    assert(reply.code() == "226");
    assert(reply.spacing1() == " ");
    assert(reply.message() == "Transfer complete.");
    assert(reply.lineending() == "\r\n");
    assert(reply.serialized() == reply_str2);
}

void test_reply_offsets()
{
    std::string reply_str1 = "100 message 1.\r\n";
    std::string reply_str2 = "200 message 2.\r\n";
    std::string reply_str3 = "300 message 3.\r\n";
    auto parser = FTP::ReplyParser();
    std::vector<uint8_t> segment1(reply_str1.begin(), reply_str1.end());
    std::vector<uint8_t> segment2(reply_str2.begin(), reply_str2.end());
    std::vector<uint8_t> segment3(reply_str3.begin(), reply_str3.end());
    parser.process_segment(segment1);
    parser.process_segment(segment2);
    parser.process_segment(segment3);

    auto replys = parser.replys();
    assert(replys.size() == 3);
    assert(replys[0].get().offset == 0);
    assert(replys[1].get().offset == 16);
    assert(replys[2].get().offset == 32);
}

void test_request_offsets()
{
    std::string request_str1 = "CMD1 args1.\r\n";
    std::string request_str2 = "CMD2 args2.\r\n";
    std::string request_str3 = "CMD3 args3.\r\n";
    auto parser = FTP::RequestParser();
    std::vector<uint8_t> segment1(request_str1.begin(), request_str1.end());
    std::vector<uint8_t> segment2(request_str2.begin(), request_str2.end());
    std::vector<uint8_t> segment3(request_str3.begin(), request_str3.end());
    parser.process_segment(segment1);
    parser.process_segment(segment2);
    parser.process_segment(segment3);

    auto requests = parser.requests();
    assert(requests.size() == 3);
    assert(requests[0].get().offset == 0);
    assert(requests[1].get().offset == 13);
    assert(requests[2].get().offset == 26);
}


int main(int argc, char** argv)
{
    test_request_parser1();
    test_request_parser2();
    test_request_parser3();
    test_reply_parser1();
    test_reply_parser2();
    test_reply_parser3();
    test_reply_offsets();
    test_request_offsets();
    exit(0);
}
