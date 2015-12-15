#ifndef REPORTS_H
#define REPORTS_H
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <iomanip>
#include <sstream>
#include "butterfly.h"
#include "sighting.h"
#include "user.h"
class Reports{
public:
	static std::string hotspot(std::map<unsigned int, Sighting>& sightings);
	static std::string migration(std::map<std::string, std::vector<Sighting*> >& dateSightings, std::map<std::string, Butterfly>& tags);
	static std::string userRankings(std::map<std::string, std::vector<Sighting*> >& userSightings, std::map<std::string, User>& users, std::string currentUser);
	static std::string speciesLocation(std::map<unsigned int, Sighting>& sightings);
	static std::string sightingHistory(std::map<std::string, std::vector<Sighting*> >& dateSightings);
	static std::string cityDateLookup(std::map<std::string, std::vector<Sighting*> >& dateSightings, std::map<std::string, std::vector<Sighting*> >& locationSightings);
	static std::string tagDateLookup(std::map<std::string, Butterfly>& tags);
private:
	static double latLongDistance(double lat1, double long1, double lat2, double long2, bool km);
	static void incrementFrequency(std::map<std::string, unsigned int>& frequency, std::string location);
};
#endif