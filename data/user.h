#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>
class User{
private:
	unsigned int id;
	unsigned int taggerId;
	std::string name;
	std::string address;
	static unsigned int nextId;
public:
	User(std::string name, std::string address, unsigned int taggerId=0);
	std::string getName();
	std::string getAddress();
	unsigned int getId();
	unsigned int getTaggerId();
	friend std::ostream& operator<<(std::ostream& out, const User& user);
};
#endif