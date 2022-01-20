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
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <unistd.h> /* F_OK */

#include "md5.h"

void fatal( const char *msg, ... )
{
	va_list argsptr;
	char text[4096];

	va_start( argsptr, msg );
	sprintf( text, msg, argsptr );
	va_end( argsptr );

	fprintf( stdout, "Fatal: %s\n", text );

	exit( EXIT_FAILURE );
}

void *_malloc( ssize_t size )
{
	void *mptr;

	if( sizeof( size ) >= SSIZE_MAX )
	{
		fatal( "_malloc: Tried to allocate absolute (%li bytes) amount of memory", size );
		return NULL;
	}

	mptr = malloc( size );

	if( mptr == NULL )
		fatal( "_malloc: Out of memory (tried to allocate %li bytes)", size );
	else
		memset( mptr, 0, size );

	return mptr;
}

static bool fileExists( const char *file )
{
	static bool exist = false;

	if( !access( file, F_OK ) )
		exist = true;

	return exist;
}

static char *readFile( FILE *file )
{
	char *out;
	unsigned long fileLength;

	fseek( file, 0, SEEK_END );
	fileLength = ftell( file );
	fseek( file, 0, SEEK_SET );

	out = (char *)_malloc( fileLength + 1 ); /* + null terminator */

	fread( out, fileLength, 1, file );

	return out;
}

char *get_md5( const char *file )
{
	FILE *fp;
	char *data;
	static char md5[33];
	char *pmd5 = md5;
	static int i;
	md5_state_t state;
	md5_byte_t digest[16];

	if( !fileExists( file ) )
	{
		fatal( "%s: Unable to find file", file );
		return NULL;
	}

	fp = fopen( file, "rb" );
	if( fp == NULL )
	{
		fatal( "%s: Couldn't open file", file );
		return NULL;
	}

	data = readFile( fp );
	if( data == NULL )
	{
		fatal( "%s: readFile error", file );
		return NULL;
	}

	md5_init( &state );
	md5_append( &state, (const md5_byte_t *)data, strlen( data ) );
	md5_finish( &state, digest );

	for(i = 0; i < 16; i++)
		sprintf( &md5[i*2], "%02x", digest[i] );

	fclose( fp );
	fp = NULL;

	free( data );

	return pmd5;
}
