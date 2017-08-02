#include <iostream>
#include <boost/asio.hpp>
#include "server.h"

int main(int argc, char *argv[]) {
    try {
        std::string port;
        if (argc < 2) {
            std::cerr << "Enter port:" << std::endl;
            std::cin >> port;
        } else {
            port = argv[1];
        }

        m2::server::server s(argv[1]);

        s.run();
    }
    catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}