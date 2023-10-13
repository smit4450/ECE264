#include <assert.h>
#include "bit_writer.h"
#include "log_macros.h"

BitWriter open_bit_writer(const char* path) {
	return (BitWriter) { .file = fopen(path, "w"), .current_byte = 0, .num_bits_left = 8 };
}

void write_bits(BitWriter* a_writer, uint8_t bits, uint8_t num_bits_to_write) {
	assert(num_bits_to_write >= 0 && num_bits_to_write <= 8);
	assert(a_writer -> num_bits_left >= 1 && a_writer -> num_bits_left <= 8);

	if(num_bits_to_write > a_writer -> num_bits_left) {
		uint8_t num_bits_second = num_bits_to_write - a_writer -> num_bits_left;
		write_bits(a_writer, bits >> (num_bits_to_write - (a_writer -> num_bits_left)), a_writer -> num_bits_left);
		num_bits_to_write = num_bits_second;
	}

	bits = (bits & (0xff >> (8 - num_bits_to_write)));
	a_writer -> current_byte = (bits << ((a_writer -> num_bits_left) - num_bits_to_write)) | a_writer -> current_byte;
	a_writer -> num_bits_left = a_writer -> num_bits_left - num_bits_to_write;

	if(a_writer -> num_bits_left == 0) {
		fputc(a_writer -> current_byte, a_writer -> file);
		a_writer -> current_byte = 0;
		a_writer -> num_bits_left = 8;
	}
	assert(a_writer -> num_bits_left >= 1 && a_writer -> num_bits_left <= 8);
}

void flush_bit_writer(BitWriter* a_writer) {
	if(a_writer -> num_bits_left != 8) {
		write_bits(a_writer, 0, a_writer -> num_bits_left);
	}
}

void close_bit_writer(BitWriter* a_writer) {
	flush_bit_writer(a_writer);
	fclose(a_writer -> file);
	a_writer -> file = NULL;
}

#define __BIT_WRITER_C_V1__
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab colorcolumn=96: */

