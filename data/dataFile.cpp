#include "dataFile.h"
unsigned int DataFile::seqNumber = 6;
std::string DataFile::exportSightings(std::map<unsigned int, Sighting>& sightings, std::map<std::string, Butterfly>& tags,
							 std::map<std::string, std::vector<Sighting*> > tagSightings,
							 std::map<std::string, std::vector<Sighting*> > locationSightings){
	std::string line;
	std::string path;
	std::cout << "Enter path to export file (directory structure must exist)\n: ";
	std::getline(std::cin, path);
	std::ofstream outFile;
	outFile.open(path, std::ofstream::trunc);
	unsigned int numRecords = 0;

	SightingData data;

	std::string prompt, city, state, country, tagNum, firstDate, lastDate;

	if(outFile.is_open()){
		line = "";
		prompt = "Enter selection: ";
		while(line.length() < 1 && !(line[0] >= '1' && line[0] <= '4')){
			std::cout << "FilePath: " << path << "\n\n"
					  << "Export Menu:\n"
					  << "1. Export All Sightings\n"
					  << "2. Export Sightings for Location\n"
					  << "3. Export Sightings for Tag\n"
					  << "4. Cancel\n\n";
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
					std::cout << "Enter State: ";
					std::getline(std::cin, state);
					std::cout << "Enter Country: ";
					std::getline(std::cin, country);
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
					std::cout << "Enter Tag Number (Blank for untagged): ";
					std::getline(std::cin, line);
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
						line = "UNTAGGED";
						return "Sightings for Tag " + line + " exported to " + path;
					}
					else{
						return "No sightings found for Tag# " + tagNum + ".";
					}
				}
				break;
			case '4':
				return "Export cancelled!";
		};
	}
	else{
		return "Export file " + line + " not found.\nPlease ensure directory structure exists.";
	}
}
std::string DataFile::import(std::map<unsigned int, Sighting>& sightings,
							 std::map<std::string, Butterfly>& tags,
							 std::map<std::string, std::vector<Sighting*> > tagSightings,
							 std::map<std::string, std::vector<Sighting*> > userSightings,
							 std::map<std::string, std::vector<Sighting*> > dateSightings,
							 std::map<std::string, std::vector<Sighting*> > locationSightings){

}