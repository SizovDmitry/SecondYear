#include "Set.h"

Set::Set(size_t mp) : _maxPower(mp), _bitField(mp) {

}
Set::Set(const Set& s) : _maxPower(s._maxPower), _bitField(s._bitField) {

}
Set::Set(const BitField& bf) : _maxPower(bf.GetLength()), _bitField(bf) {

}


size_t Set::GetMaxPower() const {
    return _maxPower;
}

void Set::InsElem(const uint64_t Elem) {
    _bitField.SetBit(Elem);
}

void Set::DelElem(const uint64_t Elem) {
    _bitField.ClrBit(Elem);
}
bool Set::IsMember(const uint64_t Elem) const {
    return _bitField.GetBit(Elem);
}


bool Set::operator== (const Set& s) const {
    return (s._bitField == _bitField);
}
bool Set::operator!=(const Set& tmp) const {
    return !(_bitField == tmp._bitField);
}
Set& Set::operator=(const Set& s) {
    _bitField = s._bitField; _maxPower = s.GetMaxPower();
    return *this;
}
Set Set::operator+ (const uint64_t Elem) {
    Set res(*this); res.InsElem(Elem); return res;
}

Set Set::operator- (const uint64_t Elem) {
    Set res(*this); res.DelElem(Elem); return res;
}

Set Set::operator+ (const Set& s) {
    _bitField = _bitField | s._bitField;
    return *this;
}
Set Set::operator* (const Set& s) {
    _bitField = _bitField & s._bitField;
    return *this;
}

Set Set::operator~ () {
    Set res((~_bitField));
    return res;
}


std::vector<uint64_t> Set::GetPrimary() const {
    std::vector<uint64_t> res;
    if (_maxPower < 2) return res;

    res.push_back(1);
    std::vector<bool> is_used(_maxPower + 1, false);

    for (uint64_t i = 2; i < _maxPower; i++) {
        if (!is_used[i]) {
            res.push_back(i);
            for (uint64_t j = i * 2; j <= _maxPower; j += i) {
                is_used[j] = true;
            }
        }
    }

    return res;
}