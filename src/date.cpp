#include <libext/date.hpp>

namespace ext {

ext::datetime::datetime()
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

ext::datetime::datetime(double time)
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

ext::datetime::datetime(ext::datetime const& datetime)
    : _year(datetime._year)
    , _month(datetime._month)
    , _date(datetime._date)
    , _day(datetime._day)
    , _hour(datetime._hour)
    , _minute(datetime._minute)
    , _second(datetime._second)
    , _millisecond(datetime._millisecond)
    , _time(datetime._time) {}

ext::datetime& ext::datetime::operator=(ext::datetime const& datetime) {
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

bool ext::datetime::operator==(ext::datetime const& datetime) const {
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

bool ext::datetime::operator!=(ext::datetime const& datetime) const {
    return !operator==(datetime);
}

int64_t const& ext::datetime::year() const {
    return _year;
}

int64_t const& ext::datetime::month() const {
    return _month;
}

int64_t const& ext::datetime::date() const {
    return _date;
}

int64_t const& ext::datetime::day() const {
    return _day;
}

int64_t const& ext::datetime::hour() const {
    return _hour;
}

int64_t const& ext::datetime::minute() const {
    return _minute;
}

int64_t const& ext::datetime::second() const {
    return _second;
}

int64_t const& ext::datetime::millisecond() const {
    return _millisecond;
}

double const& ext::datetime::time() const {
    return _time;
}

ext::datetime ext::datetime::local() const {
    return {};
}

ext::datetime ext::datetime::add(int64_t num, ext::datetime_part const& part) const {
    return {};
}

ext::datetime ext::datetime::subtract(int64_t num, ext::datetime_part const& part) const {
    return {};
}

} /* namespace ext */