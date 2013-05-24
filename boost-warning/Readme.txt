

Ce tests a pour objectif de résoudre un warning dans boost/multi-array

Message envoyé à boost 
============================

Hello boost comunity,

I found a warning using boost/multi-array  (boost 1.53) on mingw.

The warning message :

boost/multi_array/base.hpp:503:13: attention : unused variable 'bound_adjustment'

When compiling a simple example including muti-array with the command line :

c:\MinGW\bin\g++.exe  -Wall -Wextra -O2 -DNDEBUG -g -Ic:/natifvle/install/boost/include/boost-1_53 -o MyExample.o -c MyExample.cpp


The reason is that a locale variable bound_adjustement, before line 503 of multi_array/base.hpp, is defined and computed only if BOOST_DISABLE_ASSERT is not set.
The line after, a BOOST_ASSERT is called using bound_adjustement. Since BOOST_DISABLE_ASSERT is not set,  BOOST_ASSERT is defined as the mingw macro "assert" in boost/assert.hpp. Finally, mingw assert macro  (see Mingw/include/assert.h) is defined as ((void) 0) if NDEBUG is defined (this is the case in my example).
It took me a long time to see the problem.

So my questions are :
- Do I miss use the combination of NDEBUG and BOOST_DISABLE_ASSERTS ? Eg. if NDEBUG and BOOST_DISABLE_ASSERTS  are set (or unset) together, then I have no warning. Should they be set to the same value ?
- Or should boost/assert.hpp take into account NDEBUG for defining the macro BOOST_ASSERT (only for mingw ?)

Best regards
Ronan Trépos 

============================

Pour identifier ce soucis on peut utiliser les options de gcc:

- compilation classique :
c:\MinGW\bin\g++.exe -Wall -Wextra -O2 -g -DNDEBUG -Ic:/natifvle/install/boost/include/boost-1_53 -o myobj.o -c c:\tests\boost-warning\Matrix.cpp

- seulement preprocessing (-E) mais que pour les directives (-fdirectives-only)
c:\MinGW\bin\g++.exe -E -fdirectives-only -Wall -Wextra -O2 -g -DNDEBUG -Ic:/natifvle/install/boost/include/boost-1_53 -o myobj.o -c c:\tests\boost-warning\Matrix.cpp