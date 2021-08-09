#pragma once

#include <libext/core/base.hpp>
#include <libext/core/string.hpp>
#include <libext/core/status.hpp>

namespace ext {

enum class datetime_part {
    year,
    month,
    week,
    day,
    hour,
    minute,
    second,
    millisecond
};

class datetime final {
private:
    int64_t _year;
    int64_t _month;
    int64_t _date;
    int64_t _day;
    int64_t _hour;
    int64_t _minute;
    int64_t _second;
    int64_t _millisecond;
    double _time;
public:
    datetime();
    datetime(double time);
    datetime(ext::datetime const& datetime);
    ext::datetime& operator=(ext::datetime const& datetime);
    bool operator==(ext::datetime const& datetime) const;
    bool operator!=(ext::datetime const& datetime) const;
    int64_t const& year() const;
    int64_t const& month() const;
    int64_t const& date() const;
    int64_t const& day() const;
    int64_t const& hour() const;
    int64_t const& minute() const;
    int64_t const& second() const;
    int64_t const& millisecond() const;
    double const& time() const;
    ext::datetime local() const;
    ext::datetime add(int64_t num, ext::datetime_part const& part) const;
    ext::datetime subtract(int64_t num, ext::datetime_part const& part) const;
    static ext::datetime parse(ext::string const& string, ext::status& status);
    static ext::datetime now();
};

} /* namespace ext */

inline constexpr double operator "" _ms(long double ms) {
    return ms;
}

inline constexpr double operator "" _sec(long double s) {
    return (s * 1000.0);
}

inline constexpr double operator "" _min(long double m) {
    return (m * 60.0 * 1000.0);
}