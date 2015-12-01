#include "system.h"
#include <iostream>
void System::start(){
	/*
		Starts the Butterfly Tracking System
	*/
	mainMenu();
}
void System::login(){
	/*
		Handles the login process
	*/
	std::cout << "login\n";
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
		std::cout << "Import/Export Menu:\n"
				  << "1. Import\n"
				  << "2. Export\n"
				  << "3. Cancel\n";
		std::cout << prompt;
		std::getline(std::cin, line);
		prompt = "\nInvalid option\nChoose option: ";
	}
	if(line[0] != '3'){
		std::cout << "\n\n\n";
		std::cout << "Enter file path: ";
		std::getline(std::cin, path);
		switch(line[0]){
			case '1':
				std::cout << "\nCheck import data and whatnot ";
				prompt = "File Import Success/Fail";
				break;
			case '2':
				std::cout << "\nExport sightings to file ";
				prompt = "File Export Success/Fail";
				break;
		};
		std::getline(std::cin, line);
		return prompt;
	}
	return "File operation cancelled.";
}
std::string System::createSighting(){
	/*
		Handles creating a sighting
	*/
	clear();
	std::string line = "";
	std::string prompt = "\nSelect Sighting Type: ";
	std::cout << "Sightings Menu:\n\n"
			  << "1. Tagged\n"
			  << "2. Untagged\n"
			  << "3. Cancel\n";
	std::cout << prompt;
	std::getline(std::cin, line);
	while(line.length() < 1 || !(line[0] >= '1' && line[0] <= '3')){
		clear();
		prompt = "\nUnknown command\nSelect Sighting Type: ";
		std::cout << "\n\n\n";
		std::cout << "Sightings Menu:\n\n"
				  << "1. Tagged\n"
				  << "2. Untagged\n"
				  << "3. Cancel\n";
		std::cout << prompt;
		std::getline(std::cin, line);
	}
	switch(line[0]){
		case '1':
			std::cout << "Enter Tagged Sighting stuff";
			std::getline(std::cin, line);
			break;
		case '2':
			std::cout << "Enter Untagged Sighting stuff";
			std::getline(std::cin, line);
			break;
		default:
			return "Sighting creation cancelled.";
			break;
	};
	return "Sighting created, ID = _____.";
}
void System::viewUsers(){
	/*
		Handles viewing users
	*/
	clear();
	std::cout << "Displaying Users:\n\n";
	std::string line = "";
	std::string prompt = "\nType \"exit\" to exit or press enter for more: ";
	size_t userNum = 0;
	size_t numUsers = 127;
	size_t digit;
	size_t range;
	while(userNum < numUsers && line.compare("EXIT") != 0){
		for(int index = 0; index < 10 && userNum < numUsers; index++){
			digit = ++userNum;
			range = 0;
			while(digit % 100 > 9){
				digit -= 10;
				range++;
			}
			std::cout << userNum;
			if(digit % 100 == 1 && range != 1){
				std::cout << "st";
			}
			else if(digit % 100 == 2 && range != 1){
				std::cout << "nd";
			}
			else if(digit % 100 == 3 && range != 1){
				std::cout << "rd";
			}
			else{
				std::cout << "th";
			}
			std::cout << " User displayed\n";
		}
		if(userNum >= numUsers){
			prompt = "\nEnter to proceed: ";
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
		return true;
	}
	return false;
}
std::string System::manageSightings(){
	/*
		Handles managing sightings
	*/
	clear();
	std::string line = "";
	std::string sightID = "";
	std::cout << "Enter Sighting ID: ";
	std::getline(std::cin, sightID);
	std::string prompt = "\nChoose option: ";
	std::string title;
	bool cancelled = false;
	bool deleted = false;
	while(line.length() < 1 || !(line[0] >= '1' && line[0] <= '3')){
		clear();
		std::cout << "Sighting ID: " << sightID << '\n'
				  << "Manage Sightings Menu:\n"
				  << "1. Update\n"
				  << "2. Delete\n"
				  << "3. Cancel\n";
		std::cout << prompt;
		std::getline(std::cin, line);
		prompt = "\nInvalid option\nChoose option: ";
	}
	switch(line[0]){
		case '1':
			title = "Sighting ID: " + sightID + "\nUpdate Sighting Menu:\n";
			break;
		case '2':
			title = "Sighting ID: " + sightID + "\nDelete Sighting Menu:\n";
			deleted = true;
			break;
		default:
			cancelled = true;
	};
	if(deleted){
		return "Sighting " + sightID + " Deleted.";
	}
	if(cancelled){
		return "Sighting " + sightID + " update cancelled.";
	}
	else{
		line = "";
		prompt = "\nChoose option: ";
		while(line.length() < 1 || !(line[0] >= '1' && line[0] <= '3')){
			clear();
			std::cout << title
					  << "1. Tagged\n"
					  << "2. Untagged\n"
					  << "3. Cancel\n";
			std::cout << prompt;
			std::getline(std::cin, line);
			prompt = "\nInvalid option\nChoose option: ";
		}
		switch(line[0]){
			case '1':
				std::cout << "Tagged Sighting Information Input";
				std::getline(std::cin, line);
				break;
			case '2':
				std::cout << "Untagged Sighting Information Input ";
				std::getline(std::cin, line);
				break;
			case '3':
				return "Sighting " + sightID + " update cancelled!";
		};
	}
	return "Sighting " + sightID + " update successful!";

}
void System::reports(){
	/*
		Handles generating reports
	*/
	std::string line = "";
	std::string prompt = "\nEnter Selection: ";
	while(line.length() < 1 || !(line[0] >= '1' && line[0] <= '7')){
		clear();
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
	std::cout << std::string(100,'\n');
}
void System::mainMenu(){
	/*
		Handles display and navigation of the main menu
	*/
	std::string line = "";
	std::string prompt = "Enter Selection: ";
	while(line.length() < 1 || line[0] != '7'){
		std::cout << "Main Menu:\n\n"
				  << "1. View All Users\n"
				  << "2. Manage Sightings\n"
				  << "3. Create Sighting\n"
				  << "4. Create Reports\n"
				  << "5. Import/Export\n"
				  << "6. Delete Account\n"
				  << "7. Exit\n";
		std::cout << '\n';
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() < 1 || line[0] < '1' || line[0] > '7'){
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
						line = "7";
					}
					else{
						prompt = "Delete cancelled\n" + prompt;
					}
					break;
				case '7':
					quit();
					break;
			};
			if(line[0] != '7'){
				clear();
			}
		}
	}
}