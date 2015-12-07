#include "storage.h"

#ifdef _WIN32
std::string Storage::separator = "\\";
#else
std::string Storage::separator = "/";
#endif


std::string Storage::storageDir = "storage";
std::string Storage::userFile = "Users.txt";
std::string Storage::sightingFile = "Sightings.txt";
std::string Storage::tagFile = "Tags.txt";
std::string Storage::stateFile = "State.txt";

void Storage::saveState(SystemState& state){

}
void Storage::loadState(){
	std::ifstream inFile(storageDir + separator + stateFile);
	unsigned int seqNum;
	inFile >> seqNum;
	if(!inFile.fail()){
		DataFile::setSeqNum(seqNum);
	}
}
void Storage::storeTags(std::map<std::string, Butterfly>& tags){
	std::ofstream outFile;
	outFile.open(storageDir + separator + tagFile), std::ofstream::trunc;
	if(outFile.is_open()){
		for(std::map<std::string, Butterfly>::iterator iter = tags.begin(); iter != tags.end(); ++iter){
			iter->second.saveStr(outFile);
		}
	}
}
void Storage::saveTag(Butterfly& tag){
	std::ofstream outFile;
	outFile.open(storageDir + separator + tagFile, std::ofstream::app);
	if(outFile.is_open()){
		tag.saveStr(outFile);
		outFile.close();
	}
}
void Storage::fetchTags(std::map<std::string, Butterfly>& tags){
	std::string line;

	std::ifstream inFile(storageDir + separator + tagFile);
	ButterflyData data;
	std::stringstream ss;
	Sighting* addr;
	if(inFile.is_open()){
		while(std::getline(inFile, data.tagger)){
			if(data.tagger.length() > 0){
				std::getline(inFile, data.tagNum);
				std::getline(inFile, data.species);
				std::getline(inFile, data.city);
				std::getline(inFile, data.state);
				std::getline(inFile, data.country);
				inFile >> data.day >> data.month >> data.year >> data.hour >> data.minute >> data.second >> data.latitude >> data.longitude;
				tags[data.tagNum] = Butterfly(data);
				inFile.ignore(10, '\n');
			}
		}
	}
}
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
void Storage::fetchSightings(std::map<unsigned int, Sighting>& sightings,
							 std::map<std::string, std::vector<Sighting*> >& tagSightings,
							 std::map<std::string, std::vector<Sighting*> >& dateSightings,
							 std::map<std::string, std::vector<Sighting*> >& locationSightings,
							 std::map<std::string, std::vector<Sighting*> >& userSightings){
	std::string line;

	std::ifstream inFile(storageDir + separator + sightingFile);
	SightingData data;
	std::stringstream ss;
	Sighting* addr;
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
				addr = &sightings[data.id];
				tagSightings[data.tagNum].push_back(addr);
				dateSightings[data.dateStr()].push_back(addr);
				locationSightings[data.cityStr()].push_back(addr);
				userSightings[data.reporter].push_back(addr);
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
