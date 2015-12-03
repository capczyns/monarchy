#include "user.h"

unsigned int User::nextId = 1;
User::User(){
	name = "EMPTY";
	address = "EMPTY";
	taggerId = "NOT TAGGER";
	id = 0;
	pwdHash = "EMPTY";
	phone = "EMPTY";
}
User::User(std::string name, std::string pwdHash, std::string address, std::string phone, std::string taggerId, unsigned int id){
	this->name = name;
	this->address = address;
	this->taggerId = taggerId;
	this->pwdHash = pwdHash;
	this->phone = phone;
	if(id == 0){
		this->id = nextId++;
	}
	else{
		this->id = id;
	}
}
std::string User::getName(){
	return name;
}
std::string User::getAddress(){
	return address;
}
unsigned int User::getId(){
	return id;
}
std::string User::getTaggerId(){
	return taggerId;
}
std::ostream& operator<<(std::ostream& out, const User& user){
	std::string strOut = "";
	if(user.name.length() > 15){
		strOut += user.name.substr(0, 12) + "...";
	}
	else{
		strOut += user.name + std::string(15 - user.name.length(), ' ');
	}
	strOut += '\t';
	if(user.address.length() > 20){
		strOut += user.address.substr(0,17) + "...";
	}
	else{
		strOut += user.address + std::string(20-user.address.length(), ' ');
	}
	strOut += '\t' + user.phone + '\t' + user.taggerId;
	out << strOut;
	return out;
}
bool User::canLogin(){
	return exists;
}
void User::deleteUser(){
	exists = false;
}
void User::setNextId(unsigned int id){
	nextId = id;
}
bool User::checkHash(std::string inHash){
	return (pwdHash.compare(inHash) == 0);
}
void User::saveStr(std::ostream& out){
	out << address << std::endl
		<< phone << std::endl
		<< taggerId << std::endl
		<< name << " " << pwdHash << " " << id;
	if(exists){
		out << " T";
	}
	else{
		out << " F";
	}
	out << std::endl;
}
/*
	unsigned int id;
	unsigned int taggerId;
	std::string name;
	std::string address;
	std::string pwdHash;
	bool exists = true;
*/