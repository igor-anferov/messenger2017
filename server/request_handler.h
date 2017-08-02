#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include <string>

namespace m2 {
    namespace server {

        struct reply;
        struct request;

        class request_handler {
        public:
            request_handler(const request_handler &) = delete;

            request_handler();

            request_handler &operator=(const request_handler &) = delete;

        private:
        };

    } // namespace server
} // namespace m2

#endif // REQUEST_HANDLER_HPP