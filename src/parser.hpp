#pragma once

#include <libext/string.hpp>

namespace ext {

struct parser_number_options {
    bool E;
    bool sign;
    bool spaces;
    bool precision;
    char decimal_separator;
    char thousands_separator;
};

class parser {
private:
public:
    parser(ext::string const& string);
    bool end() const;
    bool seek(int64_t delta);
    bool read_line(ext::string& out);
    bool read_until(ext::string const& until, ext::string& out);
    bool read_exact(ext::string const& exact);
    bool read_string(ext::string& out);
    bool read_quoted(char quote, ext::string& out);
    bool read_whitespace(int64_t& out);
    bool read_number(ext::parser_number_options const& options, double& out);
    bool peek_line(ext::string& out);
    bool peek_until(ext::string const& until, ext::string& out);
    bool peek_exact(ext::string const& exact);
    bool peek_string(ext::string& out);
    bool peek_quoted(char quote, ext::string& out);
    bool peek_whitespace(int64_t& out);
    bool peek_number(ext::parser_number_options const& options, double& out);
    void skip_whitespace();
};

} /* namespace ext */