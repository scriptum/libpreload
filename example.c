/*******************************************************************************

Copyright (c) 2014 Pavel Roschin <rpg89@post.ru>

Compile:
gcc -shared -fPIC -ldl example.c -o example.so

Use:
LD_PRELOAD=./example.so cat example.c
Hello from open!
...
*******************************************************************************/

#include "libpreload.h"
#include <stdio.h>

HIDE_START(int, open, (const char *pathname, int flags))
{
	puts("Hello from open!");
	return open_orig(pathname, flags);
}
HIDE_END
