#include "BitField.h"

const int min_bits = 8 * sizeof(uint16_t) - 1;
const int max_bits = 8 * sizeof(uint16_t);

size_t BitField::GetMemIndex(size_t n) const {
	return n / max_bits;
}

uint16_t BitField::GetMask(size_t n) const {
	return 1 << (n & min_bits);
}

BitField::BitField(size_t sizeBit) : _sizeBit(sizeBit), _mem(nullptr) {
	if (_sizeBit == 0) {
		_memSize = 0;
		_mem = nullptr;
	}
	else {
		_memSize = (_sizeBit + (max_bits - 1)) / max_bits;
		_mem = new uint16_t[_memSize];
		for (size_t i = 0; i < _memSize; ++i) {
			_mem[i] = 0;
		}
	}
}

BitField::BitField(const BitField& tmp)
	: _sizeBit(tmp._sizeBit), _memSize(tmp._memSize), _mem(new uint16_t[tmp._memSize]) {

	for (size_t i = 0; i < _memSize; ++i) {
		_mem[i] = tmp._mem[i];
	}
}

BitField& BitField::operator=(const BitField& tmp) {
	if (this == &tmp)  return *this;
	if (tmp._mem == NULL)
	{
		delete _mem; _memSize = tmp._memSize; return *this;
	}

	if (_memSize != tmp._memSize)
	{
		if (_mem != NULL) delete _mem;
		_memSize = tmp._memSize;
		_mem = new uint16_t[_memSize];
	}
	_sizeBit = tmp._sizeBit;
	for (int i = 0; i < tmp._memSize; i++) _mem[i] = tmp._mem[i];
	return *this;
}

size_t BitField::GetLength() const {
	return _sizeBit;
}
void BitField::SetBit(size_t n) {
	if (n < _sizeBit)
		_mem[GetMemIndex(n)] |= GetMask(n); else throw "Error in bit access";
}

void BitField::ClrBit(size_t n) {
	if (n < _sizeBit)
		_mem[GetMemIndex(n)] &= (~GetMask(n)); else throw "Error in bit access";
}

uint8_t BitField::GetBit(size_t n) const {
	if (n < _sizeBit)
		return (((_mem[GetMemIndex(n)] & GetMask(n)) != 0) ? 1 : 0); else throw "Error in bit access";
}

BitField BitField::operator|(const BitField& tmp) {
	int len = (_sizeBit > tmp._sizeBit) ? _sizeBit : tmp._sizeBit;
	BitField temp(len);

	for (int i = 0; i < temp._memSize; i++) {
		temp._mem[i] = (i < _memSize ? _mem[i] : 0) | (i < tmp._memSize ? tmp._mem[i] : 0);
	}

	return temp;
}


BitField BitField::operator&(const BitField& tmp) {
	int resultSize = max(_sizeBit, tmp._sizeBit);
	BitField result(resultSize);
	int minSize = min(_sizeBit, tmp._sizeBit);
	for (int i = 0; i < minSize; i++) {
		result._mem[i] = _mem[i] & tmp._mem[i];
	}
	for (int i = minSize; i < result._memSize; i++) {
		result._mem[i] = 0;
	}
	return result;
}

BitField BitField::operator^(const BitField& tmp) {
	int resultSize = max(_sizeBit, tmp._sizeBit);
	BitField result(resultSize);
	int minSize = min(_sizeBit, tmp._sizeBit);
	for (int i = 0; i < minSize; i++) {
		result._mem[i] = _mem[i] ^ tmp._mem[i];
	}
	for (int i = minSize; i < _memSize; i++) {
		result._mem[i] = _mem[i];
	}
	for (int i = minSize; i < tmp._memSize; i++) {
		result._mem[i] = tmp._mem[i];
	}

	return result;
}

bool BitField::operator==(const BitField& tmp) const {
	int res = 1;
	if (_sizeBit != tmp._sizeBit) res = 0;
	else
		for (int i = 0; i < _memSize; i++)
			if (_mem[i] != tmp._mem[i]) { res = 0; break; }
	return res;
}
BitField BitField::operator~() {
	BitField result(_sizeBit);

	for (size_t i = 0; i < _memSize; i++) {
		result._mem[i] = ~_mem[i];
	}

	size_t bitsInLastElement = _sizeBit % max_bits; // Эта строка вычисляет, сколько бит используется в последнем элементе массива
	if (bitsInLastElement != 0) {
		uint16_t mask = GetMask(bitsInLastElement) - 1;
		result._mem[result.GetMemIndex(_sizeBit - 1)] &= mask;
	}

	return result;
}
