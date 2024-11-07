#include "BitField.h"

const int min_bits=8*sizeof(int)-1,  max_bits=8*sizeof(int);

size_t BitField::GetMemIndex(size_t n) const{
    return ( n / max_bits );;
}
uint16_t BitField::GetMask(size_t n) const {
    return 1 << (n & min_bits);;
}

BitField::BitField(size_t len) {

}

BitField::BitField(const BitField& tmp) {

}

BitField& BitField::operator=(const BitField& tmp) {
    if (this == &tmp)  return *this;  //если присваиваем самому себе
	if (tmp._mem== NULL) //если присваиваем пустое поле
						{ delete _mem; _sizeBit=tmp._sizeBit; _memSize=tmp._memSize; return *this; }
	
	if (_memSize != tmp._memSize) //если разное количество элементов в массивах - пересоздаём
		{ 
			if (_mem != NULL) delete _mem;
			_memSize=tmp._memSize;
			_mem=new uint16_t[_memSize];
		}
	_sizeBit=tmp._sizeBit;
	for (int i=0; i<tmp._memSize; i++) _mem[i] = tmp._mem[i];
    return *this;
}
    
size_t BitField::GetLength() const {
    return _sizeBit;
}
void BitField::SetBit(size_t n) {
    if ( (n > -1) && (n < _sizeBit) ) 
			_mem[GetMemIndex(n)] |= GetMask(n);
}
void BitField::ClrBit(size_t n) {
    if ( (n > -1) && (n < _sizeBit) ) 
	     _mem[ GetMemIndex(n) ] &= ~GetMask(n);
}
uint8_t BitField::GetBit(size_t n) const {
    if ( (n > -1)&&(n < _sizeBit) )
		return (   ( (_mem[GetMemIndex(n)] & GetMask(n)) != 0  ) ? 1 : 0   );;
}
BitField BitField::operator|(const BitField& tmp) {
    int len = _sizeBit;
	if ( tmp._sizeBit > len ) { len = tmp._sizeBit; }

	BitField temp(len); 
	for (int i=0; i<_memSize; i++) temp._mem[i] = _mem[i];
	
	for ( int i=0; i < tmp._memSize; i++ ) temp._mem[i] |= tmp._mem[i];
	return temp;
}

BitField BitField::operator&(const BitField& tmp) {
    int len = _sizeBit;
	if ( tmp._sizeBit < len ) { len = tmp._sizeBit; }	 
	
	BitField temp(len);  memcpy(temp._mem, _mem, sizeof(temp._mem) ); 
	
	for (int i=0; i < temp._memSize; i++ )  temp._mem[i] &= tmp._mem[i];
	return temp;
}
BitField BitField::operator^(const BitField& tmp) {
    return *this;
}
bool BitField::operator==(const BitField& tmp) const{
    int res = 1;
	if ( _sizeBit != tmp._sizeBit ) res = 0;
		else
			for ( int i=0; i < _memSize; i++ )
				if ( _mem[i] != tmp._mem[i] ) { res = 0; break; }	
	return res;
}
BitField BitField::operator~(){
    BitField temp(_sizeBit);
	for (int i=0; i< temp._memSize; i++ ) temp._mem[i] = ~_mem[i];
	return temp;
}

istream& operator>>(istream& in, BitField& bf) {
    size_t sizeBit;
    in >> sizeBit;
    bf._sizeBit = sizeBit;
    bf._memSize = (sizeBit / (16 * (sizeof(uint16_t)))) + (sizeBit % (16 * sizeof(uint16_t)) != 0);
    bf._mem = new uint16_t[bf._memSize];
    uint64_t tmp;
    while (true) {
        in >> tmp;
        bf.SetBit(tmp);
    }
    return in;
}

ostream& operator<< (ostream &ostr, const BitField &bf)  
{   
	for (int i=0; i < bf._sizeBit; i++)
		ostr <<  bf.GetBit(i) << ' '; 
	return ostr;
}