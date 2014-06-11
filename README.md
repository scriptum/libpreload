libpreload
==========

Simple header that helps you to do LD_PRELOAD tricks. It provides two macros: 
`HIDE_START` and `HIDE_END`. Use `HIDE_START` to hide library function and put
`HIDE_END` at the end of your own implementation. Just below macro `HIDE_START` 
use `<FUNC>_orig` function to call original library implementation. 
Inside your implementation use `first_run` variable to detect first call.

`USE_START(return_value, function_name, arguments)`

Example (trace open system call and call original function):

```cpp
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
```

To build that just run:

`gcc -shared -fPIC -O2 example.c -ldl -o libexample.so`

And use:

`LD_PRELOAD=./libexample.so cat example.c`
