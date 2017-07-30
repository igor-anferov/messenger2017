#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <vector>

namespace m2 {
    namespace server {

/// A request received from a client.
        struct request
        {
            enum STATE {
                indeterminate
            };
            STATE state_;
        };

    } // namespace server
} // namespace m2

#endif // REQUEST_HPP