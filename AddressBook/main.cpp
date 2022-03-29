#include<iostream>
#include"AddressBook.h"

using namespace std;
void printAddress(Address& address) {
	cout << "姓名: " << address.getFirstName() << ' ' << address.getLastName() << endl;
	cout << "  电话:";
	for (auto tel = address.getTelList().begin(); tel != address.getTelList().end(); tel++) {
		cout << *tel << "; ";
	}
	cout << endl;
	cout << "  邮箱:";
	for (auto email = address.getEmailList().begin(); email != address.getEmailList().end(); email++) {
		cout << *email << "; ";
	}
	cout << endl << endl;
}
void printBook(AddressBook& addressBook) {
	cout << "---------------------通讯录--------------------" << endl;
	for (auto it = addressBook.begin(); it != addressBook.end(); it++) {
		printAddress(*it);
	}
}
void printNameSortBook(AddressBook& addressBook){
	cout << "-----------------通讯录(按名字排序)-------------" << endl;
	auto nameMap = addressBook.getNameMap();
	for (auto it = nameMap.begin(); it != nameMap.end(); it++) {
		printAddress(*(it->second));
	}
}

int main() {
	AddressBook book;
	book.addAddress(Address("李", "华").addTel("1000000").addEmail("lihua@mail.com").addTel("13123213213"));
	auto Aka=book.addAddress(Address("Aka", "rin").addEmail("aka@go.com"));
	printBook(book);

	Aka->addTel("13123123");
	book.addAddress(Address("Misaka", "Mikoto").addEmail("aka@go.com"));
	book.nameEqualRange("Misaka", "Mikoto").first->second->addTel("1000000");  
	printBook(book);

	book.addAddress(Address("李", "华").addTel("20000").addEmail("lihua2@gmailcom").addEmail("cn@gov.cn"));

	cout << "-----------电话为1000000的联系人有:---------" << endl;
	AddressBook::StringMapRange range = book.telEqualRange("1000000");
	for (auto it = range.first; it != range.second; it++) {
		printAddress(*(it->second));
	}

	cout << "-----------删除李华的号码10000000-----------" << endl<<endl;
	book.nameEqualRange("李", "华").first->second->deleteTel("1000000");

	cout << "-----------电话为1000000的联系人有:---------" << endl;
	range = book.telEqualRange("1000000");
	for (auto it = range.first; it != range.second; it++) {
		printAddress(*(it->second));
	}
	cout << "-----------邮件为aka@go.com的联系人有:------" << endl;
	range = book.emailEqualRange("aka@go.com");
	for (auto it = range.first; it != range.second; it++) {
		printAddress(*(it->second));
	}
	cout << "------------名字为李华的联系人有:-----------" << endl;
	range = book.nameEqualRange("李", "华");
	for (auto it = range.first; it != range.second; it++) {
		printAddress(*(it->second));
	}
	
	printNameSortBook(book);

	cout << "--------------删除Aka rin-----------------" << endl << endl;
	book.deleteAddress(book.nameEqualRange("Aka", "rin").first->second);

	printNameSortBook(book);
	getchar();
	return 0;
}