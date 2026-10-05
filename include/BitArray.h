#pragma once

#include <string>

class BitArray {
public:
    using BlockType = unsigned long;
    static constexpr int BITS_PER_BLOCK = static_cast<int>(sizeof(BlockType) * 8);

    BitArray();
    ~BitArray();
    explicit BitArray(int num_bits, unsigned long value = 0);
    BitArray(const BitArray& b);

    void swap(BitArray& b);
    BitArray& operator=(const BitArray& b);

    void resize(int num_bits, bool value = false);
    void clear();
    void push_back(bool bit);

    BitArray& operator&=(const BitArray& b);
    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);

    BitArray& operator<<=(int n);
    BitArray& operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;

    BitArray& set(int n, bool val = true);
    BitArray& set();
    BitArray& reset(int n);
    BitArray& reset();

    bool any() const;
    bool none() const;
    BitArray operator~() const;
    int count() const;

    bool operator[](int i) const;
    bool operator()(int i) const;

    int size() const;
    bool empty() const;

    std::string to_string() const;

private:
    BlockType* data_ = nullptr;
    int num_bits_ = 0;
    int capacity_blocks_ = 0;

    static int calculate_required_blocks(int num_bits);
    void trim_unused_bits();
};

bool operator==(const BitArray& a, const BitArray& b);
bool operator!=(const BitArray& a, const BitArray& b);
BitArray operator&(const BitArray& b1, const BitArray& b2);
BitArray operator|(const BitArray& b1, const BitArray& b2);
BitArray operator^(const BitArray& b1, const BitArray& b2);