#include "echoDisable.h"
namespace chrisLibs{
	void echo(bool on = true){
		#ifdef _WIN32
		DWORD mode;
		HANDLE hConIn = GetStdHandle( STD_INPUT_HANDLE );
		GetConsoleMode( hConIn, &mode);
		mode = on
			? (mode | ENABLE_ECHO_INPUT)
			: (mode & ~(ENABLE_ECHO_INPUT));
		SetConsoleMode( hConIn, mode );
		#endif
		
		#ifdef __linux__
		struct termios settings;
		tcgetattr( STDIN_FILENO, &settings );
		settings.c_lflag = on
			? (settings.c_lflag | ECHO)
			: (settings.c_lflag & ~(ECHO));
		tcsetattr( STDIN_FILENO, TCSANOW, &settings );
		#endif
	}
}