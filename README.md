ticktock
========

A handy wrapper around the high-precision [time stamp counter](https://en.wikipedia.org/wiki/Time_Stamp_Counter).


Usage
-----

```c
// include the header
#include "ticktock.h"
```

```c
// start a timer
tick();
// some code to be timed...
unsigned long long int delta = tock();
```


Notes
-----

*   Compile using gcc with the `-std=c99` flag.
