#include <stdio.h>
#include <stdbool.h>

#ifndef __LOG_MACROS_H__
#define __LOG_MACROS_H__

#define log_int(n) 			printf("%s == %d\n", (#n), (n))
#define log_char(c) 		printf("%s == '%c'\n", (#c), (c))
#define log_str(s) 			printf("%s == \"%s\"\n", (#s), (s))
#define log_addr(addr) 		printf("%s == %p\n", (#addr), ((void*)addr))
#define log_float(n)		printf("%s == %.16f\n", (#n), (n))
#define log_bool(condition) printf("%s == %s\n", (#condition), (condition ? "true" : "false"))

#endif

