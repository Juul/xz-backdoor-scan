#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "scan-file.h"

int scan_file( char * filename , uint8_t * signature , size_t length )
{
	struct stat statbuf;

	int errors = stat( filename , & statbuf );
	if( errors )
	{
		perror( filename );

		return( SCAN_FILE_ERROR_STAT_FAILED );
	}

	if( ( size_t ) ( statbuf . st_size ) < length )
	{
		return( SCAN_FILE_OK_TOO_SMALL );
	}

	int fd = open( filename , O_RDONLY );
	if( fd < 0 )
	{
		perror( filename );

		return( SCAN_FILE_ERROR_OPEN_FAILED );
	}

	uint8_t * file_content = mmap( NULL , statbuf . st_size , PROT_READ , MAP_PRIVATE , fd , 0 );
	if( file_content == MAP_FAILED )
	{
		perror( filename );

		close( fd );

		return( SCAN_FILE_ERROR_MMAP_FAILED );
	}

  // Something closely resembling Boyer-Moore
  // https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm
  
	size_t offset = 0;

	while( offset <= statbuf . st_size - length )
	{
		bool match = true;

		size_t scan_backwards_offset = length;
		size_t jump_forward = 1;

		while( scan_backwards_offset > 0 )
		{
			uint8_t chr = file_content[ ( offset + scan_backwards_offset ) -1 ];

			if( chr != signature[ scan_backwards_offset - 1 ] )
			{
				for( jump_forward = 1 ; jump_forward < scan_backwards_offset ; jump_forward ++ )
				{
					if( signature[ ( scan_backwards_offset - 1 ) - jump_forward ] == chr )
					{
						break;
					}
				}
			
				match = false;
				
				break;
			}
			
			scan_backwards_offset --;
		}

		if( match )
		{
			fprintf( stderr , "%s: CONTAINS THE SIGNATURE\n" , filename );

			munmap( file_content , statbuf . st_size );
			close( fd );

			return( SCAN_FILE_SIGNATURE_FOUND );
		}

		offset += jump_forward;
	}

	munmap( file_content , statbuf . st_size );
	close( fd );

	return( SCAN_FILE_CLEAN );
}
