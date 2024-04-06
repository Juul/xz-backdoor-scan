#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "signature.h"

#include "scan-file.h"

int main( int argc , char * argv [] )
{
	bool all_good = true;

	for( int i = 1 ; i < argc ; i ++ )
	{
		char * filename = argv[ i ];

		int status = scan_file( filename , signature , length );

		if( status < 0 )
		{
			all_good = false;

			continue;
		}

//		printf( "%s: OK\n" , filename );
	}

	if( ! all_good )
	{
		exit( EXIT_FAILURE );
	}

	exit( EXIT_SUCCESS );
}
