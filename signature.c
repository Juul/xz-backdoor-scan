#include "signature.h"

/*
 * TODO: Read "signature" from a file instead of having it hardcoded
 */

uint8_t signature [] = {
	0xF3 , 0x0F , 0x1E , 0xFA , 0x55 , 0x48 , 0x89 , 0xF5 ,
	0x4C , 0x89 , 0xCE , 0x53 , 0x89 , 0xFB , 0x81 , 0xE7 ,
	0x00 , 0x00 , 0x00 , 0x80 , 0x48 , 0x83 , 0xEC , 0x28 ,
	0x48 , 0x89 , 0x54 , 0x24 , 0x18 , 0x48 , 0x89 , 0x4C ,
	0x24 , 0x10
};

size_t length = sizeof( signature );