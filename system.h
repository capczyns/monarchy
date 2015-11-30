#ifndef SYSTEM_H
#define SYSTEM_H
class System{
private:
	void login();
	void quit();
	bool importExport();
	void createSighting();
	void viewUsers();
	bool deleteAccount();
	bool manageSightings();
	void reports();
	void mainMenu();
	void clear();
public:
	void start();
};
#endif