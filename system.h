#ifndef SYSTEM_H
#define SYSTEM_H
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include "data/user.h"
#include "data/storage.h"
#include "data/sighting.h"
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
	std::string manageSightings(std::string message = "", unsigned int id = 0);
	void reports();
	void mainMenu();
	void clear();
	void editAccount();
	std::string editSighting(Sighting& sighting);

	std::map<std::string, User> users;
	std::map<unsigned int, Sighting> sightings;
	std::string pwdFile;
	std::string currentUser;
public:
	void start();
};
#endif