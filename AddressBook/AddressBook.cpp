#include"AddressBook.h"

using namespace std;

string Address::getFirstName() const{
	return FirstName;
}
string Address::getLastName() const {
	return LastName;
}

const vector<string>& Address::getTelList() const {
	return telList;
}

const vector<string>& Address::getEmailList() const {
	return emailList;
}

Address& Address::setFirstName(string fname) {
	if (inBook) throw "Unable to modify the data in book directly";
	FirstName = fname;
	return *this;
}

Address& Address::setLastName(string lname) {
	if (inBook) throw "Unable to modify the data in book directly";
	LastName = lname;
	return *this;
}

Address& Address::addTel(string _tel) {
	if (inBook) throw "Unable to modify the data in book directly";
	telList.push_back(_tel);
	return *this;
}

Address& Address::addEmail(string _email) {
	if (inBook) throw "Unable to modify the data in book directly";
	emailList.push_back(_email);
	return *this;
}

Address& Address::deleteTel(string _tel) {
	if (inBook) throw "Unable to modify the data in book directly";
	telList.erase(find(telList.begin(), telList.end(), _tel));
	return *this;
}

Address& Address::deleteEmail(string _email) {
	if (inBook) throw "Unable to modify the data in book directly";
	emailList.erase(find(emailList.begin(), emailList.end(), _email));
	return *this;
}


AddressBook::~AddressBook(){
	addressList.clear();
	nameMap.clear();
	telMap.clear();
	emailMap.clear();
}
AddressList::iterator AddressBook::begin() {
	return addressList.begin();
}

AddressList::iterator AddressBook::end() {
	return addressList.end();
}

typedef std::multimap<std::string, AddressList::iterator> StringMap;
AddressBook::StringMapRange AddressBook::nameEqualRange(string FirstName,string LastName) {
	return nameMap.equal_range(FirstName + LastName);
}

AddressBook::StringMapRange AddressBook::telEqualRange(string _tel) {
    return telMap.equal_range(_tel);
}

AddressBook::StringMapRange AddressBook::emailEqualRange(string _email) {
	return emailMap.equal_range(_email);

}

AddressList::iterator AddressBook::addAddress(const Address& _new) {
	addressList.push_back(Address());
	auto tail = addressList.end();
	tail--;
	setNameFor(tail, _new.FirstName, _new.LastName);
	for (auto it = _new.telList.begin(); it != _new.telList.end(); it++) {
		addTelFor(tail, *it);
	}
	for (auto it = _new.emailList.begin(); it != _new.emailList.end(); it++) {
		addEmailFor(tail, *it);
	}
	tail->inBook = true;
	return tail;
}

AddressBook& AddressBook::deleteAddress(AddressList::iterator pos) {
	nameMap.erase(multiFind(nameMap,
							make_pair(pos->FirstName + pos->LastName, pos)));
	for (auto it = pos->telList.begin(); it != pos->telList.end(); it++) {
		delTelOf(pos, *it);
	}
	for (auto it = pos->emailList.begin(); it != pos->emailList.end(); it++) {
		delEmailOf(pos, *it);
	}
	addressList.erase(pos);
	return *this;
}


std::multimap<std::string, AddressList::iterator>::const_iterator AddressBook::multiFind(const std::multimap<std::string, AddressList::iterator>& _map,
	const std::pair< std::string, AddressList::iterator> _pair) {
	for (auto it=_map.lower_bound(_pair.first); it!=_map.end() && it->first == _pair.first; it++) {
		if (it->second == _pair.second) {
			return it;
		}
	}
	return _map.end();
}
AddressBook& AddressBook::setNameFor(AddressList::iterator pos, string FirstName, string LastName) {
	auto it = multiFind(nameMap, make_pair(FirstName + LastName, pos));
	if(it!=nameMap.end()) nameMap.erase(it);
	pos->setFirstName(FirstName).setLastName(LastName);
	nameMap.insert(make_pair(FirstName + LastName, pos));

	return *this;
}

AddressBook& AddressBook::addTelFor(AddressList::iterator pos, string _tel) {
	if (multiFind(telMap, make_pair(_tel, pos)) == telMap.end()) {
		telMap.insert(make_pair(_tel, pos));
	}
	pos->telList.push_back(_tel);
	return *this;
}

AddressBook& AddressBook::addEmailFor(AddressList::iterator pos, string _email) {
	if (multiFind(emailMap, make_pair(_email, pos)) == emailMap.end()) {
		emailMap.insert(make_pair(_email, pos));
	}
	pos->emailList.push_back(_email);
	return *this;
}


AddressBook& AddressBook::delTelOf(AddressList::iterator pos, std::string _tel) {
	auto it = multiFind(telMap, make_pair(_tel, pos));
	if(it!=telMap.end()) telMap.erase(it);
	auto &telList = pos->telList;
	telList.erase(find(telList.begin(), telList.end(), _tel));
	return *this;
}

AddressBook& AddressBook::delEmailOf(AddressList::iterator pos, std::string _email) {
	auto it = multiFind(emailMap, make_pair(_email, pos));
	if (it != emailMap.end()) emailMap.erase(it);
	auto& emailList = pos->emailList;
	emailList.erase(find(emailList.begin(), emailList.end(), _email));
	return *this;
}