#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include <tuple>
#include <string>
#include <regex>

namespace m2 {
    namespace server {

        class request_parser {
        public:
            request_parser() {

            }

            template<typename InputIterator>
            request parse(InputIterator begin, InputIterator end) {
                return request();
            }

        private:
        };

    } // namespace server
} // namespace m2

#endif // REQUEST_PARSER_HPP