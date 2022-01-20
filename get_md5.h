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

#ifndef __GET_MD5_H_INCLUDED__
#define __GET_MD5_H_INCLUDED__

#define MAX_NAME_LEN 256 /* same as ext4 + 1 */
#define MD5CALC_VER 1.00

#if defined __BYTE_ORDER__ && __BYTE_ORDER__ == __BIG__ENDIAN
	#define ARCH_IS_BIG_ENDIAN 1
#endif

char *get_md5( const char *file ); /* calculate md5 by using md5 library */
void fatal( const char *msg, ... ); /* throw error and shutdown */
void *_malloc( ssize_t size ); /* currently only used in get_md5.c */
#endif
