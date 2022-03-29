#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H
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
	AddressBook* book; //��¼����ͨѶ¼
public:
	Address() : book(nullptr) {}
	Address(std::string fname, std::string lname)
		:FirstName(fname), LastName(lname), book(nullptr) {};
	~Address() {};  //ʹ��STL���������ڴ�
	std::string getFirstName() const;
	std::string getLastName() const;
	const std::vector<std::string>& getTelList() const;
	const std::vector<std::string>& getEmailList() const;
	Address& setName(std::string fname, std::string lname);
	Address& addTel(std::string _tel);
	Address& addEmail(std::string _email);
	Address& deleteTel(std::string _tel);
	Address& deleteEmail(std::string _email);
};

typedef std::list<Address> AddressList;
class AddressBook {
public:
	typedef std::multimap<std::string, Address*> StringMap;
	typedef std::pair<StringMap::iterator, StringMap::iterator> StringMapRange;
	AddressBook() {};
	~AddressBook() {}; //ʹ��STL���������ڴ�
	AddressList::iterator begin();
	AddressList::iterator end();
	StringMapRange nameEqualRange(std::string FirstName, std::string LastName);  //������ʹ�ÿ���ӳ�䣬�ʲ��Һ������ص��Ƿ�Χ
	StringMapRange telEqualRange(std::string tel);
	StringMapRange emailEqualRange(std::string email);
	const StringMap& getNameMap() { return nameMap; }
	const StringMap& getTelMap() { return telMap; }
	const StringMap& getEmailMap() { return emailMap; }
	AddressList::iterator addAddress(const Address& _new);
	AddressBook& deleteAddress(AddressList::iterator pos);
	AddressBook& deleteAddress(Address* pos);
private:
	friend Address;      //Ԫ�ظı���Adress�෽��֧�֣���ͬʱά��AdressBook������������Ϊ��Ԫ��
	AddressList addressList;  //ʹ��std::list��Ϊ������ͬʱ��multimapά�������ӿ�����
	std::map<Address*, AddressList::iterator> pointerConverter;  //STL��֧�ֽ�ָ��ת��Ϊlist�������������ά��ָ��-������ӳ���
	StringMap nameMap;
	StringMap telMap;
	StringMap emailMap;
	static StringMap::const_iterator multiFind(const StringMap& _map,  
		const std::pair< std::string, Address*> _pair);   //�ڿ���ӳ���в����ض���-ֵ��
};

#endif