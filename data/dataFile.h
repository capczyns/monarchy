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
#include <ctime>
#include "storage.h"
#include "../system.h"
class DataFile{
private:
	unsigned static int seqNumber;
	static void clear();
	unsigned static int parseHeader(std::string& header);
	static std::string parseLine(std::string& line, SightingData& sightingData, bool& valid);
	static void prepStream(std::stringstream& ss, std::string str);
	static void addError(std::map<std::string, int>& errors, std::string error);
public:
	static std::string exportSightings(std::map<unsigned int, Sighting>& sightings, std::map<std::string, Butterfly>& tags,
							  std::map<std::string, std::vector<Sighting*> >& tagSightings,
							 std::map<std::string, std::vector<Sighting*> >& locationSightings);
	static std::string import(std::map<unsigned int, Sighting>& sightings,
							  std::map<std::string, Butterfly>& tags,
							  std::map<std::string, std::vector<Sighting*> >& tagSightings,
							  std::map<std::string, std::vector<Sighting*> >& userSightings,
							  std::map<std::string, std::vector<Sighting*> >& dateSightings,
							  std::map<std::string, std::vector<Sighting*> >& locationSightings);
	static void setSeqNum(unsigned int next);
};
#endif
/*
	Sightings File Req:

		Header:
			HD
			spaces
			seq num
			spaces
			10 char date

		Entry:
			every entry is a new line
			every entry has at least 171 characters
			1 char entry type (S or T)
			1 space
			10 char username
			10 char date
			1 space
			8 char time
			1 space
			10 char latitude
			10 char longitude
			1 space
			30 char city
			30 char state
			30 char country
			20 char species
			at least 6 char tag (Any non-blank string)

		Trailing Record:
			TR
			spaces
			#entries
*/