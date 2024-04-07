#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "scan-file.h"
#include "usage.h"

#include "xz-backdoor-signature.h"

int main( const int argc , char * const argv [] )
{
	int needle_fd = -1;
	uint8_t * needle = xz_backdoor_signature;
	size_t length = xz_backdoor_signature_length;
	
	int option;
	
	do
	{
		char * optstring =
			"f:"	/* --file <filename> */
			"h"	/* --help */
			"n:"	/* --needle <needle> */
			"";
		
		struct option longopts [] =
		{
			{ "file" , required_argument , NULL , 'f' },
			{ "help" , no_argument , NULL , 'h' },
			{ "needle" , required_argument , NULL , 'n' },
			{ NULL , no_argument , NULL , 0 },
		};
		
		int longindex;
		
		option = getopt_long( argc , argv , optstring , longopts , & longindex );
		
		switch( option )
		{
			case -1:
			{
				/* All options done */
			}
			break;
			
			case 'f':
			{
				if( needle_fd != -1 )
				{
					munmap( needle , length );
					close( needle_fd );
					needle_fd = -1;
				}
				
				struct stat needle_statbuf;
				
				int errors = stat( optarg , & needle_statbuf );
				if( errors )
				{
					perror( optarg );
					
					exit( EXIT_FAILURE );
				}
				
				length = needle_statbuf . st_size;
				
				needle_fd = open( optarg , O_RDONLY );
				if( needle_fd < 0 )
				{
					perror( optarg );
					
					exit( EXIT_FAILURE );
				}
				
				needle = mmap( NULL , length , PROT_READ , MAP_PRIVATE , needle_fd , 0 );
				if( needle == MAP_FAILED )
				{
					perror( optarg );

					close( needle_fd );
					
					exit( EXIT_FAILURE );
				}
			}
			break;
			
			case 'h':
			{
				usage( stdout , argv[ 0 ] );
				
				if( needle_fd != -1 )
				{
					munmap( needle , length );
					close( needle_fd );
				}
				
				exit( EXIT_SUCCESS );
			}
			
			case 'n':
			{
				if( needle_fd != -1 )
				{
					munmap( needle , length );
					close( needle_fd );
					needle_fd = -1;
				}

				needle = ( uint8_t * ) optarg;

				length = strlen( optarg );
			}
			break;

			default:
			{
				fprintf( stderr , "Missing code for -%c\n" , option );
				
				exit( EXIT_FAILURE );
			}
			break;
		}
	}
	while( option != -1 );
	
	bool all_good = true;

	for( int i = optind ; i < argc ; i ++ )
	{
		char * filename = argv[ i ];

		int status = scan_file( filename , needle , length );

		if( status < 0 )
		{
			all_good = false;

			continue;
		}

//		printf( "%s: OK\n" , filename );
	}

	if( needle_fd != -1 )
	{
		munmap( needle , length );
		close( needle_fd );
	}
	
	if( ! all_good )
	{
		exit( EXIT_FAILURE );
	}

	exit( EXIT_SUCCESS );
}
