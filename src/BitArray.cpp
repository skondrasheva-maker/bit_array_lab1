#include "BitArray.h"
#include <algorithm>
#include <stdexcept>

int BitArray::calculate_required_blocks(int num_bits) {
	if (num_bits <= 0) {
		return 0;
	}
	return (num_bits + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK; //округление вверх
}

BitArray::BitArray() {
	data_ = nullptr;
	num_bits_ = 0;
	capacity_blocks_ = 0;
}

BitArray::~BitArray() {
	delete[] data_;
}

BitArray::BitArray(int num_bits, unsigned long value) {
    num_bits_ = num_bits;
    capacity_blocks_ = calculate_required_blocks(num_bits);

    if (capacity_blocks_ > 0) {
        data_ = new BlockType[capacity_blocks_];
        for (int i = 0; i < capacity_blocks_; ++i) {
            data_[i] = 0;
        }
        data_[0] = value;
    }
    else {
        data_ = nullptr;
    }
	trim_unused_bits();
}

void BitArray::trim_unused_bits() {
	if (num_bits_ == 0 || data_ == nullptr) {
		return;
	}
	int last_block_index = (num_bits_ - 1) / BITS_PER_BLOCK;
	int bits_in_last_block = num_bits_ % BITS_PER_BLOCK;
	if (bits_in_last_block != 0) {
		BlockType mask = (static_cast<BlockType>(1) << bits_in_last_block) - 1;
		data_[last_block_index] &= mask;
	}

}

BitArray::BitArray(const BitArray& b) {
	num_bits_ = b.num_bits_;
	capacity_blocks_ = b.capacity_blocks_;
	if (capacity_blocks_ > 0) {
		data_ = new BlockType[capacity_blocks_];
		std::copy(b.data_, b.data_ + capacity_blocks_, data_);
	}
	else {
		data_ = nullptr;
	}
}

void BitArray::swap(BitArray& b) {
	std::swap(data_, b.data_);
	std::swap(num_bits_, b.num_bits_);
	std::swap(capacity_blocks_, b.capacity_blocks_);
}

BitArray& BitArray::operator=(const BitArray& b) {
	if (this != &b) {
		BitArray temp(b);
		this->swap(temp);
	}
	return *this;
}

int BitArray::size() const{
	return num_bits_;
}

bool BitArray::empty() const{
	return num_bits_ == 0;
}

bool BitArray::operator[](int i) const {
	if (i < 0 || i >= num_bits_) {
		throw std::out_of_range("Bit index out of range");
	}
	int block_index = i / BITS_PER_BLOCK;
	int bit_offset = i % BITS_PER_BLOCK;
	return (data_[block_index] >> bit_offset) & 1;
}

void BitArray::clear() {
	delete[] data_;
	data_ = nullptr;
	num_bits_ = 0;
	capacity_blocks_ = 0;
}

void BitArray::push_back(bool bit) {
	int new_num_bits = num_bits_ + 1;
	int new_capacity_blocks_ = calculate_required_blocks(new_num_bits);
	if (new_capacity_blocks_ > capacity_blocks_) {
		BlockType* new_data = new BlockType[new_capacity_blocks_];
		for (int i = 0; i < capacity_blocks_; ++i) {
			new_data[i] = data_[i];
		}
		for (int i = capacity_blocks_; i < new_capacity_blocks_; ++i) {
			new_data[i] = 0;
		}
		delete[] data_;
		data_ = new_data;
		capacity_blocks_ = new_capacity_blocks_;
	}
	num_bits_ = new_num_bits;
	if (bit) {
		int last_block = (num_bits_ - 1) / BITS_PER_BLOCK;
		int bit_offset = (num_bits_ - 1) % BITS_PER_BLOCK;
		data_[last_block] |= (static_cast<BlockType>(1) << bit_offset);
	}
}

void BitArray::resize(int num_bits, bool value) {
	if (num_bits < 0) {
		throw std::invalid_argument("Negative size is not allowed");
	}
	if (num_bits == num_bits_) {
		return;
	}
	if (num_bits < num_bits_) {
		num_bits_ = num_bits;
	}
	else {
		int new_capacity = calculate_required_blocks(num_bits);
		if (new_capacity > capacity_blocks_) {
			BlockType* new_data = new BlockType[new_capacity];
			for (int i = 0; i < capacity_blocks_; ++i)
				new_data[i] = data_[i];
			BlockType fill_value;
			if (value) {
				fill_value = ~static_cast<BlockType>(0);
			}
			else {
				fill_value = 0;
			}
			for (int i = capacity_blocks_; i < new_capacity; ++i) {
				new_data[i] = fill_value;
			}
			delete[] data_;
			data_ = new_data;
			capacity_blocks_ = new_capacity;
		}
		else {
			BlockType fill_value;
			if (value) {
				fill_value = ~static_cast<BlockType>(0);
			}
			else {
				fill_value = 0;
			}
			int start_bit = num_bits_;
			for (int i = start_bit; i < num_bits; ++i) {
				int block = i / BITS_PER_BLOCK;
				int offset = i % BITS_PER_BLOCK;
				if (value) {
					data_[block] |= (static_cast<BlockType>(1) << offset);
				}
				else {
					data_[block] &= ~(static_cast<BlockType>(1) << offset);
				}
			}

		}
		num_bits_ = num_bits;
		trim_unused_bits();
	}
}