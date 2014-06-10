/*******************************************************************************

Copyright (c) 2014 Pavel Roschin <rpg89@post.ru>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions: The above
copyright notice and this permission notice shall be included in all copies
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.

*******************************************************************************/

#define _GNU_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <dlfcn.h>

#define HIDE_START(returnspec, funcname, args)                                 \
returnspec (*funcname##_orig) args;                                            \
static int funcname##_load() {                                                 \
    funcname##_orig = dlsym(RTLD_NEXT, #funcname);                             \
    if(dlerror() != NULL)                                                      \
        return -1;                                                             \
    return 0;                                                                  \
}                                                                              \
returnspec funcname args {                                                     \
    static int first_run = 1;                                                  \
    if(!funcname##_orig) {                                                     \
        if(funcname##_load() != 0)                                             \
            exit(-1);                                                          \
    }                                                                          \
    else                                                                       \
        first_run = 0;                                                         \

#define HIDE_END }
