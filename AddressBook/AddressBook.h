#include<map>
#include<string>
#include<vector>
#include<list>

class AddressBook;

class Address {
private:
	friend AddressBook;
	std::string FirstName, LastName;
	std::vector<std::string> telList;
	std::vector<std::string> emailList;
	bool inBook;
public:
	Address(): inBook(false){}
	Address(std::string fname, std::string lname)
		:FirstName(fname), LastName(lname),inBook(false) {};
	~Address() {};
	std::string getFirstName() const;
	std::string getLastName() const;
	const std::vector<std::string>& getTelList() const;
	const std::vector<std::string>& getEmailList() const;
	Address& setFirstName(std::string fname);
	Address& setLastName(std::string lname);
	Address& addTel(std::string _tel);
	Address& addEmail(std::string _email);
	Address& deleteTel(std::string _tel);
	Address& deleteEmail(std::string _email);
};

typedef std::list<Address> AddressList;

class AddressBook {
public:
	typedef std::multimap<std::string, AddressList::iterator> StringMap;
	typedef std::pair<StringMap::iterator, StringMap::iterator> StringMapRange;
	AddressBook() {};
	~AddressBook();
	AddressList::iterator begin();
	AddressList::iterator end();
	StringMapRange nameEqualRange(std::string FirstName, std::string LastName);
	StringMapRange telEqualRange(std::string tel);
	StringMapRange emailEqualRange(std::string email);
	const StringMap& getNameMap() { return nameMap; }
	const StringMap& getTelMap() { return telMap; }
	const StringMap& getEmailMap() { return emailMap; }
	AddressList::iterator addAddress(const Address& _new);
	AddressBook& deleteAddress(AddressList::iterator pos);

	AddressBook& setNameFor(AddressList::iterator pos, std::string FirstName, std::string LastName);
	AddressBook& addTelFor(AddressList::iterator pos, std::string _tel);
	AddressBook& addEmailFor(AddressList::iterator, std::string email);

	AddressBook& delTelOf(AddressList::iterator pos, std::string _tel);
	AddressBook& delEmailOf(AddressList::iterator pos, std::string _email);
private:
	AddressList addressList;
	StringMap nameMap;
	StringMap telMap;
	StringMap emailMap;
	static StringMap::const_iterator multiFind(const StringMap& _map,
		const std::pair< std::string, AddressList::iterator> _pair);
};