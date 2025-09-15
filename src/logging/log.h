#ifndef STYLE_H
#define STYLE_H

#include <stdio.h>

#define _ANSI_COLOR_RED     "\x1b[31m"
#define _ANSI_COLOR_GREEN   "\x1b[32m"
#define _ANSI_COLOR_YELLOW  "\x1b[33m"
#define _ANSI_COLOR_BLUE    "\x1b[34m"
#define _ANSI_COLOR_MAGENTA "\x1b[35m"
#define _ANSI_COLOR_CYAN    "\x1b[36m"
#define _ANSI_COLOR_RESET   "\x1b[0m"

#define _LINIT	"["_ANSI_COLOR_CYAN"INIT"_ANSI_COLOR_RESET"]\t\t"
#define _LOK		"["_ANSI_COLOR_GREEN"OK"_ANSI_COLOR_RESET"]\t\t"
#define _LWARN	"["_ANSI_COLOR_YELLOW"WARN"_ANSI_COLOR_RESET"]\t\t"
#define _LERR	"["_ANSI_COLOR_RED"ERR"_ANSI_COLOR_RESET"]\t\t"
#define _LEND	"["_ANSI_COLOR_MAGENTA"END"_ANSI_COLOR_RESET"]\t\t"
#define _LINFO	"["_ANSI_COLOR_BLUE"INFO"_ANSI_COLOR_RESET"]\t\t"
#define _LDBG	"["_ANSI_COLOR_CYAN"DBG"_ANSI_COLOR_RESET"]\t\t"

#define LOG_ERR(_s) ({ \
	fprintf(stdout, _LERR "%s | %s - %s\n", _s, __FILE__, __LINE__);})

#define LOG_OK(_s) ({ \
	fprintf(stdout, _LOK "%s | %s - %s\n", _s, __FILE__, __LINE__);})

#define LOG_WARN(_s) ({ \
	fprintf(stdout, _LWARN "%s | %s - %s\n", _s, __FILE__, __LINE__);})

#define LOG_END(_s) ({ \
	fprintf(stdout, _LEND "%s | %s - %s\n", _s, __FILE__, __LINE__);})

#define LOG_DBG(_s) ({ \
	fprintf(stdout, _LDBG "%s | %s - %s\n", _s, __FILE__, __LINE__);})

#define LOG_INIT(_s) ({ \
	fprintf(stdout, _LINIT "%s | %s - %s\n", _s, __FILE__, __LINE__);})

#define LOG_INFO(_s) ({ \
	fprintf(stdout, _LINFO "%s | %s - %s\n", _s, __FILE__, __LINE__);})

#endif
