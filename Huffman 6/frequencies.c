#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "frequencies.h"

bool calc_frequencies(Frequencies freqs, const char* path, const char** a_error) {
	FILE* fp = fopen(path, "r");
	if(fp == NULL) {
		*a_error = strerror(errno);
		return false;
	}
	for(unsigned char ch = fgetc(fp); !feof(fp); ch = fgetc(fp)) {
		freqs[ch]++;
	}
	fclose(fp);

	return true;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */

