#include "dataFile.h"
unsigned int DataFile::seqNumber = 6;
void DataFile::setSeqNum(unsigned int next){
	seqNumber = next;
}
std::string DataFile::exportSightings(std::map<unsigned int, Sighting>& sightings, std::map<std::string, Butterfly>& tags,
							 std::map<std::string, std::vector<Sighting*> >& tagSightings,
							 std::map<std::string, std::vector<Sighting*> >& locationSightings){
	std::string line;
	std::string path;
	std::cout << "Enter path to export file, (directory structure must exist; \".txt\" added to the end automatically)\n: ";
	std::getline(std::cin, path);
	if(path.length() == 4 && (path[0] == 'e' || path[0] == 'E') &&
		(path[1] == 'x' || path[1] == 'X') && (path[2] == 'i' || path[2] == 'I') &&
		(path[3] == 't' || path[3] == 'T')){
		return "Export Cancelled";
	}
	path += ".txt";
	std::ofstream outFile;
	outFile.open(path, std::ofstream::app);
	unsigned int numRecords = 0;

	SightingData data;

	std::string prompt, city, state, country, tagNum, firstDate, lastDate;

	if(outFile.is_open()){
		outFile.close();
		line = "";
		prompt = "Enter selection: ";
		while(line.length() < 1 && !(line[0] >= '0' && line[0] <= '3')){
			std::cout << System::programTitle << "\n";
			std::cout << "Export Menu:\n"
					  << "FilePath: " << path << "\n"
					  << "1. Export All Sightings\n"
					  << "2. Export Sightings for Location\n"
					  << "3. Export Sightings for Tag\n"
					  << "0. Exit\n\n";
			std::cout << prompt;
			std::getline(std::cin, line);
			prompt = "Invalid option\nEnter selection: ";
		}
		switch(line[0]){
			case '1':
				{
					std::map<unsigned int, Sighting>::iterator iter = sightings.begin();
					std::map<unsigned int, Sighting>::iterator end = sightings.end();
					if(iter != end){
						data  = iter->second.getData();
						outFile.open(path, std::ofstream::trunc);
						outFile << "HD" << std::string(10, ' ');
						firstDate = data.dateStr();
						lastDate = data.dateStr();
						while(iter != end){
							data  = iter->second.getData();
							if(firstDate.compare(data.dateStr()) > 0){
								firstDate = data.dateStr();
							}
							if(lastDate.compare(data.dateStr()) < 0){
								lastDate = data.dateStr();
							}
							++iter;
						}
						iter = sightings.begin();
						outFile << firstDate << ' ' << lastDate << std::endl;
						while(iter != end){
							data = iter->second.getData();
							data.exportStr(outFile);
							outFile << std::endl;
							++iter;
							++numRecords;
						}
						outFile << "TR " << std::setfill('0') << std::setw(6) << numRecords;
						outFile.close();
						return "All sightings exported to " + path;
					}
					else{
						return "No sightings to export!";
					}
				}
				break;
			case '2':
				{
					std::cout << "Enter City: ";
					std::getline(std::cin, city);
					if(city.length() == 4 && (city[0] == 'e' || city[0] == 'E') &&
						(city[1] == 'x' || city[1] == 'X') && (city[2] == 'i' || city[2] == 'I') &&
						(city[3] == 't' || city[3] == 'T')){
						return "Export Cancelled";
					}
					std::cout << "Enter State: ";
					std::getline(std::cin, state);
					if(state.length() == 4 && (state[0] == 'e' || state[0] == 'E') &&
						(state[1] == 'x' || state[1] == 'X') && (state[2] == 'i' || state[2] == 'I') &&
						(state[3] == 't' || state[3] == 'T')){
						return "Export Cancelled";
					}
					std::cout << "Enter Country: ";
					std::getline(std::cin, country);
					if(country.length() == 4 && (country[0] == 'e' || country[0] == 'E') &&
						(country[1] == 'x' || country[1] == 'X') && (country[2] == 'i' || country[2] == 'I') &&
						(country[3] == 't' || country[3] == 'T')){
						return "Export Cancelled";
					}
					line = city.substr(0,30);
					if(city.length() < 30){
						line += std::string(30-city.length(), ' ');
					}
					line += state.substr(0,30);
					if(state.length() < 30){
						line += std::string(30-state.length(), ' ');
					}
					line += country.substr(0,30);
					if(country.length() < 30){
						line += std::string(30-country.length(), ' ');
					}
					for(int index = 0; index < 90; ++index){
						if(line[index] >= 'a' && line[index] <= 'z'){
							line[index] -= ('a'-'A');
						}
					}
					std::map<std::string, std::vector<Sighting*> >::iterator iter = locationSightings.find(line);
					if(iter != locationSightings.end() && iter->second.size() > 0){
						data = iter->second[0]->getData();
						firstDate = data.dateStr();
						lastDate = data.dateStr();
						for(int index = 1; index < iter->second.size(); ++index){
							data = iter->second[index]->getData();
							if(firstDate.compare(data.dateStr()) > 0){
								firstDate = data.dateStr();
							}
							if(lastDate.compare(data.dateStr()) < 0){
								lastDate = data.dateStr();
							}
						}
						outFile.open(path, std::ofstream::trunc);
						outFile << "HD" << std::string(10, ' ') << firstDate << ' ' << lastDate << std::string(6, ' ') << "Location: " << city << ' ' << state << ' ' << country << std::endl;
						for(int index = 0; index < iter->second.size(); ++index){
							data = iter->second[index]->getData();
							data.exportStr(outFile);
							outFile << std::endl;
							++numRecords;
						}
						outFile << "TR " << std::setfill('0') << std::setw(6) << numRecords;
						outFile.close();
						return "Sightings for " + city + " " + state + " " +country + " exported to " + path;
					}
					else{
						return "No sightings found for " + city + " " + state + " " + country + ".";
					}
				}
				break;
			case '3':
				{
					std::cout << "Enter Tag ID (Enter for untagged): ";
					std::getline(std::cin, line);
					if(line.length() == 4 && (line[0] == 'e' || line[0] == 'E') &&
						(line[1] == 'x' || line[1] == 'X') && (line[2] == 'i' || line[2] == 'I') &&
						(line[3] == 't' || line[3] == 'T')){
						return "Export Cancelled";
					}
					std::map<std::string, std::vector<Sighting*> >::iterator iter = tagSightings.find(line);
					if(iter != tagSightings.end() && iter->second.size() > 0){
						data = iter->second[0]->getData();
						firstDate = data.dateStr();
						lastDate = data.dateStr();
						for(int index = 1; index < iter->second.size(); ++index){
							data = iter->second[index]->getData();
							if(firstDate.compare(data.dateStr()) > 0){
								firstDate = data.dateStr();
							}
							if(lastDate.compare(data.dateStr()) < 0){
								lastDate = data.dateStr();
							}
						}
						outFile.open(path, std::ofstream::trunc);
						outFile << "HD" << std::string(10, ' ') << firstDate << ' ' << lastDate << std::string(6, ' ') << "Tag: ";
						if(line.length() > 0){
							outFile << line;
						}
						else{
							outFile << "UNTAGGED";
						}
						outFile << std::endl;
						for(int index = 0; index < iter->second.size(); ++index){
							data = iter->second[index]->getData();
							data.exportStr(outFile);
							outFile << std::endl;
							++numRecords;
						}
						outFile << "TR " << std::setfill('0') << std::setw(6) << numRecords;
						outFile.close();
						if(line.length() < 1){
							line = "UNTAGGED";
						}
						return "Sightings for Tag " + line + " exported to " + path;
					}
					else{
						return "No sightings found for Tag ID " + line + ".";
					}
				}
				break;
			case '0':
				return "Export cancelled!";
		};
	}
	else{
		return "Export file " + line + " not found.\nPlease ensure directory structure exists.";
	}
}
std::string DataFile::import(std::map<unsigned int, Sighting>& sightings,
							 std::map<std::string, Butterfly>& tags,
							 std::map<std::string, std::vector<Sighting*> >& tagSightings,
							 std::map<std::string, std::vector<Sighting*> >& userSightings,
							 std::map<std::string, std::vector<Sighting*> >& dateSightings,
							 std::map<std::string, std::vector<Sighting*> >& locationSightings){
	std::string line, path, temp;
	std::cout << System::programTitle << "\nFile Import\n\n";
	std::cout << "Enter path to import file: ";
	std::getline(std::cin, path);
	if(path.length() == 4 && (path[0] == 'e' || path[0] == 'E') &&
		(path[1] == 'x' || path[1] == 'X') && (path[2] == 'i' || path[2] == 'I') &&
		(path[3] == 't' || path[3] == 'T')){
		return "Import Cancelled";
	}
	std::ifstream inFile(path);
	bool trFound = false;
	std::string hd;
	unsigned int seqNum = 0;
	unsigned int numEntries = 0;
	unsigned int numReported = 0;
	ButterflyData butterfly;
	SightingData sighting;
	bool tagging = false;
	int numStart, numEnd;
	int successfulSightings = 0;
	int successfulTaggings = 0;
	size_t index;
	bool dotFound, valid;

	SystemState saveState;
	std::map<std::string, int> errors;

	std::map<std::string, Butterfly>::iterator tagIter;
	Sighting* addr;
	Sighting sight;


	std::time_t epochSec = std::time(NULL);
	std::tm * curTime = std::localtime(&epochSec);
	std::stringstream ss;
	if(inFile.is_open()){
		std::getline(inFile, hd);
		seqNum = parseHeader(hd);
		if(seqNum == 0){
			return "Error: Header invalid.";
		}
		if(seqNum != seqNumber){
			prepStream(ss, std::string());
			ss << "Error: sequence number " << seqNumber << " expected, but number " << seqNum << " found.";
			return(ss.str());
		}
		while(!trFound && std::getline(inFile, line)){
			sighting = SightingData();
			if(line.length() >= 2 && line.substr(0,2).compare("TR") == 0){
				trFound = true;
				index = 2;
				while(index < line.length() && line[index] == ' '){
					++index;
				}
				numStart = index;
				while(index < line.length() && (line[index] >= '0' && line[index] <= '9')){
					++index;
				}
				numEnd = index;
				while(index < line.length() && line[index] == ' '){
					++index;
				}
				if(index < line.length()){
					errors["Trailing Record Invalid"] = 1;
				}
				else{
					saveState.seqNum = ++seqNumber;
					Storage::saveState(saveState);
					prepStream(ss, line.substr(numStart, numEnd - numStart));
					ss >> numReported;
					if(numReported != numEntries){
						ss.str(std::string());
						ss.seekg(0);
						ss.clear();
						ss << numReported << " entries in Trailing Record but " << numEntries << " in file.";
						errors[ss.str()] = -1;
					}
				}
			}
			else if(line.length() > 1 && (line[0] == 'S' || line[0] == 'T')){
				tagging = line[0] == 'T';
				++numEntries;
				if(line.length() < 2 || line[1] != ' '){
					addError(errors, "No space after entry type");
					continue;
				}
				sighting.reporter = line.substr(2,10);
				if(sighting.reporter.length() < 10){
					addError(errors, "Line too short");
					continue;
				}
				if(sighting.reporter.find_last_not_of(' ') == std::string::npos){
					addError(errors, "No reporter/tagger specified");
					continue;
				}
				sighting.reporter = sighting.reporter.substr(0, sighting.reporter.find_last_not_of(' ') + 1);
				if(line.length() < 171){
					addError(errors, "Line too short");
					continue;
				}
				temp = line.substr(12, 4);
				if((temp.compare(std::string(4, '9')) > 0) ||
					temp.compare(std::string(4, '0')) < 0){
					addError(errors, "Invalid year");
					continue;
				}
				prepStream(ss, temp);
				ss >> sighting.year;
				temp = line.substr(17, 2);
				if((temp.compare(std::string(2, '9')) > 0) ||
					temp.compare(std::string(2, '0')) < 0){
					addError(errors, "Invalid month");
					continue;
				}
				prepStream(ss, temp);
				ss >> sighting.month;
				if(sighting.month < 1 || sighting.month > 12){
					addError(errors, "Invalid Month");
					continue;
				}
				temp = line.substr(20, 2);
				if((temp.compare(std::string(2, '9')) > 0) ||
					temp.compare(std::string(2, '0')) < 0){
					addError(errors, "Invalid day");
					continue;
				}
				prepStream(ss, temp);
				ss >> sighting.day;
				if(sighting.day < 1 || sighting.day > 31){
					addError(errors, "Invalid day");
					continue;
				}
				else{
					if(sighting.month == 2){
						if(sighting.day > 29){
							addError(errors, "Invalid day");
							continue;
						}
						if(sighting.year % 4 != 0 && sighting.day > 28){
							addError(errors, "Invalid day");
							continue;
						}
					}
					else if((sighting.month == 4 || sighting.month == 6 || sighting.month == 9 ||
							 sighting.month == 11) && sighting.day > 30){
						addError(errors, "Invalid day");
						continue;
					}
				}
				if(sighting.year > 1900 + curTime->tm_year ||
					(sighting.year == 1900 + curTime->tm_year && sighting.month > curTime->tm_mon + 1) ||
					(sighting.year == 1900 + curTime->tm_year && sighting.month == curTime->tm_mon + 1 && sighting.day > curTime->tm_mday)){
					addError(errors, "Future date");
					continue;
				}
				if(sighting.year < 1900){
					addError(errors, "Date before 1900");
				}
				//	Date is valid up to this point

				temp = line.substr(23, 2);
				if((temp.compare(std::string(2, '9')) > 0) ||
					temp.compare(std::string(2, '0')) < 0){
					addError(errors, "Invalid hour");
					continue;
				}
				prepStream(ss, temp);
				ss >> sighting.hour;
				if(sighting.hour < 0 || sighting.hour > 23){
					addError(errors, "Invalid hour");
				}

				temp = line.substr(26, 2);
				if((temp.compare(std::string(2, '9')) > 0) ||
					temp.compare(std::string(2, '0')) < 0){
					addError(errors, "Invalid minute");
					continue;
				}
				prepStream(ss, temp);
				ss >> sighting.minute;
				if(sighting.minute < 0 || sighting.minute > 59){
					addError(errors, "Invalid minute");
					continue;
				}

				temp = line.substr(29, 2);
				if((temp.compare(std::string(2, '9')) > 0) ||
					temp.compare(std::string(2, '0')) < 0){
					addError(errors, "Invalid second");
					continue;
				}
				prepStream(ss, temp);
				ss >> sighting.second;
				if(sighting.second < 0 || sighting.second > 59){
					addError(errors, "Invalid second");
					continue;
				}

				temp = line.substr(32, 11);
				if(!(temp[0] == '+' || temp[0] == '-')){
					addError(errors, "Invalid latitude");
					continue;
				}
				dotFound = false;
				valid = true;
				for(int index = 1; valid && index < 11; ++index){
					if(temp[index] == '.'){
						if(dotFound){
							valid =false;
						}
						dotFound = true;
					}
					else if(temp[index] < '0' || temp[index] > '9'){
						valid = false;
					}
				}
				if(!valid){
					addError(errors, "Invalid latitude");
					continue;
				}
				prepStream(ss, temp);
				ss >> sighting.latitude;
				if(sighting.latitude < -90 || sighting.latitude > 90){
					addError(errors, "Invalid latitude");
					continue;
				}

				temp = line.substr(43, 11);
				if(!(temp[0] == '+' || temp[0] == '-')){
					addError(errors, "Invalid longitude");
					continue;
				}
				dotFound = false;
				valid = true;
				for(int index = 1; valid && index < 11; ++index){
					if(temp[index] == '.'){
						if(dotFound){
							valid =false;
						}
						dotFound = true;
					}
					else if(temp[index] < '0' || temp[index] > '9'){
						valid = false;
					}
				}
				if(!valid){
					addError(errors, "Invalid longitude");
					continue;
				}
				prepStream(ss, temp);
				ss >> sighting.longitude;
				if(sighting.longitude < -180 || sighting.longitude > 180){
					addError(errors, "Invalid longitude");
					continue;
				}

				//	Everything up to City is valid
				sighting.city = line.substr(55, 30);
				index = sighting.city.find_last_not_of(' ');
				if(index == std::string::npos){
					sighting.city = "";
				}
				else{
					sighting.city = sighting.city.substr(0, index + 1);
				}

				sighting.state = line.substr(85, 30);
				index = sighting.state.find_last_not_of(' ');
				if(index == std::string::npos){
					sighting.state = "";
				}
				else{
					sighting.state = sighting.state.substr(0, index + 1);
				}

				sighting.country = line.substr(115, 30);
				index = sighting.country.find_last_not_of(' ');
				if(index == std::string::npos){
					sighting.country = "";
				}
				else{
					sighting.country = sighting.country.substr(0, index + 1);
				}

				if((sighting.latitude == 0 && sighting.longitude == 0) && 
					(sighting.city.length() < 1 && sighting.state.length() < 1 && sighting.country.length() < 1)){
					addError(errors, "No Location Specified");
					continue;
				}

				sighting.species = line.substr(145, 20);
				index = sighting.species.find_last_not_of(' ');
				if(index == std::string::npos){
					addError(errors, "No Species Specified");
					continue;
				}
				else{
					sighting.species = sighting.species.substr(0, index + 1);
				}
				sighting.tagNum = line.substr(165,6);
				index = sighting.tagNum.find_last_not_of(' ');
				if(tagging && index == std::string::npos){
					addError(errors, "Tagging with no tag number specified");
				}
				else if(index == std::string::npos){
					sighting.tagNum = "";
				}
				else{
					sighting.tagNum = sighting.tagNum.substr(0, index + 1);
				}
				if(tagging){
					tagIter = tags.find(sighting.tagNum);
					if(tagIter != tags.end()){
						addError(errors, "Tag already in use");
						continue;
					}
					else if(tagIter == tags.end()){
						butterfly = ButterflyData(sighting);
						tags[sighting.tagNum] = Butterfly(butterfly);
						Storage::saveTag(tags[sighting.tagNum]);
						++successfulTaggings;
					}
					else{
						addError(errors, "Tag already in use");
						continue;
					}
				}
				else{
					if(sighting.tagNum.length() > 0){
						tagIter = tags.find(sighting.tagNum);
						if(tagIter == tags.end()){
							addError(errors, "Tagging not logged yet");
							continue;
						}
						if(sighting.species.compare(tagIter->second.getSpecies()) != 0){
							addError(errors, "Species of sighting does not match tagged species");
							continue;
						}
					}
					sighting.id = 0;
					sight = Sighting(sighting);
					sighting = sight.getData();
					sightings[sighting.id] = Sighting(sighting);
					Storage::saveSighting(sightings[sighting.id]);
					addr = &sightings[sighting.id];
					
					tagSightings[sighting.tagNum].push_back(addr);
					userSightings[sighting.reporter].push_back(addr);
					dateSightings[sighting.dateStr()].push_back(addr);
					locationSightings[sighting.cityStr()].push_back(addr);

					++successfulSightings;

				}
				/*
sightings
tags
tagSightings
userSightings
dateSightings
locationSightings

tagIter
indexingIter
				*/
			}
			else{
				addError(errors, "Unknown Entry Type");
				continue;
			}
		}
	}
	else{
		return "Could not open file " + path;
	}
	
	prepStream(ss, std::string());
	ss << "Import Complete... Successful Sightings: " << successfulSightings << ",     Successful Taggings: " << successfulTaggings << std::endl;
	ss << "Errors:\n";
	std::map<std::string, int>::iterator iter = errors.begin();
	if(iter == errors.end()){
		ss << "NONE";
	}
	else{
		while(iter != errors.end()){
			ss << iter->first;
			if(iter->second > 0){
				ss << ": " << iter->second;
			}
			ss << std::endl;
			++iter;
		}
	}
	return ss.str();
}
void DataFile::prepStream(std::stringstream& ss, std::string str){
	ss.str(str);
	ss.seekg(0);
	ss.clear();
}
void DataFile::addError(std::map<std::string, int>& errors, std::string error){
	std::map<std::string, int>::iterator iter = errors.find(error);
	if(iter == errors.end()){
		errors[error] = 1;
	}
	else{
		++errors[error];
	}
}
unsigned int DataFile::parseHeader(std::string& header){
	std::string line = "";
	std::string hd = "";
	std::string seqNum = "";
	std::string date = "";

	std::string year = "";
	std::string month = "";
	std::string day = "";
	std::time_t epochSec = std::time(NULL);
	std::tm * curTime = std::localtime(&epochSec);

	int index = 0;
	while(index < header.length() && header[index] != ' '){
		hd += header[index++];
	}
	if(hd.length() != 2){
		return 0;
	}
	if(hd[0] != 'H' || hd[1] != 'D'){
		return 0;
	}
	while(index < header.length() && header[index] == ' '){
		++index;
	}
	while(index < header.length() && (header[index] >= '0' && header[index] <= '9')){
		seqNum += header[index++];
	}
	if(seqNum.length() < 1){
		return 0;
	}
	std::stringstream ss(seqNum);
	unsigned int seqNumm = 0;
	ss.seekg(0);
	ss.clear();
	ss >> seqNumm;

	while(index < header.length() && header[index] == ' '){
		++index;
	}
	while(index < header.length() && ((header[index] >= '0' && header[index] <= '9') || header[index] == '-')){
		date += header[index++];
	}
	if(date.length() != 10){
		return 0;
	}
	for(int i = 0; i < 4; ++i){
		if(date[i] < '0' || date[i] > '9'){
			return 0;
		}
		year += date[i];
	}
	for(int i = 5; i < 7; ++i){
		if(date[i] < '0' || date[i] > '9'){
			return 0;
		}
		month += date[i];
	}
	for(int i = 5; i < 7; ++i){
		if(date[i] < '0' || date[i] > '9'){
			return 0;
		}
		day += date[i];
	}
	while(index < header.length() && header[index] == ' '){
		++index;
	}

	return seqNumm;
}
