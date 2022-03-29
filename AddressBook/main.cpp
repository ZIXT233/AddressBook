#include<iostream>
#include"AddressBook.h"

using namespace std;
void printAddress(Address& address) {
	cout << "����: " << address.getFirstName() << ' ' << address.getLastName() << endl;
	cout << "  �绰:";
	for (auto tel = address.getTelList().begin(); tel != address.getTelList().end(); tel++) {
		cout << *tel << "; ";
	}
	cout << endl;
	cout << "  ����:";
	for (auto email = address.getEmailList().begin(); email != address.getEmailList().end(); email++) {
		cout << *email << "; ";
	}
	cout << endl << endl;
}
void printBook(AddressBook& addressBook) {
	cout << "---------------------ͨѶ¼--------------------" << endl;
	for (auto it = addressBook.begin(); it != addressBook.end(); it++) {
		printAddress(*it);
	}
}
void printNameSortBook(AddressBook& addressBook){
	cout << "-----------------ͨѶ¼(����������)-------------" << endl;
	auto nameMap = addressBook.getNameMap();
	for (auto it = nameMap.begin(); it != nameMap.end(); it++) {
		printAddress(*(it->second));
	}
}

int main() {
	AddressBook book;
	book.addAddress(Address("��", "��").addTel("1000000").addEmail("lihua@mail.com").addTel("13123213213"));
	auto Aka=book.addAddress(Address("Aka", "rin").addEmail("aka@go.com"));
	printBook(book);

	Aka->addTel("13123123");
	book.addAddress(Address("Misaka", "Mikoto").addEmail("aka@go.com"));
	book.nameEqualRange("Misaka", "Mikoto").first->second->addTel("1000000");  
	printBook(book);

	book.addAddress(Address("��", "��").addTel("20000").addEmail("lihua2@gmailcom").addEmail("cn@gov.cn"));

	cout << "-----------�绰Ϊ1000000����ϵ����:---------" << endl;
	AddressBook::StringMapRange range = book.telEqualRange("1000000");
	for (auto it = range.first; it != range.second; it++) {
		printAddress(*(it->second));
	}

	cout << "-----------ɾ����ĺ���10000000-----------" << endl<<endl;
	book.nameEqualRange("��", "��").first->second->deleteTel("1000000");

	cout << "-----------�绰Ϊ1000000����ϵ����:---------" << endl;
	range = book.telEqualRange("1000000");
	for (auto it = range.first; it != range.second; it++) {
		printAddress(*(it->second));
	}
	cout << "-----------�ʼ�Ϊaka@go.com����ϵ����:------" << endl;
	range = book.emailEqualRange("aka@go.com");
	for (auto it = range.first; it != range.second; it++) {
		printAddress(*(it->second));
	}
	cout << "------------����Ϊ�����ϵ����:-----------" << endl;
	range = book.nameEqualRange("��", "��");
	for (auto it = range.first; it != range.second; it++) {
		printAddress(*(it->second));
	}
	
	printNameSortBook(book);

	cout << "--------------ɾ��Aka rin-----------------" << endl << endl;
	book.deleteAddress(book.nameEqualRange("Aka", "rin").first->second);

	printNameSortBook(book);
	getchar();
	return 0;
}