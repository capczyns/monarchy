#include "sighting.h"
unsigned int Sighting::nextId = 1;
Sighting::Sighting(){
	reporter = "NOT SPECIFIED";
	year = 0;
	month = 0;
	day = 0;
	hour = 0;
	minute = 0;
	second = 0;
	latitude = 0.0;
	longitude = 0.0;
	city = "NOT SPECIFIED";
	state = "NOT SPECIFIED";
	country = "NOT SPECIFIED";
	species = "NOT SPECIFIED";
	tagNum = "NOT SPECIFIED";
	id = 0;
}
Sighting::Sighting(std::string reporter, int year, int month, int day,
			 	   int hour, int minute, int second, double latitude, double longitude,
			 	   std::string city, std::string state, std::string country, std::string species, std::string tagNum){
	update(reporter, year, month, day, hour, minute, second, latitude, longitude, city, state, country, species, tagNum);
	id = nextId++;
}
Sighting::Sighting(SightingData& data){
	update(data);
	id = data.id;
	if(id >= nextId){
		nextId = id + 1;
	}
}
void Sighting::update(std::string reporter, int year, int month, int day,
					  int hour, int minute, int second, double latitude, double longitude,
					  std::string city, std::string state, std::string country, std::string species, std::string tagNum){
	this->reporter = reporter;
	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
	this->second = second;
	this->latitude = latitude;
	this->longitude = longitude;
	this->city = city;
	this->state = state;
	this->country = country;
	this->species = species;
	this->tagNum = tagNum;
}
void Sighting::update(SightingData& data){
	reporter = data.reporter;
	year = data.year;
	month = data.month;
	day = data.day;
	hour = data.hour;
	minute = data.minute;
	second = data.second;
	latitude = data.latitude;
	longitude = data.longitude;
	city = data.city;
	state = data.state;
	country = data.country;
	species = data.species;
	tagNum = data.tagNum;
}
bool Sighting::sameSighting(Sighting& other){
	bool same = true;
	same &= (reporter.compare(other.reporter) == 0);
	same &= (year == other.year);
	same &= (month == other.month);
	same &= (day == other.day);
	same &= (hour == other.hour);
	same &= (minute == other.minute);
	same &= (second == other.second);
	same &= (latitude == other.latitude);
	same &= (longitude == other.longitude);
	same &= (city.compare(other.city) == 0);
	same &= (state.compare(other.state) == 0);
	same &= (country.compare(other.country) == 0);
	same &= (species.compare(other.species) == 0);
	same &= (tagNum.compare(other.tagNum) == 0);
	return same;
}
SightingData Sighting::getData(){
	return SightingData(reporter, year, month, day, hour, minute, second, latitude, longitude, city, state, country, species, tagNum, id);
}
unsigned int Sighting::getId(){
	return id;
}
SightingData::SightingData(std::string reporter, int year, int month, int day,
					  int hour, int minute, int second, double latitude, double longitude,
					  std::string city, std::string state, std::string country, std::string species, std::string tagNum, unsigned int id){
	this->reporter = reporter;
	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
	this->second = second;
	this->latitude = latitude;
	this->longitude = longitude;
	this->city = city;
	this->state = state;
	this->country = country;
	this->species = species;
	this->tagNum = tagNum;
	this->id = id;
}
std::string Sighting::getReporter(){
	return reporter;
}
void Sighting::saveStr(std::ostream& out){
	out << species << std::endl;
	out << id << std::endl;
	out << year << std::endl;
	out << month << std::endl;
	out << day << std::endl;
	out << hour << std::endl;
	out << minute << std::endl;
	out << second << std::endl;
	out << latitude << std::endl;
	out << longitude << std::endl;
	out << reporter << std::endl;
	out << city << std::endl;
	out << state << std::endl;
	out << country << std::endl;
	out << tagNum << std::endl;
}
std::string SightingData::dateStr(){
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << year << '-' << std::setw(2) << month << '-' << std::setw(2) << day;
	return ss.str();
}
std::string SightingData::cityStr(){
	char cityStr[90];
	for(int index = 0; index < 30; ++index){
		if(index < city.length()){
			cityStr[index] = city[index];
		}
		else{
			cityStr[index] = ' ';
		}
	}
	for(int index = 0; index < 30; ++index){
		if(index < city.length()){
			cityStr[index+30] = city[index];
		}
		else{
			cityStr[index+30] = ' ';
		}
	}
	for(int index = 0; index < 30; ++index){
		if(index < city.length()){
			cityStr[index+60] = city[index];
		}
		else{
			cityStr[index+60] = ' ';
		}
	}
	return std::string(cityStr);
}
std::ostream& operator<<(std::ostream& out, const Sighting& sighting){
	out << "Sighting ID: " << sighting.id << "     Reporter: " << sighting.reporter << "     Date: "
		<< std::setfill('0') << std::setw(2)
		<< sighting.year << '-' << std::setw(2) << sighting.month << '-' << std::setw(2) << sighting.day << "     Time: "
		<< std::setw(2) << sighting.hour << ':' << std::setw(2) << sighting.minute << ':' << std::setw(2) << sighting.second << std::endl;

	if(sighting.latitude > 0 || sighting.latitude < 0 || sighting.longitude > 0 || sighting.longitude < 0){
		out << "Location: ";
		if(sighting.latitude >= 0){
			out << '+';
		}
		out << sighting.latitude << ",";
		if(sighting.longitude >= 0){
			out << '+';
		}
		out << sighting.longitude << "     ";
	}
	if(sighting.city.length() > 0){
		out << sighting.city << ", " << sighting.state << ", " << sighting.country;
	}
	out << std::endl;
	out << "Species: " << sighting.species;
	if(sighting.tagNum.length() > 0){
		out << "     Tag Number: " << sighting.tagNum;
	}
	return out;
}