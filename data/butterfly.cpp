#include "butterfly.h"

Butterfly::Butterfly(){
	tagger = "NONE";
	tagNum = "NONE";
	species = "NONE";
	city = "NONE";
	state = "NONE";
	country = "NONE";
	day = 0;
	month = 0;
	year = 0;
	hour = 0;
	minute = 0;
	second = 0;
	latitude = 0.0;
	longitude = 0.0;
}
Butterfly::Butterfly(std::string tagger, std::string tagNum, std::string species, std::string city, std::string state, std::string country,
		  int day, int month, int year, int hour, int minute, int second, double latitude, double longitude){
	this->tagger = tagger;
	this->tagNum = tagNum;
	this->species = species;
	this->city = city;
	this->state = state;
	this->country = country;
	this->day = day;
	this->month = month;
	this->year = year;
	this->hour = hour;
	this->minute = minute;
	this->second = second;
	this->latitude = latitude;
	this->longitude = longitude;
}
Butterfly::Butterfly(ButterflyData& data){
	update(data);
}
void Butterfly::update(ButterflyData& data){
	tagger = data.tagger;
	tagNum = data.tagNum;
	species = data.species;
	city = data.city;
	state = data.state;
	country = data.country;
	day = data.day;
	month = data.month;
	year = data.year;
	hour = data.hour;
	minute = data.minute;
	second = data.second;
	latitude = data.latitude;
	longitude = data.longitude;
}
ButterflyData Butterfly::getData(){
	return ButterflyData(tagger, tagNum, species, city, state, country, day, month, year, hour, minute, second, latitude, longitude);
}
void Butterfly::saveStr(std::ostream& out){
	out << tagger << std::endl;
	out << tagNum << std::endl;
	out << species << std::endl;
	out << city << std::endl;
	out << state << std::endl;
	out << country << std::endl;
	out << day << std::endl;
	out << month << std::endl;
	out << year << std::endl;
	out << hour << std::endl;
	out << minute << std::endl;
	out << second << std::endl;
	out << latitude << std::endl;
	out << longitude << std::endl;
}
std::string Butterfly::getSpecies(){
	return species;
}
ButterflyData::ButterflyData(){
	tagger = "NONE";
	tagNum = "NONE";
	species = "NONE";
	city = "NONE";
	state = "NONE";
	country = "NONE";
	day = 0;
	month = 0;
	year = 0;
	hour = 0;
	minute = 0;
	second = 0;
	latitude = 0.0;
	longitude = 0.0;
}
ButterflyData::ButterflyData(std::string tagger, std::string tagNum, std::string species, std::string city, std::string state, std::string country,
		  int day, int month, int year, int hour, int minute, int second, double latitude, double longitude){
	this->tagger = tagger;
	this->tagNum = tagNum;
	this->species = species;
	this->city = city;
	this->state = state;
	this->country = country;
	this->day = day;
	this->month = month;
	this->year = year;
	this->hour = hour;
	this->minute = minute;
	this->second = second;
	this->latitude = latitude;
	this->longitude = longitude;
}