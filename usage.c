#include "usage.h"

void usage( FILE * out , const char * program_name )
{
	fprintf( out ,
		"Usage:\n"
		"\t%s [options] <filenames> [...]\n"
		"\n"
		"Where [options] are:\n"
		"\n"
		"\t-h / --help\n"
		"\t\tThis text\n"
		"\n"
		"\t-f / --file <filename>\n"
		"\t\tSearch for content of \"filename\" instead of the xz-backdoor signature\n"
		"\t-n / --needle <needle>\n"
		"\t\tSearch for \"needle\" instead of the xz-backdoor signature\n"
		"\t\tThis is mostly useful for searching for text strings.\n"
		"\t\tFor binary data, see -f / --file\n"
		"" ,
		program_name
	);
}
