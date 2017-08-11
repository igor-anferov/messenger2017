#include "../stdafx.h"
#include "../include/server.h"

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <signal.h>

using namespace m2::server;

Server server;

void my_handler (int param)
{
    exit(1);
}

int main(int argc, char* argv[]) {
    using boost::lexical_cast;
    using boost::bad_lexical_cast;

    uint16_t port = 8282;
    if (argc > 1) {
        try {
            port = lexical_cast<uint16_t>(argv[1]);
        }
        catch (bad_lexical_cast&) {
            std::cout << "Error port argument! Use default - 8282" << std::endl;
        }
    }

    std::cout << "Connected to port = " << port << std::endl;

    signal (SIGINT, my_handler);

    server.start(port);

    return 0;
}