#ifndef STORAGE_H
#define STORAGE_H
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include "user.h"
#include "sighting.h"
#include "butterfly.h"
#include "dataFile.h"
class SystemState{
public:
	unsigned int seqNum;
};
class Storage{
private:
	static std::string stateFile;
	static std::string tagFile;
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
	static void fetchSightings(std::map<unsigned int, Sighting>& sightings,
							 std::map<std::string, std::vector<Sighting*> >& tagSightings,
							 std::map<std::string, std::vector<Sighting*> >& dateSightings,
							 std::map<std::string, std::vector<Sighting*> >& locationSightings,
							 std::map<std::string, std::vector<Sighting*> >& userSightings);

	static void storeTags(std::map<std::string, Butterfly>& tags);
	static void saveTag(Butterfly& tag);
	static void fetchTags(std::map<std::string, Butterfly>& tags);

	static void saveState(SystemState& state);
	static void loadState();
};
#endif