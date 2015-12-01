#ifndef SYSTEM_H
#define SYSTEM_H
#include <string>
#include <map>
class System{
private:
	void login();
	void quit();
	std::string importExport();
	std::string createSighting();
	void viewUsers();
	bool deleteAccount();
	std::string manageSightings();
	void reports();
	void mainMenu();
	void clear();

	//std::map<unsigned int, User> users;
	std::string pwdFile;
public:
	void start();
};
#endif