#ifndef SYSTEM_H
#define SYSTEM_H
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <ctime>
#include "data/user.h"
#include "data/storage.h"
#include "data/sighting.h"
#include "data/butterfly.h"
#include "data/dataFile.h"
#include "data/reports.h"
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
	std::string reports();
	void mainMenu();
	void clear();
	bool editAccount();
	std::string editSighting(Sighting& sighting);

	std::map<std::string, User> users;
	std::map<unsigned int, Sighting> sightings;
	std::map<std::string, Butterfly> tags;
	std::map<std::string, std::vector<Sighting*> > userSightings;
	std::map<std::string, std::vector<Sighting*> > tagSightings;
	std::map<std::string, std::vector<Sighting*> > locationSightings;
	std::map<std::string, std::vector<Sighting*> > dateSightings;
	std::string currentUser;
	static std::string versionNumber;
public:
	static std::string programTitle;
	void start();
};
#endif