# C-operating-system-emulater
A C++ program that emulate the operating system’s responsibility of allocating
memory to certain programs. A very simple page-based view of memory
management. On startup, program will have some 32 pages of contiguous, unused
memory. Each page will be 4 KB long.
It allow the users to “run” programs that require chunks
of this memory for some period of time. It also allow the users to “kill” programs
(i.e., “Ctrl-c” or “kill -9” in most OSs) that are in progress. The pages used by programs
that are killed can then be re-used for future programs.
