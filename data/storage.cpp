#include "storage.h"

#ifdef _WIN32
std::string Storage::separator = "\\";
#else
std::string Storage::separator = "/";
#endif


std::string Storage::storageDir = "storage";
std::string Storage::userFile = "Users.txt";
void Storage::storeUsers(std::map<std::string, User>& users){
	std::ofstream outFile;
	std::string thisUser;
	outFile.open(storageDir + separator + userFile, std::ofstream::trunc);
	if(outFile.is_open()){
		for(std::map<std::string, User>::iterator i = users.begin(); i != users.end(); ++i){
			i->second.saveStr(outFile);
		}
		outFile.close();
	}
	else{
		std::cout << "Didn't open outFile";
	}
}
void Storage::fetchUsers(std::map<std::string, User>& users){
	std::string name;
	std::string address;
	std::string city;
	std::string state;
	std::string zip;
	std::string realName;
	std::string homePhone;
	std::string cellPhone;
	std::string organization;
	std::string pwdHash;
	std::string existStr;
	std::string taggerStr;
	bool exists;
	bool tagger;

	std::ifstream inFile(storageDir + separator + userFile);
	if(inFile.is_open()){
		while(std::getline(inFile, name)){
			if(name.length() > 0){
				std::getline(inFile, address);
				std::getline(inFile, city);
				std::getline(inFile, state);
				std::getline(inFile, zip);
				std::getline(inFile, realName);
				std::getline(inFile, homePhone);
				std::getline(inFile, cellPhone);
				std::getline(inFile, organization);
				std::getline(inFile, pwdHash);
				std::getline(inFile, existStr);
				std::getline(inFile, taggerStr);
				if(existStr[0] == 'T'){
					exists = true;
				}
				else{
					exists = false;
				}
				if(taggerStr[0] == 'T'){
					tagger = true;
				}
				else{
					tagger = false;
				}
				users[name] = User(name, pwdHash, realName, address, city, state, zip, cellPhone, homePhone, organization, tagger);
				if(!exists){
					users[name].deleteUser();
				}
			}
		}
	}
}
