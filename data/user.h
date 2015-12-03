#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>
class User{
private:
	unsigned int id;
	std::string taggerId;
	std::string name;
	std::string address;
	std::string phone;
	bool exists = true;
	static unsigned int nextId;
public:
	std::string pwdHash;
	User();
	User(std::string name, std::string pwdHash, std::string address, std::string phone, std::string taggerId=0, unsigned int id = 0);
	User(std::string name, std::string address, std::string phone, std::string taggerId="NOT TAGGER", unsigned int id = 0) : User(name, ".", address, taggerId, id){}
	std::string getName();
	std::string getAddress();
	unsigned int getId();
	std::string getTaggerId();
	void deleteUser();
	bool canLogin();
	static void setNextId(unsigned int id);
	void saveStr(std::ostream& out);
	bool checkHash(std::string inHash);
	friend std::ostream& operator<<(std::ostream& out, const User& user);
};
#endif