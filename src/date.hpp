#pragma once

#include <libext/base.hpp>

namespace ext {

enum class date_part {
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
    ext::datetime add(int64_t num, ext::date_part const& part);
    ext::datetime subtract(int64_t num, ext::date_part const& part);
};

} /* namespace ext */