#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "log_macros.h"
#define MINIUNIT_BONUS_SELECTIVE_TESTING
#define MINIUNIT_BONUS_INLINE_FUNCTIONS

inline static int _mu_check(int condition, int __mu_first_failure_line_number_or_0, int line); 
inline static void _mu_run(char *function, int function_return, int argc, char *args[]);

#ifndef __MINIUNIT_H__
#define __MINIUNIT_H__

#define MU_SUCCESS 0

#define mu_start() 						int __mu_first_failure_line_number_or_0 = MU_SUCCESS

#define mu_end() 						return(__mu_first_failure_line_number_or_0)

#define mu_check(condition)				__mu_first_failure_line_number_or_0 = _mu_check(condition, __mu_first_failure_line_number_or_0, __LINE__)

#define mu_check_strings_equal(s1, s2)	mu_check(strcmp(s1, s2) == 0) 

#define mu_run(function)				_mu_run(#function, function(), argc, argv)
	
#endif

inline static int _mu_check(int condition, int __mu_first_failure_line_number_or_0, int line) {
	if ((condition ? false : true) && (__mu_first_failure_line_number_or_0 == MU_SUCCESS)) {
		__mu_first_failure_line_number_or_0 = line;
	}
	return __mu_first_failure_line_number_or_0;
}

inline static void _mu_run(char *function, int function_return, int argc, char *args[]) {
	if ((argc < 2) || (strcmp(args[1], function) == 0)) { 
		if (function_return == 0) {															
			printf("\x1b[32m");																
			printf("Test passed: %s\n", function);											
			printf("\x1b[0m");																
		}																					
		else if (function_return >= 1) {													
			printf("\x1b[31m");																
			printf("Test failed: %s at line %d\n", function, function_return);				
			printf("\x1b[0m");																
		}
	}
	return;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */

