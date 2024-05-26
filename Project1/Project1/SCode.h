#pragma once

class SCode
{
public:
    SCode();
    SCode(int initCapacity);
    SCode(const SCode& other);
    SCode(SCode&& other) noexcept;
    ~SCode();

    void pushBack(int value);
    int size() const;
    int& operator[](int index);
    int operator[](int index) const;

    bool operator==(const SCode& other) const;
    SCode& operator=(const SCode& other);
    SCode& operator=(SCode&& other) noexcept;


private:
    int* _array;
    int _length;
    int _capacity;

    void resize(int newCapacity);
};



