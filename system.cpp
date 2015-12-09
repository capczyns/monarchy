#include "system.h"
#include "external/echoDisable.h"
#include "external/ChrisHash.h"
#include <iostream>
#include <fstream>
std::string System::versionNumber = "Version 0.0.1";
std::string System::programTitle = "Monarchy Butterfly Tracking System";
void System::start(){
	/*
		Starts the Butterfly Tracking System
	*/
	Storage::fetchUsers(users);
	Storage::loadState();
	loginMenu("");
}
bool System::createUser(){
	std::string pageName = "Create User Account";
	std::string prompt = programTitle + "\n" + pageName + "\n\n" + "User ID: ";
	bool validInput = false;
	bool tagger;
	std::string name, realName, pwd, address, city, state, zip, cellPhone, homePhone, organization, line;

	while(!validInput){
		clear();
		std::cout << prompt;
		std::getline(std::cin, name);
		validInput = true;
		validInput = (users.find(name) == users.end());
		if(!validInput){
			prompt = programTitle + "\n" + pageName + "\n\n" + "User ID already exists\nUser ID: ";
		}
	}
	std::cout << "Password: ";
	chrisLibs::echo(false);
	std::getline(std::cin, pwd);
	chrisLibs::echo(true);
	pwd = chrisLibs::sha256(pwd);
	std::cout << "\nName: ";
	std::getline(std::cin, realName);
	std::cout << "Street Address: ";
	std::getline(std::cin, address);
	std::cout << "City: ";
	std::getline(std::cin, city);
	std::cout << "State: ";
	std::getline(std::cin, state);
	prompt = "Zip (##### or #####-####):";
	validInput = false;
	while(!validInput){
		validInput = true;
		std::cout << prompt;
		prompt = "Invalid Zip\nZip (##### or #####-####): ";
		std::getline(std::cin, zip);
		if(!(zip.length() == 5 || zip.length() == 10)){
			validInput = false;
			continue;
		}
		for(int index = 0; validInput && index < 5; ++index){
			if(zip[index] < '0' || zip[index] > '9'){
				validInput = false;
			}
		}
		if(zip.length() == 10){
			if(zip[5] != '-'){
				validInput = false;
			}
			for(int index = 6; validInput && index < 10; ++index){
				if(zip[index] < '0' || zip[index] > '9'){
					validInput = false;
				}
			}
		}
	}
	prompt = "Cell Phone (###-###-####): ";
	validInput = false;
	while(!validInput){
		validInput = true;
		std::cout << prompt;
		prompt = "Invalid Phone Number\nCell Phone (###-###-####): ";
		std::getline(std::cin, cellPhone);
		if(cellPhone.length() != 12){
			validInput = false;
			continue;
		}
		if(cellPhone[3] != '-' || cellPhone[7] != '-'){
			validInput = false;
			continue;
		}
		for(int index = 0; validInput && index < 3; ++index){
			if(cellPhone[index] < '0' || cellPhone[index] > '9'){
				validInput = false;
			}
		}
		for(int index = 4; validInput && index < 7; ++index){
			if(cellPhone[index] < '0' || cellPhone[index] > '9'){
				validInput = false;
			}
		}
		for(int index = 8; validInput && index < 10; ++index){
			if(cellPhone[index] < '0' || cellPhone[index] > '9'){
				validInput = false;
			}
		}
	}
	validInput = false;
	prompt = "Home Phone (###-###-####): ";
	while(!validInput){
		validInput = true;
		std::cout << prompt;
		prompt = "Invalid Phone Number\nHome Phone (###-###-####): ";
		std::getline(std::cin, homePhone);
		if(homePhone.length() != 12){
			validInput = false;
			continue;
		}
		if(homePhone[3] != '-' || homePhone[7] != '-'){
			validInput = false;
			continue;
		}
		for(int index = 0; validInput && index < 3; ++index){
			if(homePhone[index] < '0' || homePhone[index] > '9'){
				validInput = false;
			}
		}
		for(int index = 4; validInput && index < 7; ++index){
			if(homePhone[index] < '0' || homePhone[index] > '9'){
				validInput = false;
			}
		}
		for(int index = 8; validInput && index < 10; ++index){
			if(homePhone[index] < '0' || homePhone[index] > '9'){
				validInput = false;
			}
		}
	}
	std::cout << "Organization: ";
	std::getline(std::cin, organization);
	std::cout << "Tagger (Y/YES for yes, anything else for no): ";
	std::getline(std::cin, line);
	if((line.length() == 1 && (line[0] == 'Y' || line[0] == 'y')) ||
		(line.length() == 3 && (line[0] == 'Y' || line[0] == 'y') &&
							   (line[1] == 'E' || line[1] == 'e') &&
							   (line[2] == 'S' || line[2] == 's'))){
		tagger = true;
	}
	else{
		tagger = false;
	}
	users[name] = User(name, pwd, realName, address, city, state, zip, cellPhone, homePhone, organization, tagger);
	Storage::saveUser(users[name]);
	loginMenu("Account Created");
}
void System::loginMenu(std::string message){
	std::string prompt = message + "\nEnter choice: ";
	std::string line = "";
	while(line.length() < 1 || !(line[0] >= '1' && line[0] <= '3')){
		clear();
		std::cout << programTitle << '\n'
				  << versionNumber << '\n'
				  << "Login Menu:\n\n"
				  << "1. Login\n"
				  << "2. Create Account\n"
				  << "3. Quit\n\n";

		std::cout << prompt;
		std::getline(std::cin, line);
		switch(line[0]){
			case '1':
				login("");
				break;
			case '2':
				createUser();
				break;
			case '3':
				std::cout << "Goodbye\n";
		};
		prompt = "Invalid Option\nEnter choice: ";
	}
}
void System::login(std::string message){
	/*
		Handles the login process
	*/
	std::string pageName = "User Login";
	std::string name, pwd, prompt, line;
	bool validName = false;
	prompt = programTitle + "\n" + pageName + "\n\n" + message + "\n\nUsername: ";
	while(!validName){
		clear();
		std::cout << prompt;
		std::getline(std::cin, name);
		validName = true;
	}
	std::cout << "Password: ";
	chrisLibs::echo(false);
	std::getline(std::cin, pwd);
	chrisLibs::echo(true);
	std::string holdPw = pwd;
	pwd = chrisLibs::sha256(holdPw);
	if(users.find(name) != users.end() && users[name].canLogin() && users[name].checkHash(pwd)){
		/*
			Log in the user
		*/
		currentUser = name;
		Storage::fetchSightings(sightings, tagSightings, dateSightings, locationSightings, userSightings);
		Storage::fetchTags(tags);
		mainMenu();
	}
	else{
		loginMenu("Invalid Username/Password\n");
	}
	//mainMenu();
	/*
		Read lines from file until I find username
		If I don't find username or pwd doesn't match, inform user try again
	*/
}
void System::quit(){
	/*
		Handles quitting the program
	*/
}
std::string System::importExport(){
	/*
		Handles file import and export
	*/
	std::string line = "";
	std::string path = "";
	std::string prompt = "\nChoose option: ";
	while(line.length() < 1 || !(line[0] >= '1' && line[0] <= '3')){
		clear();
		std::cout << programTitle << '\n'
				  << "Import/Export Menu:\n"
				  << "1. Import\n"
				  << "2. Export\n"
				  << "3. Cancel\n";
		std::cout << prompt;
		std::getline(std::cin, line);
		prompt = "\nInvalid option\nChoose option: ";
	}
	if(line[0] != '3'){
		std::cout << "\n\n\n";
		switch(line[0]){
			case '1':
				return DataFile::import(sightings, tags, tagSightings, userSightings, dateSightings, locationSightings);
				break;
			case '2':
				return DataFile::exportSightings(sightings, tags, tagSightings, locationSightings);
				break;
		};
		return prompt;
	}
	return "File operation cancelled.";
}
std::string System::editSighting(Sighting& sighting){
	/*
		Handles creating a sighting
	*/
	clear();
	bool validInput = false;
	bool cancelled = false;
	std::string line, temp;
	SightingData data = sighting.getData();

	std::string oldDate = data.dateStr();
	std::string oldCity = data.cityStr();
	std::string oldTag = data.tagNum;



	std::string prompt;
	std::cout << programTitle << "\nEdit Sighting\n\n";
	std::cout << sighting << "\n\n";
	std::cout << "Enter sighting data, or \"exit\" to cancel.\nLeave blank to use original value\n\n";

	std::string date;
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << data.year << '-' << std::setw(2) << data.month << '-' << std::setw(2) << data.day;
	date = ss.str();
	ss.str(std::string());

	ss << std::setfill('0') << std::setw(2) << data.hour << ':' << std::setw(2) << data.minute << ':' << std::setw(2) << data.second;
	std::string sightTime = ss.str();
	ss.str(std::string());

	prompt = "Date (Blank to use " + date + ") : ";
	while(!validInput && !cancelled){	//	Entering Latitude
		validInput = true;
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Sighting Update cancelled!";
		}
		else if(line.length() == 0){
			validInput = true;
		}
		else if(line.length() == 10){
			temp = "";
			for(int index = 0; validInput && index < 4; ++index){
				if(line[index] >= '0' && line[index] <= '9'){
					temp += line[index];
					validInput = true;
				}
				else{
					validInput = false;
				}
			}
			if(validInput){
				ss.str(temp);
				ss.seekg(0);
				ss.clear();
				ss >> data.year;
				//data.year = std::stoi(temp);
			}
			temp = "";
			for(int index = 5; validInput && index < 7; ++index){
				if(line[index] >= '0' && line[index] <= '9'){
					temp += line[index];
					validInput = true;
				}
				else{
					validInput = false;
				}
			}
			if(validInput){
				ss.str(temp);
				ss.seekg(0);
				ss.clear();
				ss >> data.month;
				//data.month = std::stoi(temp);
			}
			temp = "";
			for(int index = 8; validInput && index < 10; ++index){
				if(line[index] >= '0' && line[index] <= '9'){
					temp += line[index];
					validInput = true;
				}
				else{
					validInput = false;
				}
			}
			if(validInput){
				if(!(validInput = data.month > 0 && data.month <= 12)){
					prompt = "Month must be between 1 and 12\nDate (YYYY-MM-DD): ";
				}
				ss.str(temp);
				ss.seekg(0);
				ss.clear();
				ss >> data.day;
				//data.day = std::stoi(temp);
				if(data.day < 1 || data.day > 31){
					prompt = "Wrong number of days\nDate (YYYY-MM-DD): ";
					validInput = false;
				}
				else{
					if(data.month == 2){
						if(data.day > 29){
							validInput = false;
							prompt = "Wrong number of days (February)\nDate (YYYY-MM-DD): ";
						}
						if(data.year % 4 == 0 && data.day > 28){
							validInput = false;
							prompt = "Wrong number of days (February in Leap Year)\nDate (YYYY-MM-DD): ";
						}
					}
					else if((data.month == 4 || data.month == 6 || data.month == 9 ||
							 data.month == 11) && data.day > 30){
						validInput = false;
						prompt = "Wrong number of days\nDate (YYYY-MM-DD): ";
					}
				}
			}
			else{
				prompt = "Please use correct format (YYYY-MM-DD): ";
				validInput = false;
			}
		}
		else{
			validInput = false;
			prompt = "Please use correct format (YYYY-MM-DD): ";
		}
	}
	prompt = "Time (Blank to use " + sightTime + ") : ";
	validInput = false;
	while(!validInput && !cancelled){	//	Entering Latitude
		validInput = true;
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Sighting Update cancelled!";
		}
		else if(line.length() == 0){
			validInput = true;
		}
		else if(line.length() == 8){
			temp = "";
			for(int index = 0; validInput && index < 2; ++index){
				if(line[index] >= '0' && line[index] <= '9'){
					temp += line[index];
				}
				else{
					validInput = false;
				}
			}
			if(validInput){
				ss.str(temp);
				ss.seekg(0);
				ss.clear();
				ss >> data.hour;
				//data.hour = std::stoi(temp);
			}
			temp = "";
			for(int index = 3; validInput && index < 5; ++index){
				if(line[index] >= '0' && line[index] <= '9'){
					temp += line[index];
				}
				else{
					validInput = false;
				}
			}
			if(validInput){
				ss.str(temp);
				ss.seekg(0);
				ss.clear();
				ss >> data.minute;
				//data.minute = std::stoi(temp);
			}
			temp = "";
			for(int index = 6; validInput && index < 8; ++index){
				if(line[index] >= '0' && line[index] <= '9'){
					temp += line[index];
				}
				else{
					validInput = false;
				}
			}
			if(validInput){
				ss.str(temp);
				ss.seekg(0);
				ss.clear();
				ss >> data.second;
				//data.second = std::stoi(temp);
				if(data.hour < 0 || data.hour > 23){
					validInput = false;
					prompt = "Hour must be between 0 and 23\nTime (HH:MM:SS): ";
				}
				if(data.minute < 0 || data.minute > 59 ||
				   data.second < 0 || data.second > 59){
					validInput = false;
					prompt = "Minutes and Seconds must be between 0 and 59\nTime (HH:MM:SS): ";
				}
			}
			else{
				prompt = "Please use correct format (HH:MM:SS): ";
				validInput = false;
			}
		}
		else{
			prompt = "Please use correct format (HH:MM:SS): ";
			validInput = false;
		}
	}
	temp = "";
	ss.str(std::string());
	ss.seekg(0);
	ss.clear();
	if(data.latitude > 0){
		ss << '+';
	}
	ss << data.latitude;
	temp = ss.str();
	prompt = "Latitude (Blank to use " + temp + "): ";
	validInput = false;
	while(!validInput && !cancelled){	//	Entering Latitude
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Sighting update cancelled!";
		}
		else if(line.length() > 0){
			ss.str(line);
			ss.seekg(0);
			ss.clear();
			ss >> data.latitude;
			validInput = !ss.fail();
			if(validInput){
				validInput = data.latitude >= -90 && data.latitude <= 90;
			}
			prompt = "Invalid Latitude, Please try again: ";
		}
		else{
			validInput = true;
		}
	}
	validInput = false;
	temp = "";
	ss.str(std::string());
	ss.seekg(0);
	ss.clear();
	if(data.longitude > 0){
		ss << '+';
	}
	ss << data.longitude;
	temp = ss.str();
	prompt = "Longitude (Blank to use " + temp + "): ";
	while(!validInput && !cancelled){	//	Entering Longitude
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Sighting update cancelled!";
		}
		else if(line.length() > 0){
			ss.str(line);
			ss.seekg(0);
			ss.clear();
			ss >> data.longitude;
			validInput = !ss.fail();
			if(validInput){
				validInput = data.longitude >= -180 && data.longitude <= 180;
			}
			prompt = "Invalid Longitude, Please try again: ";
		}
		else{
			validInput = true;
		}
	}
	validInput = false;
	std::cout << "City (Blank to use " + data.city + "): ";
	std::getline(std::cin, line);
	if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
		(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
		(line[3] == 't' || line[3] == 'T')){
		return "Sighting update cancelled!";
	}
	else if(line.length() > 0){
		data.city = line;
	}
	std::cout << "State/Province (Blank to use " + data.state + "): ";
	std::getline(std::cin, line);
	if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
		(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
		(line[3] == 't' || line[3] == 'T')){
		return "Sighting update cancelled!";
	}
	else if(line.length() > 0){
		data.state = line;
	}
	std::cout << "Country (Blank to use " + data.country + "): ";
	std::getline(std::cin, line);
	if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
		(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
		(line[3] == 't' || line[3] == 'T')){
		return "Sighting update cancelled!";
	}
	else{
		data.country = line;
	}
	prompt = "Species (Blank to use " + data.species + "): ";
	while(!validInput && !cancelled){	//	Entering Longitude
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Sighting update cancelled!";
		}
		else if(line.length() > 0){
			data.species = line;
			prompt = "Species cannot be blank, please try again: ";
		}
		else{
			validInput = true;
		}
	}
	validInput = false;
	if(data.tagNum.length() > 0){
		prompt = "Tag Number (Blank to use " + data.tagNum + "): ";
	}
	else{
		prompt = "Tag Number (Blank for none): ";
	}
	while(!validInput && !cancelled){	//	Entering Longitude
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Sighting update cancelled!";
		}
		else if(line.length() > 0){
			validInput = true;	//	TODO: Change this when we have tag database
			data.tagNum = line;
			prompt = "Tag number exists for another species already, Try another: ";
		}
		else{
			validInput = true;
		}
	}
	if(cancelled){
		return "Sighting update cancelled!";
	}
	sightings[data.id].update(data);
	//	Update other maps based on new data
	Sighting* addr = &sightings[data.id];


	std::vector<Sighting*>::iterator iter;
	std::vector<Sighting*>::iterator end;
	if(!(oldDate.compare(data.dateStr()) == 0)){
		iter = dateSightings[oldDate].begin();
		end = dateSightings[oldDate].end();
		while(iter != end && (*iter)->getId() != data.id){
			iter++;
		}
		if(iter != end){
			dateSightings[oldDate].erase(iter);
			dateSightings[data.dateStr()].push_back(addr);
		}
	}
	if(!(oldCity.compare(data.cityStr()) == 0)){
		iter = locationSightings[oldCity].begin();
		end = locationSightings[oldCity].end();
		while(iter != end && (*iter)->getId() != data.id){
			iter++;
		}
		if(iter != end){
			locationSightings[oldCity].erase(iter);
			locationSightings[data.cityStr()].push_back(addr);
		}
	}
	if(!(oldTag.compare(data.tagNum) == 0)){
		iter = tagSightings[oldTag].begin();
		end = tagSightings[oldTag].end();
		while(iter != end && (*iter)->getId() != data.id){
			iter++;
		}
		if(iter != end){
			tagSightings[oldTag].erase(iter);
			tagSightings[data.tagNum].push_back(addr);
		}
	}

	Storage::storeSightings(sightings);
	ss.str(std::string());
	ss.seekg(0);
	ss.clear();
	ss << data.id;
	temp = ss.str();
	return "Sighting updated, ID = " + temp;
}
std::string System::createSighting(){
	/*
		Handles creating a sighting
	*/
	clear();
	bool validInput = false;
	bool cancelled = false;
	std::string line, temp;
	SightingData data;
	std::stringstream ss;
	std::string prompt;
	std::cout << programTitle << "\n" << "Create Sighting\n\n";
	std::cout << "Enter sighting data, or \"exit\" to cancel.\n\n";

	prompt = "Date (YYYY-MM-DD): ";
	while(!validInput && !cancelled){	//	Entering Latitude
		validInput = true;
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Sighting creation cancelled!";
		}
		else if(line.length() == 10){
			temp = "";
			for(int index = 0; validInput && index < 4; ++index){
				if(line[index] >= '0' && line[index] <= '9'){
					temp += line[index];
					validInput = true;
				}
				else{
					validInput = false;
				}
			}
			if(validInput){
				ss.str(temp);
				ss.seekg(0);
				ss.clear();
				ss >> data.year;
				//data.year = std::stoi(temp);
			}
			temp = "";
			for(int index = 5; validInput && index < 7; ++index){
				if(line[index] >= '0' && line[index] <= '9'){
					temp += line[index];
					validInput = true;
				}
				else{
					validInput = false;
				}
			}
			if(validInput){
				ss.str(temp);
				ss.seekg(0);
				ss.clear();
				ss >> data.month;
				//data.month = std::stoi(temp);
			}
			temp = "";
			for(int index = 8; validInput && index < 10; ++index){
				if(line[index] >= '0' && line[index] <= '9'){
					temp += line[index];
					validInput = true;
				}
				else{
					validInput = false;
				}
			}
			if(validInput){
				if(!(validInput = data.month > 0 && data.month <= 12)){
					prompt = "Month must be between 1 and 12\nDate (YYYY-MM-DD): ";
				}
				ss.str(temp);
				ss.seekg(0);
				ss.clear();
				ss >> data.day;
				//data.day = std::stoi(temp);
				if(data.day < 1 || data.day > 31){
					prompt = "Wrong number of days\nDate (YYYY-MM-DD): ";
					validInput = false;
				}
				else{
					if(data.month == 2){
						if(data.day > 29){
							validInput = false;
							prompt = "Wrong number of days (February)\nDate (YYYY-MM-DD): ";
						}
						if(data.year % 4 == 0 && data.day > 28){
							validInput = false;
							prompt = "Wrong number of days (February in Leap Year)\nDate (YYYY-MM-DD): ";
						}
					}
					else if((data.month == 4 || data.month == 6 || data.month == 9 ||
							 data.month == 11) && data.day > 30){
						validInput = false;
						prompt = "Wrong number of days\nDate (YYYY-MM-DD): ";
					}
				}
			}
			else{
				prompt = "Please use correct format (YYYY-MM-DD): ";
				validInput = false;
			}
		}
		else{
			validInput = false;
			prompt = "Please use correct format (YYYY-MM-DD): ";
		}
	}
	prompt = "Time (HH:MM:SS): ";
	validInput = false;
	while(!validInput && !cancelled){	//	Entering Latitude
		validInput = true;
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Sighting creation cancelled!";
		}
		else if(line.length() == 8){
			temp = "";
			for(int index = 0; validInput && index < 2; ++index){
				if(line[index] >= '0' && line[index] <= '9'){
					temp += line[index];
				}
				else{
					validInput = false;
				}
			}
			if(validInput){
				ss.str(temp);
				ss.seekg(0);
				ss.clear();
				ss >> data.hour;
				//data.hour = std::stoi(temp);
			}
			temp = "";
			for(int index = 3; validInput && index < 5; ++index){
				if(line[index] >= '0' && line[index] <= '9'){
					temp += line[index];
				}
				else{
					validInput = false;
				}
			}
			if(validInput){
				ss.str(temp);
				ss.seekg(0);
				ss.clear();
				ss >> data.minute;
				//data.minute = std::stoi(temp);
			}
			temp = "";
			for(int index = 6; validInput && index < 8; ++index){
				if(line[index] >= '0' && line[index] <= '9'){
					temp += line[index];
				}
				else{
					validInput = false;
				}
			}
			if(validInput){
				ss.str(temp);
				ss.seekg(0);
				ss.clear();
				ss >> data.second;
				//data.second = std::stoi(temp);
				if(data.hour < 0 || data.hour > 23){
					validInput = false;
					prompt = "Hour must be between 0 and 23\nTime (HH:MM:SS): ";
				}
				if(data.minute < 0 || data.minute > 59 ||
				   data.second < 0 || data.second > 59){
					validInput = false;
					prompt = "Minutes and Seconds must be between 0 and 59\nTime (HH:MM:SS): ";
				}
			}
			else{
				prompt = "Please use correct format (HH:MM:SS): ";
				validInput = false;
			}
		}
		else{
			prompt = "Please use correct format (HH:MM:SS): ";
			validInput = false;
		}
	}
	prompt = "Latitude: ";
	validInput = false;
	while(!validInput && !cancelled){	//	Entering Latitude
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Sighting creation cancelled!";
		}
		else{
			ss.str(line);
			ss.seekg(0);
			ss.clear();
			ss >> data.latitude;
			validInput = !ss.fail();
			if(validInput){
				validInput = data.latitude >= -90 && data.latitude <= 90;
			}
			prompt = "Invalid Latitude, Please try again: ";
		}
	}
	validInput = false;
	prompt = "Longitude: ";
	while(!validInput && !cancelled){	//	Entering Longitude
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Sighting creation cancelled!";
		}
		else{
			ss.str(line);
			ss.seekg(0);
			ss.clear();
			ss >> data.longitude;
			validInput = !ss.fail();
			if(validInput){
				validInput = data.longitude >= -180 && data.longitude <= 180;
			}
			prompt = "Invalid Longitude, Please try again: ";
		}
	}
	validInput = false;
	std::cout << "City: ";
	std::getline(std::cin, line);
	if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
		(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
		(line[3] == 't' || line[3] == 'T')){
		return "Sighting creation cancelled!";
	}
	else{
		data.city = line;
	}
	std::cout << "State/Province: ";
	std::getline(std::cin, line);
	if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
		(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
		(line[3] == 't' || line[3] == 'T')){
		return "Sighting creation cancelled!";
	}
	else{
		data.state = line;
	}
	std::cout << "Country: ";
	std::getline(std::cin, line);
	if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
		(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
		(line[3] == 't' || line[3] == 'T')){
		return "Sighting creation cancelled!";
	}
	else{
		data.country = line;
	}
	prompt = "Species: ";
	while(!validInput && !cancelled){	//	Entering Longitude
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Sighting creation cancelled!";
		}
		else{
			validInput = line.length() > 0;
			data.species = line;
			prompt = "Species cannot be blank, please try again: ";
		}
	}
	validInput = false;
	prompt = "Tag Number (Blank for none): ";

	std::map<std::string, Butterfly>::iterator tagIter;
	while(!validInput && !cancelled){	//	Entering Longitude
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Sighting creation cancelled!";
		}
		else if(line.length() == 0){
			validInput = true;
			data.tagNum = "";
		}
		else{
			tagIter = tags.find(line);
			data.tagNum = line;
			if(tagIter == tags.end()){
				if(users[currentUser].canTag()){
					validInput = true;
					tags[data.tagNum] = Butterfly(currentUser, data.tagNum, data.species, data.city, data.state, data.country,
												  data.day, data.month, data.year, data.hour, data.minute, data.second, data.latitude, data.longitude);

				}
				else{
					validInput = false;
					prompt = "You are not a registered tagger and this tag is not yet in use.\nTag Number (Blank for none): ";
				}
			}
			else{
				if(data.species.compare(tagIter->second.getSpecies()) == 0){
					validInput = true;
				}
				else{
					validInput = false;
					prompt = "This tag number is assigned to a different species already\nTag Number (Blank for none): ";
				}
			}
		}
	}
	if(cancelled){
		return "Sighting creation cancelled!";
	}
	Sighting tmp(currentUser, data.year, data.month, data.day, data.hour, data.minute, data.second,
				 data.latitude, data.longitude, data.city, data.state, data.country, data.species, data.tagNum);
	data = tmp.getData();
	sightings[tmp.getId()] = Sighting(data);
	//	Save sightings (only end of file?)
	Sighting* addr = &sightings[tmp.getId()];


	userSightings[currentUser].push_back(addr);
	tagSightings[data.tagNum].push_back(addr);
	locationSightings[data.cityStr()].push_back(addr);
	dateSightings[data.dateStr()].push_back(addr);

	Storage::saveSighting(sightings[data.id]);
	if(data.tagNum.length() > 0){
		Storage::saveTag(tags[data.tagNum]);
	}
	ss.str(std::string());
	ss.seekg(0);
	ss.clear();
	ss << data.id;
	temp = ss.str();
	return "Sighting created, ID = " + temp;
}
void System::viewUsers(){
	/*
		Handles viewing users
	*/
	clear();
	std::cout << programTitle << '\n';
	std::cout << "Displaying Users:\n\n";
	std::string line = "";
	std::string prompt = "\nType \"exit\" to exit or press enter for more: ";
	size_t userNum = 0;
	size_t numUsers = users.size();
	std::map<std::string, User>::iterator iter = users.begin();
	while(iter != users.end() && line.compare("EXIT") != 0){
		for(int index = 0; index < 4 && iter != users.end(); ++index){
			std::cout << iter->second << '\n';
			++iter;
		}
		if(iter != users.end()){
			prompt = "\nEnter to proceed (exit for main menu): ";
		}
		std::cout << prompt;
		std::getline(std::cin, line);
		std::cout << "\n\n\n";
		for(int index = 0; index < line.length(); index++){
			if(line[index] >= 'a' && line[index] <= 'z'){
				line[index] -= ('a' - 'A');
			}
		}
	}
}
bool System::deleteAccount(){
	/*
		Handles deleting the user's account
	*/
	std::cout << programTitle << '\n' << "Delete Account";
	std::string line = "";
	std::cout << "\n\nEnter \"delete\" to confirm account deletion: ";
	std::getline(std::cin, line);
	for(int index = 0; index < line.length(); index++){
		if(line[index] >= 'a' && line[index] <= 'z'){
			line[index] -= ('a' - 'A');
		}
	}
	if(line.length() > 0 && line.compare("DELETE") == 0){
		std::cout << "Deleting account, goodbye!\n";
		if(users.find(currentUser) != users.end()){
			users.erase(users.find(currentUser));
			Storage::storeUsers(users);
		}
		return true;
	}
	return false;
}
std::string System::manageSightings(std::string message, unsigned int id){
	/*
		Handles managing sightings
	*/
	clear();
	std::string line = "";
	std::string prompt = programTitle + "\nManage Sightings\n\nEnter Sighting ID or \"exit\" to cancel: ";
	bool validInput = false;
	bool cancelled = false;
	bool deleted = false;
	std::stringstream ss;
	std::map<unsigned int, Sighting>::iterator iter;
	if(message.length() == 0){
		while(!validInput && !cancelled){
			clear();
			std::cout << prompt;
			std::getline(std::cin, line);
			if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
				(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
				(line[3] == 't' || line[3] == 'T')){
				return "Sighting management cancelled!";
			}
			else{
				ss.str(line);
				ss.seekg(0);
				ss.clear();
				ss >> id;
				validInput = !ss.fail();
				prompt = programTitle + "\nManage Sightings\n\nError parsing Sighting ID\nEnter Sighting ID or \"exit\" to cancel: ";
				if(validInput){
					iter = sightings.find(id);
					validInput = (iter != sightings.end());
					prompt = programTitle + "\nManage Sightings\n\nSighting ID not found\nEnter Sighting ID or \"exit\" to cancel: ";
				}
			}
		}
	}
	prompt = message + "\nChoose option: ";
	line = "";
	while(line.length() < 1 || !(line[0] >= '1' && line[0] <= '3')){
		clear();
		std::cout << programTitle << "\n";
		std::cout << iter->second;
		std::cout << "\n\nManage Sightings Menu:\n"
				  << "1. Update\n"
				  << "2. Delete\n"
				  << "3. Cancel\n";
		std::cout << prompt;
		std::getline(std::cin, line);
		prompt = "\nInvalid option\nChoose option: ";
	}
	switch(line[0]){
		case '1':
			if(currentUser.compare(iter->second.getReporter()) == 0){
				return editSighting(iter->second);
			}
			else{
				return "Cannot modify sightings by other users.";
			}
			break;
		case '2':
			if(currentUser.compare(iter->second.getReporter()) == 0){
				deleted = true;
			}
			else{
				return "Cannot delete sightings by other users.";
			}
			break;
		default:
			cancelled = true;
	};
	if(deleted){
		std::cout << "Are you sure you want to delete this sighting (Y/Yes): ";
		std::getline(std::cin, line);
		if(line[0] == 'y' || line[0] == 'Y'){
			SightingData data = sightings[id].getData();
			std::vector<Sighting*>::iterator iter;
			std::vector<Sighting*>::iterator end;

			iter = userSightings[data.reporter].begin();
			end = userSightings[data.reporter].end();
			while(iter != end && (*iter)->getId() != id){
				iter++;
			}
			if(iter != end){
				userSightings[data.reporter].erase(iter);
			}

			iter = locationSightings[data.cityStr()].begin();
			end = locationSightings[data.cityStr()].end();
			while(iter != end && (*iter)->getId() != id){
				iter++;
			}
			if(iter != end){
				locationSightings[data.cityStr()].erase(iter);
			}

			iter = dateSightings[data.dateStr()].begin();
			end = dateSightings[data.dateStr()].end();
			while(iter != end && (*iter)->getId() != id){
				iter++;
			}
			if(iter != end){
				dateSightings[data.dateStr()].erase(iter);
			}

			iter = tagSightings[data.tagNum].begin();
			end = tagSightings[data.tagNum].end();
			while(iter != end && (*iter)->getId() != id){
				iter++;
			}
			if(iter != end){
				tagSightings[data.tagNum].erase(iter);
			}

			sightings.erase(id);
			Storage::storeSightings(sightings);
			ss.str(std::string());
			ss.seekg(0);
			ss.clear();
			ss << id;
			line = ss.str();
			return "Sighting " + line + " Deleted.";
		}
		else{
			return "Delete Aborted";
		}
	}
	if(cancelled){
			ss.str(std::string());
			ss.seekg(0);
			ss.clear();
			ss << id;
			line = ss.str();
		return "Sighting " + line + " update cancelled.";
	}
	else{
	}
	ss.str(std::string());
	ss.seekg(0);
	ss.clear();
	ss << id;
	line = ss.str();
	return "Sighting " + line + " update successful!";

}
void System::reports(){
	/*
		Handles generating reports
	*/
	std::string line = "";
	std::string prompt = "\nEnter Selection: ";
	while(line.length() < 1 || !(line[0] >= '1' && line[0] <= '7')){
		clear();
		std::cout << programTitle << "\n";
		std::cout << "Reports Menu:\n\n"
				  << "1. Hotspot Report\n"
				  << "2. Migration Report\n"
				  << "3. Frequency Report\n"
				  << "4. User Rankings Report\n"
				  << "5. Species Location Report\n"
				  << "6. Butterfly Sighting History\n"
				  << "7. Exit\n";
		std::cout << prompt;
		std::getline(std::cin, line);
		prompt = "\nInvalid Selection\nEnter Selection: ";
	}
	std::cout << "\n\n\n";
	switch(line[0]){
		case '1':
			std::cout << "Hotspot Report stuff ";
			break;
		case '2':
			std::cout << "Migration Report stuff ";
			break;
		case '3':
			std::cout << "Frequency Report stuff ";
			break;
		case '4':
			std::cout << "User Rankings Report stuff ";
			break;
		case '5':
			std::cout << "Species Location Report stuff ";
			break;
		case '6':
			std::cout << "Butterfly Sighting History stuff ";
			break;
	};
	if(line[0] != '7'){
		std::getline(std::cin, line);
	}
}
void System::clear(){
	/*
		Clears the screen
	*/
		std::cout << std::string(100, '\n') << std::endl;
}
void System::editAccount(){
	std::string line = "";
	std::string realName = users[currentUser].getRealName();
	std::string address = users[currentUser].getAddress();
	std::string city = users[currentUser].getCity();
	std::string state = users[currentUser].getState();
	std::string zip = users[currentUser].getZip();
	std::string homePhone = users[currentUser].getHomePhone();
	std::string cellPhone = users[currentUser].getCellPhone();
	std::string organization = users[currentUser].getOrganization();
	std::string prompt;
	bool validInput = false;

	bool tagger;
	clear();
	std::cout << programTitle << "\nEdit Account\n\n";
	std::cout << "Name (Blank to use " + realName + "): ";
	std::getline(std::cin, line);
	if(line.length()> 0){
		realName = line;
	}
	std::cout << "Street Address (Blank to use " + address + "): ";
	std::getline(std::cin, line);
	if(line.length() > 0){
		address = line;
	}
	std::cout << "City (Blank to use " + city + "): ";
	std::getline(std::cin, line);
	if(line.length() > 0){
		city = line;
	}
	std::cout << "State (Blank to use " + state + "): ";
	std::getline(std::cin, line);
	if(line.length() > 0){
		state = line;
	}
	std::cout << "Zip (Blank to use " + zip + "): ";
	std::getline(std::cin, line);
	if(line.length() > 0){
		zip = line;
	}
	std::cout << "Home Phone (Blank to use " + homePhone + "): ";
	std::getline(std::cin, line);
	if(line.length() > 0){
		homePhone = line;
	}
	std::cout << "Cell Phone (Blank to use " + cellPhone + "): ";
	std::getline(std::cin, line);
	if(line.length() > 0){
		cellPhone = line;
	}
	prompt = "Zip (##### or #####-####):";
	validInput = false;
	while(!validInput){
		validInput = true;
		std::cout << prompt;
		prompt = "Invalid Zip\nZip (##### or #####-####): ";
		std::getline(std::cin, line);
		if(line.length() == 0){
			continue;
		}
		if(!(line.length() == 5 || line.length() == 10)){
			validInput = false;
			continue;
		}
		for(int index = 0; validInput && index < 5; ++index){
			if(line[index] < '0' || line[index] > '9'){
				validInput = false;
			}
		}
		if(zip.length() == 10){
			if(line[5] != '-'){
				validInput = false;
			}
			for(int index = 6; validInput && index < 10; ++index){
				if(line[index] < '0' || line[index] > '9'){
					validInput = false;
				}
			}
		}
	}
	if(line.length() != 0){
		zip = line;
	}
	prompt = "Cell Phone (###-###-####): ";
	validInput = false;
	while(!validInput){
		validInput = true;
		std::cout << prompt;
		prompt = "Invalid Phone Number\nCell Phone (###-###-####): ";
		std::getline(std::cin, line);
		if(line.length() == 0){
			continue;
		}
		if(line.length() != 12){
			validInput = false;
			continue;
		}
		if(line[3] != '-' || line[7] != '-'){
			validInput = false;
			continue;
		}
		for(int index = 0; validInput && index < 3; ++index){
			if(line[index] < '0' || line[index] > '9'){
				validInput = false;
			}
		}
		for(int index = 4; validInput && index < 7; ++index){
			if(line[index] < '0' || line[index] > '9'){
				validInput = false;
			}
		}
		for(int index = 8; validInput && index < 10; ++index){
			if(line[index] < '0' || line[index] > '9'){
				validInput = false;
			}
		}
	}
	if(line.length() != 0){
		cellPhone = line;
	}
	validInput = false;
	prompt = "Home Phone (###-###-####): ";
	while(!validInput){
		validInput = true;
		std::cout << prompt;
		prompt = "Invalid Phone Number\nHome Phone (###-###-####): ";
		std::getline(std::cin, line);
		if(line.length() != 12){
			validInput = false;
			continue;
		}
		if(line[3] != '-' || line[7] != '-'){
			validInput = false;
			continue;
		}
		for(int index = 0; validInput && index < 3; ++index){
			if(line[index] < '0' || line[index] > '9'){
				validInput = false;
			}
		}
		for(int index = 4; validInput && index < 7; ++index){
			if(line[index] < '0' || line[index] > '9'){
				validInput = false;
			}
		}
		for(int index = 8; validInput && index < 10; ++index){
			if(line[index] < '0' || line[index] > '9'){
				validInput = false;
			}
		}
	}
	if(line.length() != 0){
		homePhone = line;
	}
	std::cout << "Organization (Blank to use " + organization + "): ";
	std::getline(std::cin, line);
	if(line.length() > 0){
		organization = line;
	}
	std::cout << "Tagger (Y/YES for yes, anything else for no): ";
	std::getline(std::cin, line);
	if((line.length() == 1 && (line[0] == 'Y' || line[0] == 'y')) ||
		(line.length() == 3 && (line[0] == 'Y' || line[0] == 'y') &&
							   (line[1] == 'E' || line[1] == 'e') &&
							   (line[2] == 'S' || line[2] == 's'))){
		tagger = true;
	}
	else{
		tagger = false;
	}
	users[currentUser].change(currentUser, realName, address, city, state, zip, homePhone, cellPhone, organization, tagger);
	Storage::storeUsers(users);
}
void System::mainMenu(){
	/*
		Handles display and navigation of the main menu
	*/
	clear();
	std::string line = "";
	std::string prompt = "Enter Selection: ";
	while(line.length() < 1 || line[0] != '8'){
		std::cout << programTitle << "\n";
		std::cout << "Main Menu:\n\n"
				  << "1. View All Users\n"
				  << "2. Manage Sightings\n"
				  << "3. Create Sighting\n"
				  << "4. Create Reports\n"
				  << "5. Import/Export\n"
				  << "6. Delete Account\n"
				  << "7. Edit Account\n"
				  << "8. Exit\n";
		std::cout << '\n';
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() < 1 || line[0] < '1' || line[0] > '8'){
			prompt = "Invalid selection\nEnter Selection: ";
			std::cout << std::string(100, '\n');
		}
		else{
			prompt = "Enter Selection: ";
			switch(line[0]){
				case '1':
					viewUsers();
					break;
				case '2':
					prompt = manageSightings() + '\n' + prompt;
					break;
				case '3':
					prompt = createSighting() + '\n' + prompt;
					break;
				case '4':
					reports();
					break;
				case '5':
					prompt = importExport() + '\n' + prompt;
					break;
				case '6':
					if(deleteAccount()){
						line = "8";
					}
					else{
						prompt = "Delete cancelled\n" + prompt;
					}
					break;
				case '7':
					editAccount();
					prompt = "Account updated\n" + prompt;
				case '8':
					quit();
					break;
			};
			if(line[0] != '8'){
				clear();
			}
		}
	}
}