#ifndef SYSTEM_H
#define SYSTEM_H
#include <string>
#include <map>
#include "data/user.h"
#include "data/storage.h"
class System{
private:
	bool createUser();
	void loginMenu(std::string message);
	void login(std::string message);
	void quit();
	std::string importExport();
	std::string createSighting();
	void viewUsers();
	bool deleteAccount();
	std::string manageSightings();
	void reports();
	void mainMenu();
	void clear();
	void editAccount();

	std::map<std::string, User> users;
	std::string pwdFile;
	std::string currentUser;
public:
	void start();
};
#endif