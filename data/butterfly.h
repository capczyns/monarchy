#ifndef BUTTERFLY_H
#define BUTTERFLY_H
#include <string>
#include <iostream>
class ButterflyData{
public:
	std::string tagger;
	std::string tagNum;
	std::string species;
	std::string city;
	std::string state;
	std::string country;
	int day;
	int month;
	int year;
	int hour;
	int minute;
	int second;
	double latitude;
	double longitude;

	ButterflyData();
	ButterflyData(std::string tagger, std::string tagNum, std::string species, std::string city, std::string state, std::string country,
			  int day, int month, int year, int hour, int minute, int second, double latitude, double longitude);
};
class Butterfly{
private:
	std::string tagger;
	std::string tagNum;
	std::string species;
	std::string city;
	std::string state;
	std::string country;
	int day;
	int month;
	int year;
	int hour;
	int minute;
	int second;
	double latitude;
	double longitude;
public:
	Butterfly();
	Butterfly(std::string tagger, std::string tagNum, std::string species, std::string city, std::string state, std::string country,
			  int day, int month, int year, int hour, int minute, int second, double latitude, double longitude);
	Butterfly(ButterflyData& data);
	void update(ButterflyData& data);
	ButterflyData getData();
	void saveStr(std::ostream& out);
	std::string getSpecies();
	friend std::ostream& operator<<(std::ostream& out, Butterfly& butterfly);
};
#endif