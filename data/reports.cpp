#include "reports.h"
double Reports::latLongDistance(double lat1, double long1, double lat2, double long2, bool km){
	double radConvert = 3.1415926535 / 180;
	double dlong = long2 * radConvert - long1 * radConvert;
	double dlat = lat2 * radConvert - lat1 * radConvert;
	double sin1 = std::sin(dlat/2);
	double sin2 = std::sin(dlong/2);

	double a = sin1 * sin1 + std::cos(lat1 * radConvert) * std::cos(lat2 * radConvert) * sin2 * sin2;
	double c = 2 * std::atan2(std::sqrt(a), sqrt(1 - a));
	if(km){
		return c * 6373.0;//	6373 is approx radius of Earth in km
	}
	return c * 3961.0;	//	3961 is approx radius of Earth in miles
}
std::string Reports::hotspot(std::map<unsigned int, Sighting>& sightings){
	/*
		Read and error check lat/long
		Read and error check distance
		Loop through sightings until distance between it and lat/long <= distance
	*/
	std::string line = "";
	std::string prompt = "";
	double latitude;
	double longitude;
	double distance;
	bool valid = false;
	bool dotFound = false;
	bool signFound = false;
	std::stringstream ss;
	prompt = "Monarchy Butterfly Tracking System\nHotspot Report\n\nEnter Information or \"exit\" to cancel.\nEnter latitude: ";
	while(!valid){
		std::cout << std::string(100,'\n');
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Hotspot Report Cancelled.";
		}
		valid = true;
		dotFound = false;
		signFound = false;
		if(line.length() < 1){
			valid = false;
			prompt = "Latitude must not be blank\nEnter latitude: ";
			continue;
		}
		for(int index = 0; valid && index < line.length(); ++index){
			if(line[index] == '+' || line[index] == '-'){
				if(!signFound){
					signFound = true;
				}
				else{
					valid = false;
					prompt = "Latitude must be a number.\nEnter latitude: ";
				}
			}
			else if(line[index] == '.'){
				if(!dotFound){
					dotFound = true;
				}
				else{
					valid = false;
					prompt = "Latitude must be a number.\nEnter latitude: ";
				}
			}
			else if(!(line[index] >= '0' && line[index] <= '9')){
				prompt = "Monarchy Butterfly Tracking System\nHotspot Report\n\nEnter Information or \"exit\" to cancel.\nLatitude must be a number.\nEnter latitude: ";
				valid = false;
				continue;
			}
		}
		ss.str(line);
		ss.seekg(0);
		ss.clear();
		ss >> latitude;
		if(latitude < -90 || latitude > 90){
			valid = false;
			prompt = "Monarchy Butterfly Tracking System\nHotspot Report\n\nEnter Information or \"exit\" to cancel.\nLatitude must be between -90 and 90\nEnter latitude: ";
		}
	}
	valid = false;
	prompt = "\nEnter longitude: ";
	while(!valid){
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Hotspot Report Cancelled.";
		}
		valid = true;
		dotFound = false;
		signFound = false;
		if(line.length() < 1){
			valid = false;
			prompt = "Longitude must not be blank.\nEnter longitude: ";
			continue;
		}
		for(int index = 0; valid && index < line.length(); ++index){
			if(line[index] == '+' || line[index] == '-'){
				if(!signFound){
					signFound = true;
				}
				else{
					valid = false;
					prompt = "Longitude must be a number.\nEnter longitude: ";
				}
			}
			else if(line[index] == '.'){
				if(!dotFound){
					dotFound = true;
				}
				else{
					valid = false;
					prompt = "Longitude must be a number.\nEnter longitude: ";
				}
			}
			else if(!(line[index] >= '0' && line[index] <= '9')){
				prompt = "Longitude must be a number.\nEnter longitude: ";
				valid = false;
				continue;
			}
		}
		ss.str(line);
		ss.seekg(0);
		ss.clear();
		ss >> longitude;
		if(longitude < -180 || longitude > 180){
			valid = false;
			prompt = "Longitude must be between -180 and 180\nEnter longitude: ";
		}
	}
	valid = false;
	prompt = "\nEnter radius (miles): ";
	while(!valid){
		std::cout << prompt;
		std::getline(std::cin, line);
		if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
			(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
			(line[3] == 't' || line[3] == 'T')){
			return "Hotspot Report Cancelled.";
		}
		valid = true;
		dotFound = false;
		for(int index = 0; valid && index < line.length(); ++index){
			if(line[index] == '.'){
				if(!dotFound){
					dotFound = true;
				}
				else{
					valid = false;
					prompt = "Distance must be a number.\nEnter radius (miles): ";
				}
			}
			else if(!(line[index] >= '0' && line[index] <= '9')){
				prompt = "Distance must be a number.\nEnter radius (miles): ";
				valid = false;
				continue;
			}
		}
		ss.str(line);
		ss.seekg(0);
		ss.clear();
		ss >> distance;
		if(distance < 1){
			valid = false;
			prompt = "Radius must be greater than 0.\nEnter radius (miles): ";
		}
		if(distance > 1300){
			valid = false;
			prompt = "Radius must be less than 1300 (roughly half the circumference of Earth in miles)\nEnter radius (miles): ";
		}
	}

	std::map<unsigned int, Sighting>::iterator iter = sightings.begin();
	SightingData data;
	unsigned int numFound = 0;
	while(iter != sightings.end()){
		data = iter->second.getData();
		++iter;
		if(data.latitude  != 0 || data.longitude != 0){
			if(latLongDistance(data.latitude, data.longitude, latitude, longitude, false) <= distance){
				std::cout << data << std::endl;
				std::cout << "Distance: " << latLongDistance(data.latitude, data.longitude, latitude, longitude, false) << " miles\n\n";
				if(++numFound % 4 == 0 && iter != sightings.end()){
					std::cout << "\nPress enter for more or type \"exit\" to quit: ";
					std::getline(std::cin, line);
					if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
						(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
						(line[3] == 't' || line[3] == 'T')){
						return "Hotspot Report Cancelled.";
					}
				}

			}
		}
	}
	std::cout << "\n";
	std::cout << numFound << " sightings found within " << distance << " miles of " << latitude << ", " << longitude << '\n';
	std::cout << "Press enter to continue: ";
	std::getline(std::cin, line);
	return "Hotspot Report Completed";
}
std::string Reports::migration(std::map<std::string, std::vector<Sighting*> >& dateSightings, std::map<std::string, Butterfly>& tags){
	std::string tagNum = "";
	std::string line;
	double lastLat = 0.0;
	double lastLong = 0.0;
	double distance = 0.0;
	double totalDistance = 0.0;
	unsigned int mostVisitNum = 0;
	SightingData data;
	SightingData mostVisited;
	std::map<std::string, unsigned int> frequency;
	std::map<std::string, std::vector<Sighting*> >::iterator dateIter = dateSightings.begin();
	std::map<std::string, SightingData> timeSightings;
	std::map<std::string, SightingData>:: iterator timeIter;
	unsigned int numShown = 0;
	bool validInput = false;
	unsigned int totalSightings = 0;


	std::string prompt = "Monarchy Butterfly Tracking System\nMigration Report\n\nEnter Tag ID (\"exit\" to cancel): ";
	while(!validInput){
		std::cout << std::string(100,'\n');
		std::cout << prompt;
		std::getline(std::cin, tagNum);
		if(tagNum.length() == 4 && (tagNum[0] == 'e' || tagNum[0] == 'E') &&
			(tagNum[1] == 'x' || tagNum[1] == 'X') && (tagNum[2] == 'i' || tagNum[2] == 'I') &&
			(tagNum[3] == 't' || tagNum[3] == 'T')){
			return "Migration Report Cancelled.";
		}
		validInput = true;
		if(tagNum.length() == 0){
			validInput = false;
			prompt = "Monarchy Butterfly Tracking System\nMigration Report\n\nTag ID Required.\nEnter Tag ID (\"exit\" to cancel): ";
		}
		else if(tags.find(tagNum) == tags.end()){
			validInput = false;
			prompt = "Monarchy Butterfly Tracking System\nMigration Report\n\nTag Not Found\nEnter Tag ID (\"exit\" to cancel): ";
		}
	}
	std::cout << "\n\n";
	while(dateIter != dateSightings.end()){
		for(int index = 0; index < dateIter->second.size(); ++index){
			data = dateIter->second[index]->getData();
			if(data.tagNum.compare(tagNum) == 0){
				++totalSightings;
				if(data.cityStr().find_first_not_of(' ') != std::string::npos){
					incrementFrequency(frequency, data.cityStr());
					if(frequency[data.cityStr()] > mostVisitNum){
						mostVisitNum = frequency[data.cityStr()];
						mostVisited = data;
					}
				}
			}
		}
		++dateIter;
	}
	dateIter = dateSightings.begin();
	while(dateIter != dateSightings.end()){
		timeSightings.clear();
		for(int index = 0; index < dateIter->second.size(); ++index){
			data = dateIter->second[index]->getData();
			if(data.tagNum.compare(tagNum) == 0){
				timeSightings[data.timeStr()] = dateIter->second[index]->getData();
			}
		}
		timeIter = timeSightings.begin();
		while(timeIter != timeSightings.end()){
			data = timeIter->second;
			std::cout << "Date: " << data.dateStr() << "          Time: " << data.timeStr() << '\n';
			std::cout << "Location: ";
			if(data.latitude >= 0){
				std::cout << "+";
			}
			std::cout << std::setw(7) << std::fixed << std::setfill('0') << data.latitude << ", ";
			if(data.longitude >= 0){
				std::cout << "+";
			}
			std::cout << std::setw(7) << std::fixed << data.longitude <<"          ";
			if(data.city.length() > 0){
				std::cout << data.city << ", " << data.state << ", " << data.country;
			} 
			std::cout << '\n';
			if(data.latitude != 0 || data.longitude != 0){
				if(lastLat != 0 || lastLong != 0){
					distance = latLongDistance(lastLat, lastLong, data.latitude, data.longitude, false);
					totalDistance += distance;
				}
				lastLat = data.latitude;
				lastLong = data.longitude;
			}
			std::cout << "Distance since last known location: " << distance << " miles\n";
			if(data.cityStr().find_first_not_of(' ') != std::string::npos){
				std::cout << "Frequency found in this city: " << frequency[data.cityStr()] << " of " << totalSightings << " sightings.\n";
			}
			std::cout << std::endl << std::endl;
			if(++numShown % 4 == 0){
				std::cout << "Press enter for more, or type \"exit\" to cancel: ";
				std::getline(std::cin, line);
				if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
					(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
					(line[3] == 't' || line[3] == 'T')){
					return "Migration Report Cancelled";
				}
			}
			++timeIter;
		}
		++dateIter;
	}
	if(totalDistance > 0)
		std::cout <<"\nTotal recorded distance: " << totalDistance << " miles.";
	if(mostVisitNum > 0)
		std::cout << "\nMost visited city: " << mostVisited.city << ", " << mostVisited.state << ", " << mostVisited.country << " with " << 
					mostVisitNum << " visits out of " << totalSightings << " sightings.";
	std::cout << "\n\nPress enter to continue: ";
	std::getline(std::cin, line);
	return "Migration Report Completed";
}
void Reports::incrementFrequency(std::map<std::string, unsigned int>& frequency, std::string location){
	if(frequency.find(location) == frequency.end()){
		frequency[location] = 0;
	}
	++frequency[location];
}
std::string Reports::userRankings(std::map<std::string, std::vector<Sighting*> >& userSightings, std::map<std::string, User>& users, std::string currentUser){
	std::cout << std::string(100,'\n');
	std::cout << "Monarchy Butterfly Tracking System\nUser Rankings:\n\n1 point per sighting, 5 points per different location.\n\n";
	unsigned int first = 0, second = 0, third = 0, user = 0, current = 0;
	unsigned int sfirst, ssecond, sthird, suser, scurrent;
	std::string user1 = "", user2 = "", user3 = "";
	std::string line;
	std::map<std::string, std::map<std::string, bool> > locations;
	std::map<std::string, std::vector<Sighting*> >::iterator iter = userSightings.find(currentUser);
	SightingData data;
	if(iter != userSightings.end()){
		user = suser = iter->second.size();
		for(int index = 0; index < userSightings[currentUser].size(); ++index){
			data = iter->second[index]->getData();
			if(data.city.length() > 0){
				if(locations[currentUser].find(data.cityStr()) == locations[currentUser].end()){
					locations[currentUser][data.cityStr()] = true;
					user += 5;
				}
			}
		}
	}
	if(user > 0){
		first = user;
		user1 = currentUser;
		sfirst = suser;
	}
	iter = userSightings.begin();
	while(iter != userSightings.end()){
		if(iter->first.compare(currentUser) != 0){
			scurrent = current = iter->second.size();
			if(current > 0){
				for(int index = 0; index < userSightings[iter->first].size(); ++index){
					data = iter->second[index]->getData();
					if(data.city.length() > 0){
						if(locations[iter->first].find(data.cityStr()) == locations[iter->first].end()){
							locations[iter->first][data.cityStr()] = true;
							current += 5;
						}
					}
				}
				if(current > first){
					if(user1.compare(iter->first) != 0){
						user2 = user1;
						second = first;
						ssecond = sfirst;
					}
					user1 = iter->first;
					first = current;
					sfirst = scurrent;
				}
				else if(current > second){
					if(user2.compare(iter->first) != 0){
						user3 = user2;
						third = second;
						sthird = ssecond;
					}
					user2 = iter->first;
					second = current;
					ssecond = scurrent;
				}
				else if(current > third){
					user3 = iter->first;
					third = current;
					sthird = scurrent;
				}
			}
		}
		++iter;
	}
	std::cout << "\n";
	if(first > 0){
		std::cout << "1st Place: " << user1 << "\n " << first << " points - " << sfirst << " sightings in " << (first - sfirst) / 5 << " different locations.\n\n";
	}
	if(second > 0){
		std::cout << "2nd Place: " << user2 << "\n " << second << " points - " << ssecond << " sightings in " << (second -ssecond) / 5 << " different locations.\n\n";
	}
	if(third > 0){
		std::cout << "3rd Place: " << user3 << "\n " << third << " points - " << sthird << " sightings in " << (third - sthird) / 5 << " different locations.\n\n";
	}
	if(user > 0){
		std::cout << "\nYour score: " << user << " points - " << suser << " sightings in " << (user - suser) / 5 << " different locations.\n";
	}
	if(first == 0){
		std::cout << "No users have scores yet.  Go watch for butterflies!";
	}
	std::cout << "\n\nPress Enter to continue: ";
	std::getline(std::cin, line);
	return "User Ranking Report Completed";
}
std::string Reports::speciesLocation(std::map<unsigned int, Sighting>& sightings){
	std::string prompt = "Monarchy Butterfly Tracking System\nSpecies Location Report:\n\nEnter Species or \"exit\" to cancel: ";
	std::string species, line;
	std::map<std::string, bool> tagList;
	std::map<std::string, unsigned int> locationsFound; 
	std::string loc1 = "", loc2 = "", loc3 = "", current = "", currentShort = "";
	unsigned int num1 = 0;
	unsigned int num2 = 0;
	unsigned int num3 = 0;
	bool valid = false;
	SightingData data;
	unsigned int counter = 0;
	while(!valid){
		std::cout << std::string(100, '\n');
		std::cout << prompt;
		std::getline(std::cin, species);
		if(species.length() == 4 && (species[0] == 'e' || species[0] == 'E') &&
			(species[1] == 'x' || species[1] == 'X') && (species[2] == 'i' || species[2] == 'I') &&
			(species[3] == 't' || species[3] == 'T')){
			return "Species Location Report Cancelled";
		}
		valid = true;
		if(species.length() < 1){
			valid = false;
			prompt = "Monarchy Butterfly Tracking System\nSpecies Location Report:\n\nSpecies cannot be blank.\nEnter Species or \"exit\" to cancel: ";
			continue;
		}
		for(std::map<unsigned int, Sighting>::iterator iter = sightings.begin(); iter != sightings.end(); ++iter){
			if(iter->second.sameSpecies(species)){
				data = iter->second.getData();
				if(data.city.length() > 0){
					current = data.cityStr();
					currentShort = data.city + ", " + data.state + ", " + data.country;
					if(locationsFound.find(current) == locationsFound.end()){
						locationsFound[current] = 1;
					}
					else{
						++locationsFound[current];
					}
					if(locationsFound[current] > num1){
						if(currentShort.compare(loc1) != 0){
							num2 = num1;
							loc2 = loc1;
						}
						num1 = locationsFound[current];
						loc1 = currentShort;
					}
					else if(locationsFound[current] > num2){
						if(currentShort.compare(loc2) != 0){
							num3 = num2;
							loc3 = loc2;
						}
						num2 = locationsFound[current];
						loc2 = data.city + ", " + data.state + ", " + data.country;
					}
					else if(locationsFound[current] > num3){
						num3 = locationsFound[current];
						loc3 = data.city + ", " + data.state + ", " + data.country;
					}
				}
			}
		}
		if(locationsFound.size() < 1){
			valid = false;
			prompt = "Monarchy Butterfly Tracking System\nSpecies Location Report:\n\nSpecies not found.\nEnter Species or \"exit\" to cancel: ";
		}
	}
	std::cout << "Best locations to find " << species << " butterflies:\n";
	if(num1 > 0){
		std::cout << "1. " << loc1 << " with " << num1 << " tagged sightings\n";
	}
	if(num2 > 0){
		std::cout << "2. " << loc2 << " with " << num2 << " tagged sightings\n";
	}
	if(num3 > 0){
		std::cout << "3. " << loc3 << " with " << num3 << " tagged sightings\n";
	}
	std::cout << "\n\nEnter to continue: ";
	std::getline(std::cin, line);
	return "Species Location Report Completed.";
}
std::string Reports::sightingHistory(std::map<std::string, std::vector<Sighting*> >& dateSightings){
	std::map<std::string, std::vector<Sighting*> >::iterator sightingIter = dateSightings.begin();
	std::map<std::string, unsigned int> tagged;
	std::string line = "";
	SightingData data;
	unsigned int max = 0;
	while(sightingIter != dateSightings.end()){
		if(sightingIter->second.size() > max){
			max = sightingIter->second.size();
		}
		tagged[sightingIter->first] = 0;
		for(int index = 0; index < sightingIter->second.size(); ++index){
			if(sightingIter->second[index]->isTagged()){
				++tagged[sightingIter->first];
			}
		}
		++sightingIter;
	}
	sightingIter = dateSightings.begin();
	double sightingsPerChar = 60.0 / (double)max;
	unsigned int untagged = 0;
	std::stringstream ss;
	std::string numPer;
	std::cout << std::string(100, '\n');
	std::cout << "Monarchy Butterfly Tracking System\nButterfly Sighting History\n\n";
	std::cout << "KEY: TTT   = Tagged\n";
	std::cout << "     UU    = Untagged\n";
	std::cout << "     AAAAA = All\n";
	std::cout << "\n2 Dates display at a time, press enter for more or type \"exit\" to quit.\n\n";
	std::cout << std::string(10, ' ') << '0';
	for(unsigned int index = 0; index < 60; ++index){
		if(max > 10){
			if((index + 1) % 10 == 0){
				ss.str(std::string());
				ss.seekg(0);
				ss.clear();
				ss <<  (int)std::round(index / sightingsPerChar);
				numPer = ss.str();
				index += numPer.length() - 1;
				std::cout << numPer;
			}
			else{
				std::cout << ' ';
			}
		}
		else{
			if((int)(index / sightingsPerChar) > untagged){
				++untagged;
				ss.str(std::string());
				ss.seekg(0);
				ss.clear();
				ss << untagged;
				numPer = ss.str();
				index += numPer.length() - 1;
				std::cout << numPer;
			}
			else if(index == 59 && untagged < max){
				std::cout << max;
			}
			else{
				std::cout << ' ';
			}
		}
	}
	std::cout << std::endl;
	std::cout << "           " << std::string(65, '-') << '\n';
	untagged = 0;
	unsigned int numShown = 0;
	while(sightingIter != dateSightings.end()){
		untagged = sightingIter->second.size() - tagged[sightingIter->first];
		std::cout << "          |" << std::string(tagged[sightingIter->first] * sightingsPerChar, 'T') << '\n';
		std::cout << sightingIter->first << "|" << std::string(untagged * sightingsPerChar, 'U') << '\n';
		std::cout << "          |" << std::string(sightingIter->second.size() * sightingsPerChar, 'A') << '\n';
		std::cout << "          |\n";
		++sightingIter;
		if(++numShown % 2 == 0){
			std::getline(std::cin, line);
			if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
				(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
				(line[3] == 't' || line[3] == 'T')){
				return "Butterfly Sightings History Cancelled.";
			}
		}
	}
	std::cout << "           " << std::string(65, '-') << "\n\n";
	std::cout << "Press enter to continue: ";
	std::getline(std::cin, numPer);
	return "Butterfly Sightings History Completed";
	/*
		Default cmd window width = 80chars
		Date is 10 chars wide
		1234-67-90: 

	*/
}