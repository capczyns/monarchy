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
bool Butterfly::sameSpecies(const std::string& other){
	if(other.length() != species.length()){
		return false;
	}
	for(int index = 0; index < species.length(); ++index){
		if(species[index] >= 'a' && species[index] <= 'z'){
			if(other[index] >= 'A' && other[index] <= 'Z'){
				if(other[index] + ('a' - 'A') != species[index]){
					return false;
				}
			}
			else if(other[index] != species[index]){
				return false;
			}
		}
		else if(species[index] >= 'A' && species[index] <= 'Z'){
			if(other[index] >= 'a' && other[index] <= 'z'){
				if(species[index] + ('a' - 'A') != other[index]){
					return false;
				}
			}
			else if(other[index] != species[index]){
				return false;
			}
		}
		else if(species[index] != other[index]){
			return false;
		}
	}
	return true;
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
ButterflyData::ButterflyData(SightingData& data){
	fromSighting(data);
}
void ButterflyData::fromSighting(SightingData& data){
	tagger = data.reporter;
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
bool Butterfly::onDate(std::string date){
	if(date.length() != 10){
		return false;
	}
	date[4] = '-';
	date[7] = '-';
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << year << '-' << std::setw(2) << month << '-' << std::setw(2) << day;
	return date.compare(ss.str()) == 0;
}
std::ostream& operator<< (std::ostream& out, Butterfly& butterfly){
	out << "Tag ID: " << butterfly.tagNum << "     Species: " << butterfly.species << '\n'
		<< "Tagger: " << butterfly.tagger << "     Date: "
		<< std::setfill('0') << std::setw(2)
		<< butterfly.year << '-' << std::setw(2) << butterfly.month << '-' << std::setw(2) << butterfly.day << "     Time: "
		<< std::setw(2) << butterfly.hour << ':' << std::setw(2) << butterfly.minute << ':' << std::setw(2) << butterfly.second << std::endl;

	if(butterfly.latitude > 0 || butterfly.latitude < 0 || butterfly.longitude > 0 || butterfly.longitude < 0){
		out << "Location: ";
		if(butterfly.latitude >= 0){
			out << '+';
		}
		out << butterfly.latitude << ",";
		if(butterfly.longitude >= 0){
			out << '+';
		}
		out << butterfly.longitude << "     ";
	}
	if(butterfly.city.length() > 0){
		out << butterfly.city << ", " << butterfly.state << ", " << butterfly.country;
	}
	return out;
}