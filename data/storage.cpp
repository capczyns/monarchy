#include "storage.h"

#ifdef _WIN32
std::string Storage::separator = "\\";
#else
std::string Storage::separator = "/";
#endif


std::string Storage::storageDir = "storage";
std::string Storage::userFile = "Users.txt";
std::string Storage::sightingFile = "Sightings.txt";
void Storage::saveSighting(Sighting& sighting){
	std::ofstream outFile;
	outFile.open(storageDir + separator + sightingFile, std::ofstream::app);
	if(outFile.is_open()){
		sighting.saveStr(outFile);
		outFile.close();
	}
}
void Storage::saveUser(User& user){
	std::ofstream outFile;
	outFile.open(storageDir + separator + userFile, std::ofstream::app);
	if(outFile.is_open()){
		user.saveStr(outFile);
		outFile.close();
	}
}
void Storage::storeSightings(std::map<unsigned int, Sighting>& sightings){
	std::ofstream outFile;
	outFile.open(storageDir + separator + sightingFile, std::ofstream::trunc);
	if(outFile.is_open()){
		for(std::map<unsigned int, Sighting>::iterator i = sightings.begin(); i != sightings.end(); ++i){
			i->second.saveStr(outFile);
		}
		outFile.close();
	}
	else{
	}
}
void Storage::fetchSightings(std::map<unsigned int, Sighting>& sightings){
	std::string line;

	std::ifstream inFile(storageDir + separator + sightingFile);
	SightingData data;
	std::stringstream ss;
	if(inFile.is_open()){
		while(std::getline(inFile, data.species)){
			if(data.species.length() > 0){
				inFile >> data.id >> data.year >> data.month >> data.day >> data.hour >> data.minute >> data.second >> data.latitude >> data.longitude;
				inFile.ignore(10, '\n');
				std::getline(inFile, data.reporter);
				std::getline(inFile, data.city);
				std::getline(inFile, data.state);
				std::getline(inFile, data.country);
				std::getline(inFile, data.tagNum);
				sightings[data.id] = Sighting(data);
				std::cerr << "species = " <<data.species << std::endl;
				std::cerr << "id = " <<data.id << std::endl;
				std::cerr << "year = " <<data.year << std::endl;
				std::cerr << "month = " <<data.month << std::endl;
				std::cerr << "day = " <<data.day << std::endl;
				std::cerr << "hour = " <<data.hour << std::endl;
				std::cerr << "minute = " <<data.minute << std::endl;
				std::cerr << "second = " <<data.second << std::endl;
				std::cerr << "latitude = " <<data.latitude << std::endl;
				std::cerr << "longitude = " <<data.longitude << std::endl;
				std::cerr << "reporter = " <<data.reporter << std::endl;
				std::cerr << "city = " <<data.city << std::endl;
				std::cerr << "state = " <<data.state << std::endl;
				std::cerr << "species = " <<data.species << std::endl;
				std::cerr << "tagNum = " <<data.tagNum << std::endl;
			}
		}
	}
	else{
		std::cerr << "ERROR";
	}
}
void Storage::storeUsers(std::map<std::string, User>& users){
	std::ofstream outFile;
	outFile.open(storageDir + separator + userFile, std::ofstream::trunc);
	if(outFile.is_open()){
		for(std::map<std::string, User>::iterator i = users.begin(); i != users.end(); ++i){
			i->second.saveStr(outFile);
		}
		outFile.close();
	}
	else{
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
