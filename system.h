#ifndef SYSTEM_H
#define SYSTEM_H
#include <string>
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
public:
	void start();
};
#endif