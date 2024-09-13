README FILE:

How to Run:
Navigate to directory of file
type "cc simple_shell.c"
then type "./a.out"

How to Use:
Type out a UNIX command such as who, ls, and any necessary arguments
type "exit" when you're ready to quit.


Design:
-------------------------------------------------------------------------------------------------------------------------------------------
The design for the program is quite simple. It is written in C and relies on system calls from the unistd.h API.

First, the program initializes a handful of character pointer arrays, counters, and other necessary variables.

Then, using the stdlib function getenv("PATH"), we search up our PATH environment variable (which is nested in all of ADA's other directories so its quite long).
We break this up using tokenization (strtok()) by the ":" delimeter. From there, we essentially get a bunch of bin directories from which to try and run our argument.

Now that the preliminary work is done, we start an indefinite forloop that runs until the user chooses to exit.
in this forloop, we set our argument count to 0 (since nothing has been typed out), and we prompt the user to enter a command.
using fgets(similar to cin in C++, but takes more specific parameters), we intake a command into our array***NOTE: COMMAND MUST BE BOUND TO 40CHARACTERS IN THIS DEMO,
WOULD NEED TO HANDLE DYNAMIC ARRAYS IN A REAL DELIVERABLE)
we cut the \n character off the end of our string since it was brought in by the stdin stream, then print the command back to the user.

if its exit, we exit. Otherwise, we keep going.

next is tokenizing the command. We want to separate commands from the original argument obviously, so we use a character pointer and strok() to break the string up based on
whitespace. as we break it up using strok(), we store the resulting token as a char pointer, and add that pointer to our array of character pointers called args (I.E 2d array
of arguments)
After this, we set the value at the index following our last argument to NULL, since UNIX relies on NULL-terminated lists for their system calls.
Then, just for clarity, we print each argument in our list back to the user

then we use the fork() system call to spawn a new process. if successful, we continue, otherwise, wait().

after this we take each path in our paths list and append our command to it. then we use execv() to attempt to run that command at that given path.
we use execv so we can pass the entire arg list.
if the execution is succesful, it returns and everything is good.
if the execution cant find the command binary (because it doesnt exist) we print that is not found and exit(1).