/*
  Copyright (c) 2022 tyabus

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "get_md5.h"

int main(int argc, char **argv)
{
	char filename[MAX_NAME_LEN];
	static int i;

	if( argc < 2 )
	{
		fprintf( stdout, "md5calc version %1.2f\n", MD5CALC_VER );
		fprintf( stdout, "Usage: %s <file/s>\n", argv[0] );
		fprintf( stdout, "Calculate and Print MD5 checksums of specified files.\n" );
		exit( EXIT_FAILURE );
	}

	for( i = 1; i < argc; i++ )
	{
		if( strlen( argv[i] ) > MAX_NAME_LEN )
		{
			printf( "%s: file name is too big\n", argv[i] );
		}
		else
		{
			strcpy( filename, argv[i] );
			printf( "%s: %s\n", filename, get_md5( filename ) );
		}
	}

	exit( EXIT_SUCCESS );
}
