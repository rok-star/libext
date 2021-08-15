#include <libext/core/date.hpp>

namespace ext {

datetime::datetime()
    : _year(0)
    , _month(0)
    , _date(0)
    , _day(0)
    , _hour(0)
    , _minute(0)
    , _second(0)
    , _millisecond(0)
    , _time(0) {

    ;
}

datetime::datetime(double time)
    : _year(0)
    , _month(0)
    , _date(0)
    , _day(0)
    , _hour(0)
    , _minute(0)
    , _second(0)
    , _millisecond(0)
    , _time(0) {

    ;
}

datetime::datetime(ext::datetime const& datetime)
    : _year(datetime._year)
    , _month(datetime._month)
    , _date(datetime._date)
    , _day(datetime._day)
    , _hour(datetime._hour)
    , _minute(datetime._minute)
    , _second(datetime._second)
    , _millisecond(datetime._millisecond)
    , _time(datetime._time) {}

ext::datetime& datetime::operator=(ext::datetime const& datetime) {
    _year = datetime._year;
    _month = datetime._month;
    _date = datetime._date;
    _day = datetime._day;
    _hour = datetime._hour;
    _minute = datetime._minute;
    _second = datetime._second;
    _millisecond = datetime._millisecond;
    _time = datetime._time;
    return *this;
}

bool datetime::operator==(ext::datetime const& datetime) const {
    return (_year == datetime._year)
        && (_month == datetime._month)
        && (_date == datetime._date)
        && (_day == datetime._day)
        && (_hour == datetime._hour)
        && (_minute == datetime._minute)
        && (_second == datetime._second)
        && (_millisecond == datetime._millisecond)
        && (_time == datetime._time);
}

bool datetime::operator!=(ext::datetime const& datetime) const {
    return !operator==(datetime);
}

int64_t const& datetime::year() const {
    return _year;
}

int64_t const& datetime::month() const {
    return _month;
}

int64_t const& datetime::date() const {
    return _date;
}

int64_t const& datetime::day() const {
    return _day;
}

int64_t const& datetime::hour() const {
    return _hour;
}

int64_t const& datetime::minute() const {
    return _minute;
}

int64_t const& datetime::second() const {
    return _second;
}

int64_t const& datetime::millisecond() const {
    return _millisecond;
}

double const& datetime::time() const {
    return _time;
}

ext::datetime datetime::local() const {
    return {};
}

ext::datetime datetime::add(int64_t num, ext::datetime_part const& part) const {
    return {};
}

ext::datetime datetime::subtract(int64_t num, ext::datetime_part const& part) const {
    return {};
}

} /* namespace ext */