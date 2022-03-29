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

Address& Address::setName(string fname,string lname) {
	if (book) {
		auto it = book->multiFind(book->nameMap, make_pair(FirstName + LastName, this));  //replace if existed
		if (it != book->nameMap.end()) book->nameMap.erase(it);
		book->nameMap.insert(make_pair(fname+lname, this)); 
		
	}
	FirstName = fname;
	LastName = lname;
	return *this;
}

Address& Address::addTel(string _tel) {
	telList.push_back(_tel);
	if (book) {
		if (AddressBook::multiFind(book->telMap, make_pair(_tel, this)) == book->telMap.end()) { //contiue if existed
			book->telMap.insert(make_pair(_tel, this)); 
		}
	}
	return *this;
}

Address& Address::addEmail(string _email) {
	emailList.push_back(_email);
	if (book) {
		if (AddressBook::multiFind(book->emailMap, make_pair(_email, this)) == book->emailMap.end()) { //contiue if existed
			book->emailMap.insert(make_pair(_email, this));
		}
	}
	return *this;
}

Address& Address::deleteTel(string _tel) {
	telList.erase(find(telList.begin(), telList.end(), _tel));
	if (book) {
		auto it = book->multiFind(book->telMap, make_pair(_tel, this));
		if (it != book->telMap.end()) book->telMap.erase(it);
	}
	return *this;
}

Address& Address::deleteEmail(string _email) {
	emailList.erase(find(emailList.begin(), emailList.end(), _email));
	if (book) {
		auto it = book->multiFind(book->emailMap, make_pair(_email, this));
		if (it != book->emailMap.end()) book->emailMap.erase(it);
	}
	return *this;
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
	tail->book = this;
	tail->setName(_new.FirstName, _new.LastName);
	for (auto it = _new.telList.begin(); it != _new.telList.end(); it++) {
		tail->addTel(*it);
	}
	for (auto it = _new.emailList.begin(); it != _new.emailList.end(); it++) {
		tail->addEmail(*it);
	}
	pointerConverter[&*tail] = tail;
	return tail;
}

AddressBook& AddressBook::deleteAddress(AddressList::iterator pos) {
	auto it = multiFind(nameMap,make_pair(pos->FirstName + pos->LastName, &*pos));
	if (it != nameMap.end()) nameMap.erase(it);
	while(!pos->telList.empty()){
		pos->deleteTel(pos->telList.back());
	}

	while (!pos->emailList.empty()) {
		pos->deleteEmail(pos->emailList.back());
	}
	pointerConverter.erase(&*pos);
	addressList.erase(pos);
	return *this;
}
AddressBook& AddressBook::deleteAddress(Address* pos) {
	return deleteAddress(pointerConverter[pos]);
}


std::multimap<std::string, Address*>::const_iterator AddressBook::multiFind(const std::multimap<std::string, Address*>& _map,
	const std::pair< std::string, Address*> _pair) {
	for (auto it=_map.lower_bound(_pair.first); it!=_map.end() && it->first == _pair.first; it++) {
		if (it->second == _pair.second) {
			return it;
		}
	}
	return _map.end();
}