#include "storage.h"
std::string Storage::userFile = "Users.txt";
void Storage::storeUsers(std::map<std::string, User>& users){
	std::ofstream outFile;
	std::string thisUser;
	outFile.open(userFile, std::ofstream::trunc);
	if(outFile.is_open()){
		for(std::map<std::string, User>::iterator i = users.begin(); i != users.end(); ++i){
			i->second.saveStr(outFile);


			/*
				unsigned int id;
				unsigned int taggerId;
				std::string name;
				std::string address;
				std::string pwdHash;
				bool exists = true;

	return address + '\n' + name + ' ' + pwdHash + ' ' + id + ' ' + taggerId + ' ' + exists;

	User(std::string name, std::string pwdHash, std::string address, unsigned int taggerId=0, unsigned int id = 0);
				
			*/
		}
		outFile.close();
	}
	else{
		std::cout << "Didn't open outFile";
	}
}
unsigned int Storage::fetchUsers(std::map<std::string, User>& users){
	unsigned int id;
	std::string taggerId;
	std::string name;
	std::string address;
	std::string pwdHash;
	std::string phone;
	std::string existChar;
	std::string idStr;
	bool exists;

	unsigned int highestId = 1;
	std::ifstream inFile(userFile);
	if(inFile.is_open()){
		while(std::getline(inFile, address)){
			if(address.length() > 0){
				std::getline(inFile, phone);
				std::getline(inFile, taggerId);
				inFile >> name >> pwdHash >> id >> existChar;
				if(existChar[0] == 'T'){
					exists = true;
				}
				else{
					exists = false;
				}
				User tmp(name, pwdHash, address, phone, taggerId, id);
				users[name] = tmp;
				if(!exists){
					users[name].deleteUser();
				}
				if(id > highestId){
					highestId = id;
				}
				inFile.ignore(10, '\n');	//	Clears leftover newline
			}
		}
	}
	return highestId;
}