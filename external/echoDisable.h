#ifndef C_ECHO
#define C_ECHO

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#endif
namespace chrisLibs{
	void echo(bool on);
}
#endif