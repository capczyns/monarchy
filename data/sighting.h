#ifndef SIGHTING_H
#define SIGHTING_H
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
struct Weather{
	int temp;
	int windSpeed;
	int windDir;
	int precipitation;
	Weather();
	Weather(int temp, int windSpeed, int windDir, int precipitation);
	friend std::ostream& operator<<(std::ostream& out, const Weather& weather);
};
struct SightingData{
public:
	unsigned int id;
	std::string reporter;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	double latitude;
	double longitude;
	std::string city;
	std::string state;
	std::string country;
	std::string species;
	std::string tagNum;
	Weather weather;
	SightingData(std::string reporter, int year, int month, int day,
			 int hour, int minute, int second, double latitude, double longitude,
			 std::string city, std::string state, std::string country, std::string species, std::string tagNum, unsigned int id);
	SightingData() : SightingData("", 0, 0, 0, 0, 0, 0, 0.0, 0.0, "", "", "", "", "", 0){}
	std::string dateStr();
	std::string cityStr();
	std::string timeStr();
	void exportStr(std::ostream& out);
	friend std::ostream& operator<<(std::ostream& out, const SightingData& sighting);
};
class Sighting{
private:
	unsigned int id;
	std::string reporter;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	double latitude;
	double longitude;
	std::string city;
	std::string state;
	std::string country;
	std::string species;
	std::string tagNum;
	Weather weather;

	unsigned static int nextId;
public:
	Sighting();
	Sighting(SightingData& data);
	Sighting(std::string reporter, int year, int month, int day,
			 int hour, int minute, int second, double latitude, double longitude,
			 std::string city, std::string state, std::string country, std::string species, std::string tagNum);
	void update(std::string reporter, int year, int month, int day,
			 int hour, int minute, int second, double latitude, double longitude,
			 std::string city, std::string state, std::string country, std::string species, std::string tagNum);
	void update(SightingData& data);
	SightingData getData();
	bool sameSighting(Sighting &other);
	unsigned int getId();
	void saveStr(std::ostream& out);
	std::string getReporter();
	bool isTagged();
	bool sameSpecies(const std::string& other);
	friend std::ostream& operator<<(std::ostream& out, const Sighting& sighting);
};
#endif