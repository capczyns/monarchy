#include "user.h"

unsigned int User::nextId = 0;
User::User(std::string name, std::string address, unsigned int taggerId){
	this->name = name;
	this->address = address;
	this->taggerId = taggerId;
	id = nextId++;
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
unsigned int User::getTaggerId(){
	return taggerId;
}
std::ostream& operator<<(std::ostream& out, const User& user){
	out << user.name << '\t' << user.address << '\t';
	if(user.taggerId > 0){
		out << user.taggerId;
	}
	else{
		out << "NOT TAGGER";
	}
}