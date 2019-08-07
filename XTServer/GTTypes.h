#pragma once




namespace GT {

	typedef struct {
		unsigned short Keep_Alive_Header;
		unsigned short Keep_Alive_ID;
		unsigned long Keep_Alive_Device_ID;
	} SyncMsg;

	typedef struct  {
		char token;
		char id[10];
		char cmd[100];
	} CmdMsg;
	
	typedef struct {
		char token;
		char id[10];
		char msg[255];
	} RetMsg;
	typedef struct {
		char token;
		char msg[255];
	} GenMsg;

}



#define ANSI_COLOR_BOLD  "\x1b[1m"
#define ANSI_COLOR_DIM "\x1b[2m"
#define ANSI_COLOR_ITALIC  "\x1b[3m"
#define ANSI_COLOR_UNDERSCORE "\x1b[4m"
#define ANSI_COLOR_BLINK "\x1b[5m"
#define ANSI_COLOR_REVERSE  "\x1b[7m"
#define ANSI_COLOR_HIDDEN   "\x1b[8m"


#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GRAY    "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define ANSI_COLOR_BLACK_   "\x1b[40m"
#define ANSI_COLOR_RED_     "\x1b[41m"
#define ANSI_COLOR_GREEN_   "\x1b[42m"
#define ANSI_COLOR_YELLOW_  "\x1b[43m"
#define ANSI_COLOR_BLUE_    "\x1b[44m"
#define ANSI_COLOR_MAGENTA_ "\x1b[45m"
#define ANSI_COLOR_CYAN_    "\x1b[46m"
#define ANSI_COLOR_WHITE_   "\x1b[47m"

