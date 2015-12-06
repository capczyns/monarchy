#ifndef STORAGE_H
#define STORAGE_H
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include "user.h"
#include "sighting.h"
class Storage{
private:
	static std::string userFile;
	static std::string sightingFile;
	static std::string separator;
	static std::string storageDir;
public:
	static void storeUsers(std::map<std::string, User>& users);
	static void saveUser(User& user);
	static void fetchUsers(std::map<std::string, User>& users);
	static void storeSightings(std::map<unsigned int, Sighting>& sightings);
	static void saveSighting(Sighting& sighting);
	static void fetchSightings(std::map<unsigned int, Sighting>& sightings);
};
#endif