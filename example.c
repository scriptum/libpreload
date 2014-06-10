/*******************************************************************************

Copyright (c) 2014 Pavel Roschin <rpg89@post.ru>

Compile:
gcc -shared -fPIC -ldl example.c -o example.so

Try:
make check
Hello from open!

*******************************************************************************/

#include "libpreload.h"
#include <stdio.h>

HIDE_START(int, open, (const char *pathname, int flags))
{
	if(first_run)
		puts("Hello from open!");
	else
		puts("open is called");
	return open_orig(pathname, flags);
}
HIDE_END
