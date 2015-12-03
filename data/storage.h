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
public:
	static void storeUsers(std::map<std::string, User>& users);
	static unsigned int fetchUsers(std::map<std::string, User>& users);
};
#endif