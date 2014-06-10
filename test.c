#include <stdio.h>

int main(int argc, char **argv)
{
	/* note that fopen is not preloaded although is calls open internally  */
	fopen("Makefile", "r");
	open("Makefile", 0);
	return 0;
}
