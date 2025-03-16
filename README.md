# Atomichan Cpp study application

Questions:

1.
I want to divide source file into three (four?) files.
After having divided the file, I came across the following errors from Liner:
-----     -----
vscode ➜ /workspaces/CppOfficeHour (main) $ cmake --build build
Consolidate compiler generated dependencies of target atomichanLib
[ 25%] Built target atomichanLib
[ 37%] Building CXX object app/CMakeFiles/atomichanApp.dir/myApp.cpp.o
[ 50%] Linking CXX executable ../bin/atomichanApp
/usr/bin/ld: CMakeFiles/atomichanApp.dir/myApp.cpp.o: warning: relocation against `_ZTV1B' in read-only section `.text.startup'
/usr/bin/ld: CMakeFiles/atomichanApp.dir/myApp.cpp.o: in function `main':
myApp.cpp:(.text.startup+0x3c): undefined reference to `vtable for B'
/usr/bin/ld: warning: creating DT_TEXTREL in a PIE
collect2: error: ld returned 1 exit status
gmake[2]: *** [app/CMakeFiles/atomichanApp.dir/build.make:99: bin/atomichanApp] Error 1
gmake[1]: *** [CMakeFiles/Makefile2:182: app/CMakeFiles/atomichanApp.dir/all] Error 2
gmake: *** [Makefile:91: all] Error 2
-----     -----

When I keep call_f function inside my header file (B.h), I can compile and runt the programm.
Where is wrong?

2. (if possible)
Then, I want to move a function defined in app/myApp.cpp (line 28-31) to myutils, into a header and source file, with defining a namespace, and if possible, make some generalization with typename directive, so that I can use this function for other type of classes inherited from class A (which is an abstract class).



