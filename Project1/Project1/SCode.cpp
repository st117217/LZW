#include "SCode.h"
#include <algorithm>

SCode::SCode() : _array(nullptr), _length(0), _capacity(0) {}

SCode::SCode(int initCapacity) : _length(0), _capacity(initCapacity)
{
    _array = new int[_capacity];
}

SCode::SCode(const SCode& other) : _length(other._length), _capacity(other._capacity)
{
    _array = new int[_capacity];
    std::copy(other._array, other._array + _length, _array);
}

SCode::SCode(SCode&& other) noexcept : _array(other._array), _length(other._length), _capacity(other._capacity)
{
    other._array = nullptr;
    other._length = 0;
    other._capacity = 0;
}

SCode::~SCode()
{
    delete[] _array;
}

void SCode::pushBack(int value)
{
    if (_length == _capacity) {
        resize(_capacity == 0 ? 1 : _capacity * 2);
    }
    _array[_length++] = value;
}

int SCode::size() const
{
    return _length;
}

int& SCode::operator[](int index)
{
    return _array[index];
}

int SCode::operator[](int index) const
{
    return _array[index];
}

bool SCode::operator==(const SCode& other) const
{
    if (_length != other._length) {
        return false;
    }
    for (int i = 0; i < _length; ++i) {
        if (_array[i] != other._array[i]) {
            return false;
        }
    }
    return true;
}

SCode& SCode::operator=(const SCode& other)
{
    if (this != &other) {
        int* newArray = new int[other._capacity];
        std::copy(other._array, other._array + other._length, newArray);
        delete[] _array;
        _array = newArray;
        _length = other._length;
        _capacity = other._capacity;
    }
    return *this;
}

SCode& SCode::operator=(SCode&& other) noexcept
{
    if (this != &other) {
        delete[] _array;
        _array = other._array;
        _length = other._length;
        _capacity = other._capacity;
        other._array = nullptr;
        other._length = 0;
        other._capacity = 0;
    }
    return *this;
}

void SCode::resize(int newCapacity)
{
    int* newArray = new int[newCapacity];
    std::copy(_array, _array + _length, newArray);
    delete[] _array;
    _array = newArray;
    _capacity = newCapacity;
}
