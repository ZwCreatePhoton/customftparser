include_directories ("include")

add_library(CustomFTParserLib request.cpp request_parser.cpp reply.cpp reply_parser.cpp ../include/customftparser/token.h)
