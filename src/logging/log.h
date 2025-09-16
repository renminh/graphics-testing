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

#define _LINIT	"["	_ANSI_COLOR_CYAN	"INIT"	_ANSI_COLOR_RESET	"]\t\t"
#define _LOK	"["	_ANSI_COLOR_GREEN	"OK"	_ANSI_COLOR_RESET	"]\t\t"
#define _LWARN	"["	_ANSI_COLOR_YELLOW	"WARN"	_ANSI_COLOR_RESET	"]\t\t"
#define _LERR	"["	_ANSI_COLOR_RED		"ERR"	_ANSI_COLOR_RESET	"]\t\t"
#define _LEND	"["	_ANSI_COLOR_MAGENTA	"END"	_ANSI_COLOR_RESET	"]\t\t"
#define _LINFO	"["	_ANSI_COLOR_BLUE	"INFO"	_ANSI_COLOR_RESET	"]\t\t"
#define _LDBG	"["	_ANSI_COLOR_CYAN	"DBG"	_ANSI_COLOR_RESET	"]\t\t"

#define LOG_ERR(fmt, ...)	({fprintf(stderr, _LERR fmt " (%s:%d)\n", ##__VA_ARGS__, __FILE__, __LINE__);})
#define LOG_OK(fmt, ...)	({fprintf(stdout, _LOK fmt " (%s:%d)\n", ##__VA_ARGS__, __FILE__, __LINE__);})
#define LOG_WARN(fmt, ...)	({fprintf(stderr, _LWARN fmt " (%s:%d)\n", ##__VA_ARGS__, __FILE__, __LINE__);})
#define LOG_END(fmt, ...)	({fprintf(stdout, _LEND fmt " (%s:%d)\n", ##__VA_ARGS__, __FILE__, __LINE__);})
#define LOG_DBG(fmt, ...)	({fprintf(stdout, _LDBG fmt " (%s:%d)\n", ##__VA_ARGS__, __FILE__, __LINE__);})
#define LOG_INIT(fmt, ...)	({fprintf(stdout, _LINIT fmt " (%s:%d)\n", ##__VA_ARGS__, __FILE__, __LINE__);})
#define LOG_INFO(fmt, ...)	({fprintf(stdout, _LINFO fmt " (%s:%d)\n", ##__VA_ARGS__, __FILE__, __LINE__);})

#endif
