#ifndef SCAN_FILE_H
	#define SCAN_FILE_H

	#include <stddef.h>
	#include <stdint.h>

	int scan_file( const char * filename , const uint8_t * needle , const size_t length );

	#define SCAN_FILE_ERROR_STAT_FAILED -1
	#define SCAN_FILE_ERROR_OPEN_FAILED -2
	#define SCAN_FILE_ERROR_MMAP_FAILED -3

	#define SCAN_FILE_NEEDLE_FOUND -666

	#define SCAN_FILE_CLEAN 0

	#define SCAN_FILE_OK_NOT_A_REGULAR_FILE 1
	#define SCAN_FILE_OK_TOO_SMALL 2
#endif /* ! SCAN_FILE_H */
