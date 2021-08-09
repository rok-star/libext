#pragma once

#include <libext/core/array.hpp>

namespace ext {
namespace unicode {

uint32_t upper(uint32_t codepoint);
uint32_t lower(uint32_t codepoint);
bool whitespace(uint32_t codepoint);
bool digital(uint32_t codepoint);

template<typename T>
class reader {
private:
	ext::array<T> const* _data;
	int64_t _cursor;
	int64_t _index;
	int64_t _size;
	int64_t _position;
	uint32_t _codepoint;
public:
	reader(ext::array<T> const& data);
	reader(ext::unicode::reader<T> const& reader) = delete;
	reader(ext::unicode::reader<T> && reader) = delete;
	ext::unicode::reader<T>& operator=(ext::unicode::reader<T> const& reader) = delete;
	ext::unicode::reader<T>& operator=(ext::unicode::reader<T> && reader) = delete;
	int64_t const& index() const;
	int64_t const& size() const;
	int64_t const& position() const;
	uint32_t const& codepoint() const;
	bool next();
};

template<typename T>
class writer {
private:
	ext::array<uint32_t> const* _codepoints;
	ext::array<T> _data;
	uint32_t _codepoint;
	int64_t _index;
public:
	writer(ext::array<uint32_t> const& codepoints);
	ext::array<T> const& data() const;
	uint32_t const& codepoint() const;
	int64_t const& index() const;
	bool next();
};

template<typename T>
inline reader<T>::reader(ext::array<T> const& data)
	: _data(&data)
	, _cursor(0)
	, _index(-1)
	, _size(0)
	, _position(-1)
	, _codepoint(0) {}

template<typename T>
inline int64_t const& reader<T>::index() const {
	return _index;
}

template<typename T>
inline int64_t const& reader<T>::size() const {
	return _size;
}

template<typename T>
inline int64_t const& reader<T>::position() const {
	return _position;
}

template<typename T>
inline uint32_t const& reader<T>::codepoint() const {
	return _codepoint;
}

template<typename T>
inline bool reader<T>::next() {
	T const* data = (_data->data() + _cursor);
	int64_t size = (_data->size() - _cursor);
	int64_t read = 0;

	if (size == 0) {
		return false;
	}

	if constexpr (sizeof(T) == 1) {
		if (data[0] == 0x0) {
	        return false;
	    } else if ((uint8_t)data[0] <= 0x7F) {
	        if (size < 1) return false;
	        _codepoint = (uint8_t)data[0];
	        read = 1;
	    } else if ((uint8_t)data[0] <= 0xDF) {
	        if (size < 2) return false;
	        _codepoint = 0;
	        _codepoint |= ((uint8_t)data[0] & 037) << 6;
	        _codepoint |= ((uint8_t)data[1] & 077);
	        read = 2;
	    } else if ((uint8_t)data[0] <= 0xEF) {
	        if (size < 3) return false;
	        _codepoint = 0;
	        _codepoint |= ((uint8_t)data[0] & 017) << 12;
	        _codepoint |= ((uint8_t)data[1] & 077) << 6;
	        _codepoint |= ((uint8_t)data[2] & 077);
	        read = 3;
	    } else if ((uint8_t)data[0] <= 0xF7) {
	        if (size < 4) return false;
	        _codepoint = 0;
	        _codepoint |= ((uint8_t)data[0] & 007) << 18;
	        _codepoint |= ((uint8_t)data[1] & 077) << 12;
	        _codepoint |= ((uint8_t)data[2] & 077) << 6;
	        _codepoint |= ((uint8_t)data[3] & 077);
	        read = 4;
	    }
	} else if (sizeof(T) == 2) {
	    if ((data[0] < 0xD800)
	    || (data[0] > 0xDFFF)) {
	        if (size < 1) return false;
	        _codepoint = (uint32_t)data[0];
	        read = 1;
	    } else {
	        if (size < 2) return false;
	        _codepoint = 0;
	        _codepoint |= (data[0] & 0x3FF) << 10;
	        _codepoint |= data[1] & 0x3FF;
	        _codepoint |= 0x10000;
	        read = 2;
	    }
	} else if (sizeof(T) == 4) {
		_codepoint = (uint32_t)data[0];
		read = 1;
	} else {
		return false;
	}

    if ((_codepoint >= 0xD800)
    && (_codepoint <= 0xDFFF)) {
		_codepoint = 0;
        return false;
    }

	_position = _cursor;
    _index += 1;
	_size = read;
	_cursor += read;

    return (read > 0);
}

template<typename T>
inline writer<T>::writer(ext::array<uint32_t> const& codepoints)
	: _codepoints(&codepoints)
	, _data(ext::array<T>::with_capacity(4))
	, _codepoint(0)
	, _index(-1) {}

template<typename T>
inline ext::array<T> const& writer<T>::data() const {
	return _data;
}

template<typename T>
inline uint32_t const& writer<T>::codepoint() const {
	return _codepoint;
}

template<typename T>
inline int64_t const& writer<T>::index() const {
	return _index;
}

template<typename T>
inline bool writer<T>::next() {
	if (_index == (_codepoints->size() - 1)) {
		return false;
	}

	int64_t size = 0;
	int64_t cursor = (_index + 1);
	uint32_t codepoint = (*_codepoints)[cursor];
	T string[4] = { 0, 0, 0, 0 };

	if constexpr (sizeof(T) == 1) {
		if (codepoint >= 0xD800 && codepoint <= 0xDFFF) {
			return false;
		} else if (codepoint <= 0x7F) {
			string[0] = (char)codepoint;
			size = 1;
		} else if (codepoint <= 0x7FF) {
			string[0] = ((codepoint >> 6) & 037) | 0300;
			string[1] = ((codepoint & 077) | 0200);
			size = 2;
		} else if (codepoint <= 0xFFFF) {
			string[0] = ((codepoint >> 12) & 017) | 0340;
			string[1] = ((codepoint >> 6) & 077) | 0200;
			string[2] = ((codepoint & 077) | 0200);
			size = 3;
		} else if (codepoint <= 0x10FFFF) {
			string[0] = ((codepoint >> 18) & 070) | 0360;
			string[1] = ((codepoint >> 12) & 077) | 0200;
			string[2] = ((codepoint >> 6) & 077) | 0200;
			string[3] = ((codepoint & 077) | 0200);
			size = 4;
		} else {
			return false;
		}
	} else if (sizeof(T) == 2) {
		if (codepoint >= 0xD800 && codepoint <= 0xDFFF) {
			return false;
		} else if (codepoint <= 0xFFFF) {
			string[0] = (uint16_t)codepoint;
			size = 1;
		} else if (codepoint <= 0x10FFFF) {
			codepoint &= 0xFFFF;
			string[0] = (uint16_t)((codepoint >> 10) | 0xD800);
			string[1] = (codepoint & 0x3FF) | 0xDC00;
			size = 2;
		} else {
			return false;
		}
	} else if (sizeof(T) == 4) {
		string[0] = codepoint;
		size = 1;
	} else {
		return false;
	}

	_index = cursor;
	_codepoint = codepoint;
	_data.clear();
	for (int64_t i = 0; i < size; i++) {
		_data.push(string[i]);
	}

	return true;
}

} /* namespace unicode */
} /* namespace ext */