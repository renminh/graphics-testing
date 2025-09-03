#ifndef STYLE_H
#define STYLE_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define INIT_STR "["ANSI_COLOR_CYAN"INIT"ANSI_COLOR_RESET"]\t\t"
#define ERROR_STR "["ANSI_COLOR_RED"ERROR"ANSI_COLOR_RESET"]\t\t"
#define SUCCESS_STR "["ANSI_COLOR_GREEN"SUCCESS"ANSI_COLOR_RESET"]\t"
#define END_STR "["ANSI_COLOR_YELLOW"END"ANSI_COLOR_RESET"]\t\t"
#define INFO_STR "[INFO]\t\t"

#endif
