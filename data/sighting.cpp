#include "sighting.h"
unsigned int Sighting::nextId = 1;
Weather::Weather(){
	std::srand(time(NULL));
	temp = std::rand() % 30 + 50;
	windSpeed = std::rand() % 10 + 1;
	windDir = std::rand() % 8;
	precipitation = std::rand() % 5;
}
Weather::Weather(int temp, int windSpeed, int windDir, int precipitation){
	this->temp = temp;
	this->windSpeed = windSpeed;
	if(windDir >= 0 && windDir < 8){
		this->windDir = windDir;
	}
	else{
		std::srand(time(NULL));
		windDir = std::rand() % 8;
	}
	this->precipitation = precipitation;
}
std::ostream& operator<< (std::ostream& out, const Weather& weather){
	out << "Weather: " << weather.temp << " degrees F. ";
	switch(weather.precipitation){
		case 1:
			out << "with Light Rain";
			break;
		case 2:
			out << "with Heavy Rain";
			break;
		case 0:
			out << "with Clear Skies";
			break;
		default:
			out << "and Partly Cloudy";
	}
	out << std::endl;
	out << "Wind: " << weather.windSpeed << "mph from the ";
	switch(weather.windDir){
		case 0:
			out << "North";
			break;
		case 1:
			out << "South";
			break;
		case 2:
			out << "East";
			break;
		case 3:
			out << "West";
			break;
		case 4:
			out << "North-East";
			break;
		case 5:
			out << "South-West";
			break;
		case 6:
			out << "North-West";
			break;
		case 7:
			out << "South-East";
			break;
	}
	return out;
}
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
	weather = Weather();
}
Sighting::Sighting(std::string reporter, int year, int month, int day,
			 	   int hour, int minute, int second, double latitude, double longitude,
			 	   std::string city, std::string state, std::string country, std::string species, std::string tagNum){
	update(reporter, year, month, day, hour, minute, second, latitude, longitude, city, state, country, species, tagNum);
	id = nextId++;
	weather = Weather();
}
Sighting::Sighting(SightingData& data){
	weather = Weather();
	update(data);
	id = data.id;
	if(id >= nextId){
		nextId = id + 1;
	}
	else if(id == 0){
		id = nextId++;
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

	weather = data.weather;
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
	SightingData data = SightingData(reporter, year, month, day, hour, minute, second, latitude, longitude, city, state, country, species, tagNum, id);
	data.weather = weather;
	return data;
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
	weather = Weather();
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
	out << weather.temp << std::endl;
	out << weather.windSpeed << std::endl;
	out << weather.windDir << std::endl;
	out << weather.precipitation << std::endl;
	out << reporter << std::endl;
	out << city << std::endl;
	out << state << std::endl;
	out << country << std::endl;
	out << tagNum << std::endl;
}
void SightingData::exportStr(std::ostream& out){
	/*
		Format:
		Date(10)
		Space(1)
		Time(8)
		Space(1)
		+/-
		Latitude(10)
		+/-
		Longitude(10)
		Space(1)
		City(30)
		State(30)
		Country(30)
		Species(20)
		TagNum(6)
	*/
		out << dateStr() << ' ' << std::setfill('0') << std::setw(2) << hour << ':' << std::setw(2) << minute << ':' << std::setw(2) << second << ' ';
		if(latitude >= 0){
			out << '+';
			if(latitude < 10){
				out << '0';
			}
			out << std::fixed << std::setprecision(7) << latitude;
		}
		else{
			out << '-';
			if(latitude > -10){
				out << '0';
			}
			out << std::fixed << std::setprecision(7) << latitude * -1;
		}
		if(longitude >= 0){
			out << '+';
			if(longitude < 10){
				out << '0';
			}
			if(longitude < 100){
				out << '0';
			}
			out << std::fixed << std::setprecision(7) << longitude;
		}
		else{
			out << '-';
			if(longitude > -10){
				out << '0';
			}
			if(longitude > -100){
				out << '0';
			}
			out << std::fixed << std::setprecision(7) << longitude * -1;
		}
		out << ' ' << cityStr();
		out << species.substr(0, 20);
		if(species.length() < 20){
			out << std::string(20 - species.length(), ' ');
		}
		out << tagNum;
		/*
		for(int index = 0; index < 20; ++index){
			if(index < species.length()){
				out << species[index];
			}
			else{
				out << ' ';
			}
		}
		for(int index = 0; index < 6; ++index){
			if(index < tagNum.length()){
				out << tagNum[index];
			}
			else{
				out << ' ';
			}
		}
		*/
}
std::string SightingData::timeStr(){
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(2) << hour << ':' << std::setw(2) << minute << ':' << std::setw(2) << second;
	return ss.str();
}
std::string SightingData::dateStr(){
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << year << '-' << std::setw(2) << month << '-' << std::setw(2) << day;
	return ss.str();
}
std::string SightingData::cityStr(){
	std::string rtn = city.substr(0,30);
	size_t index = city.find_last_not_of(' ');
	if(city.length() < 30 && index != std::string::npos){
		rtn += std::string(30 - index - 1, ' ');
	}
	rtn += state.substr(0,30);
	index = state.find_last_not_of(' ');
	if(state.length() < 30 && index != std::string::npos){
		rtn += std::string(30 - index - 1, ' ');
	}
	rtn += country.substr(0,30);
	index = country.find_last_not_of(' ');
	if(country.length() < 30 && index != std::string::npos){
		rtn += std::string(30 - index - 1, ' ');
	}
	for(int index = 0; index < rtn.length(); ++index){
		if(rtn[index] >= 'a' && rtn[index] <= 'z'){
			rtn[index] -= ('a'-'A');
		}
	}
	return rtn;
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
		out << "     Tag ID: " << sighting.tagNum;
	}
	out << "\n" << sighting.weather;
	return out;
}
bool Sighting::isTagged(){
	return tagNum.length() != 0;
}
bool Sighting::sameSpecies(const std::string& other){
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
std::ostream& operator<<(std::ostream& out, const SightingData& sighting){
	out << "Sighting ID: " << sighting.id << "     Reporter: " << sighting.reporter << "     Date: "
		<< std::setfill('0') << std::setw(2)
		<< sighting.year << '-' << std::setw(2) << sighting.month << '-' << std::setw(2) << sighting.day << "     Time: "
		<< std::setw(2) << sighting.hour << ':' << std::setw(2) << sighting.minute << ':' << std::setw(2) << sighting.second << std::endl;

	out << "Location: ";
	if(sighting.latitude > 0 || sighting.latitude < 0 || sighting.longitude > 0 || sighting.longitude < 0){
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
		out << "     Tag ID: " << sighting.tagNum;
	}
	out << "\n" << sighting.weather;
	return out;
}