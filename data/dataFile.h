#ifndef DATAFILE_H
#define DATAFILE_H
#include "sighting.h"
#include "butterfly.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <vector>
#include <fstream>
#include "storage.h"
class DataFile{
private:
	unsigned static int seqNumber;
	static void clear();
	unsigned static int parseHeader(std::string& header);
	static std::string parseLine(std::string& line, SightingData& sightingData, bool& valid);
public:
	static std::string exportSightings(std::map<unsigned int, Sighting>& sightings, std::map<std::string, Butterfly>& tags,
							  std::map<std::string, std::vector<Sighting*> > tagSightings,
							 std::map<std::string, std::vector<Sighting*> > locationSightings);
	static std::string import(std::map<unsigned int, Sighting>& sightings,
							  std::map<std::string, Butterfly>& tags,
							  std::map<std::string, std::vector<Sighting*> > tagSightings,
							  std::map<std::string, std::vector<Sighting*> > userSightings,
							  std::map<std::string, std::vector<Sighting*> > dateSightings,
							  std::map<std::string, std::vector<Sighting*> > locationSightings);
	static void setSeqNum(unsigned int next);
};
#endif