#include "user.h"

User::User(){
	name = "EMPTY";
	pwdHash = "EMPTY";
	realName = "EMPTY";
	address = "EMPTY";
	city = "EMPTY";
	state = "EMPTY";
	zip = "EMPTY";
	cellPhone = "EMPTY";
	homePhone = "EMPTY";
	organization = "EMPTY";
	tagger = false;
}
User::User(std::string name, std::string pwdHash, std::string realName, std::string address, std::string city, 
		   std::string state, std::string zip, std::string cellPhone, std::string homePhone, std::string organization, bool tagger){
	this->name = name;
	this->pwdHash = pwdHash;
	this->realName = realName;
	this->address = address;
	this->city = city;
	this->state = state;
	this->zip = zip;
	this->cellPhone = cellPhone;
	this->homePhone = homePhone;
	this->organization = organization;
	this->tagger = tagger;
}
void User::change(std::string name, std::string realName, std::string address, std::string city,
				  std::string state, std::string zip, std::string cellPhone, std::string homePhone, std::string organization, bool tagger){
	this->name = name;
	this->realName = realName;
	this->address = address;
	this->city = city;
	this->state = state;
	this->zip = zip;
	this->cellPhone = cellPhone;
	this->homePhone = homePhone;
	this->organization = organization;
	this->tagger = tagger;
}
std::string User::getName(){
	return name;
}
std::string User::getRealName(){
	return realName;
}
std::string User::getAddress(){
	return address;
}
std::string User::getCity(){
	return city;
}
std::string User::getState(){
	return state;
}
std::string User::getZip(){
	return zip;
}
std::string User::getCellPhone(){
	return cellPhone;
}
std::string User::getHomePhone(){
	return homePhone;
}
std::string User::getOrganization(){
	return organization;
}
std::ostream& operator<<(std::ostream& out, const User& user){
	out <<"Username: " << user.name << "     Name: ";
	if(user.realName.length() == 0){
		out << "Unlisted";
	}
	else
		out << user.realName;

	out << "     Organization: ";
	if(user.organization.length() == 0)
		out << "Unlisted\n";
	else
		out << user.organization << std::endl;

	out << "Address: ";
	if(user.address.length() == 0)
		out << "Unlisted Address, ";
	else
		out << user.address << ", ";

	if(user.city.length() ==0)
		out << "Unlisted City, ";
	else
		out << user.city << ", ";

	if(user.state.length() == 0)
		out << "Unlisted State, ";
	else
		out << user.state << " ";

	if(user.zip.length() == 0)
		out << "Unlisted Zip";
	else
		out << user.zip;

	out << "\nCell #: ";
	if(user.cellPhone.length() == 0)
		out << "Unlisted";
	else
		out << user.cellPhone;

	out << "     Home #: ";
	if(user.homePhone.length() == 0)
		out << "Unlisted";
	else
		out << user.homePhone;
	return out;
}
bool User::canLogin(){
	return exists;
}
void User::deleteUser(){
	exists = false;
}
bool User::checkHash(std::string inHash){
	return (pwdHash.compare(inHash) == 0);
}
void User::saveStr(std::ostream& out){
	out << name << std::endl;
	out << address << std::endl;
	out << city << std::endl;
	out << state << std::endl;
	out << zip << std::endl;
	out << realName << std::endl;
	out << homePhone << std::endl;
	out << cellPhone << std::endl;
	out << organization << std::endl;
	out << pwdHash << std::endl;
	if(exists){
		out << "T";
	}
	else{
		out << "F";
	}
	out << std::endl;
	if(tagger){
		out << "T";
	}
	else{
		out << "F";
	}
	out << std::endl;
}
bool User::canTag(){
	return tagger;
}
/*
	unsigned int id;
	unsigned int taggerId;
	std::string name;
	std::string address;
	std::string pwdHash;
	bool exists = true;
*/