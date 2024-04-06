#ifndef SCAN_FILE_H
	#define SCAN_FILE_H

	#include <stdint.h>

	int scan_file( char * filename , uint8_t * signature , size_t length );

	#define SCAN_FILE_ERROR_STAT_FAILED -1
	#define SCAN_FILE_ERROR_OPEN_FAILED -2
	#define SCAN_FILE_ERROR_MMAP_FAILED -3

	#define SCAN_FILE_SIGNATURE_FOUND -666

	#define SCAN_FILE_CLEAN 0

	#define SCAN_FILE_OK_TOO_SMALL 1
#endif /* ! SCAN_FILE_H */
