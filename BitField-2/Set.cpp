#include "Set.h"



Set::Set(size_t mp) : _maxPower(mp), _bitField(mp) {

}
Set::Set(const Set &s) : _maxPower(s._maxPower), _bitField(s._bitField){ 

} 
Set::Set(const BitField &bf) : _maxPower( bf.GetLength() ), _bitField(bf){ 

}

//Set::operator  BitField ()     {  BitField temp(this->_bitField); return temp; }

size_t Set::GetMaxPower() const{
    return _maxPower;
}    
void Set::InsElem(const uint64_t Elem){
    _bitField.SetBit(Elem);
}
void Set::DelElem(const uint64_t Elem){
    _bitField.ClrBit(Elem);
}
bool Set::IsMember(const uint64_t Elem) const{
    return _bitField.GetBit(Elem);
}


bool Set::operator== (const Set &s) const{
    return (s._bitField==_bitField);
}
bool Set::operator!= (const Set &s) const{
    return (1 - (_bitField == s._bitField));
}
Set& Set::operator=(const Set &s){
    _bitField=s._bitField; _maxPower=s.GetMaxPower();
    return *this;
}
Set Set::operator+ (const uint64_t Elem){
    Set res(*this); res.InsElem(Elem); return res;
    //return *this;
}
                                  
Set Set::operator- (const uint64_t Elem){
    Set res(*this); res.DelElem(Elem); return res;
    //return *this;
}
                                   
Set Set::operator+ (const Set &s){
    _bitField=_bitField | s._bitField;
    return *this;
}
Set Set::operator* (const Set &s){
    _bitField=_bitField & s._bitField;
    return *this;
}
Set Set::operator~ (){
    Set res( (~_bitField) );
    return res;
    //return *this;
}

istream& operator>>(istream& is, Set& tmp) {
    is >> tmp._maxPower;
    is >> tmp._bitField;
    return is;
}

ostream& operator<<  (ostream &ostr, const Set &s)
{	
	ostr << "\n{";
	for (int i=0; i<s._bitField.GetLength(); i++)
		if (s._bitField.GetBit(i) ) ostr << i << " ";
	ostr << "}\n";
	return ostr;
}

vector<uint64_t> Set::GetPrimary() const {
    vector <uint64_t> res;
    unordered_set<int> used;
    size_t tmp = _maxPower;
    res.push_back(1);
    for (int i = 2; i < tmp + 1; i++) {

        if (used.find(i) != used.end()) continue;

        else {
            res.push_back(i);
            for (int j = i + 1; j < tmp + 1; j++)
                if (j % i == 0) used.insert(j);

        }
    }
    return res;
}