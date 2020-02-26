===================================
TBB_malloc_replacement_log Function
===================================


Summary
-------

Function that provides information about the status
of dynamic memory allocation replacement (Windows* OS only).

Syntax
------

.. code:: cpp

   extern "C" int TBB_malloc_replacement_log(char *** log_ptr);


Header
------

.. code:: cpp

   #include "tbb/tbbmalloc_proxy.h"


Description
-----------

Dynamic replacement of memory allocation functions on Windows* OS
uses in-memory binary instrumentation techniques. To ensure that such instrumentation is safe,
TBB first searches for a subset of replaced functions in the Visual C++* runtime DLLs,
and checks if each one has a known bytecode pattern. If any required function is not found
or its bytecode pattern is unknown, the replacement is skipped, and the program continues
to use the standard memory allocation functions.

The ``TBB_malloc_replacement_log`` function allows the program
to check if the dynamic memory replacement has happened, and to get a log of the performed checks.

**Returns:**
0 if all necessary functions were successfully found and the replacement took place, otherwise -1.

The ``log_ptr`` parameter must be an address of
a ``char**`` variable, or be NULL. If it is not NULL, the function
writes there the address of an array of NULL-terminated strings containing detailed
information about the searched functions in the following format:

.. code:: cpp

   search_status: function_name (dll_name), byte pattern: <bytecodes>

For more information about the replacement of dynamic memory allocation functions,
see "Windows* OS C/C++ Dynamic Memory Interface Replacement" section in the TBB Developer Guide.

Usage example
-------------

.. code:: cpp

   #include "tbb/tbbmalloc_proxy.h"
   #include <stdio.h>
   
   int main(){
       char **func_replacement_log;
       int func_replacement_status = TBB_malloc_replacement_log(&func_replacement_log);
   
       if (func_replacement_status != 0) {
           printf("tbbmalloc_proxy cannot replace memory allocation routines\n");
           for (char** log_string = func_replacement_log; *log_string != 0; log_string++) {
               printf("%s\n",*log_string);
           }
       }
   
       return 0;
   }

Example output:

.. code:: cpp

   tbbmalloc_proxy cannot replace memory allocation routines
   Success: free (ucrtbase.dll), byte pattern: <C7442410000000008B4424>
   Fail: _msize (ucrtbase.dll), byte pattern: <E90B000000CCCCCCCCCCCC>

