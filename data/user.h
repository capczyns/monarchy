#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>
class User{
private:
	std::string name;
	std::string pwdHash;
	std::string realName;
	std::string address;
	std::string city;
	std::string state;
	std::string zip;
	std::string cellPhone;
	std::string homePhone;
	std::string organization;
	bool tagger;

	bool exists = true;	//	Handles 'delete'...if an account is deleted, the use shouldn't be able to log on anymore, but user still needs to be in database
public:
	User();
	User(std::string name, std::string pwdHash, std::string realName, std::string address, std::string city, std::string state, 
		 std::string zip, std::string cellPhone, std::string homePhone, std::string organization, bool tagger = false);
	std::string getName();
	std::string getRealName();
	std::string getAddress();
	std::string getCity();
	std::string getState();
	std::string getZip();
	std::string getCellPhone();
	std::string getHomePhone();
	std::string getOrganization();
	void change(std::string name, std::string realName, std::string address, std::string city,
				std::string state, std::string zip, std::string cellPhone, std::string homePhone, std::string organization, bool tagger);
	void deleteUser();
	bool canLogin();
	void saveStr(std::ostream& out);
	bool checkHash(std::string inHash);
	bool canTag();
	friend std::ostream& operator<<(std::ostream& out, const User& user);
};
#endif