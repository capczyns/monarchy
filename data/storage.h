#ifndef STORAGE_H
#define STORAGE_H
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include "user.h"
class Storage{
private:
	static std::string userFile;
	static std::string separator;
	static std::string storageDir;
public:
	static void storeUsers(std::map<std::string, User>& users);
	static void fetchUsers(std::map<std::string, User>& users);
};
#endif