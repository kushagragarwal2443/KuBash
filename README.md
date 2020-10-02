# KuBash

This repository contains a Linux shell implemented in C which resembles the Bourne Again Shell

## Run the shell
* Type the command `make`
* Type `./a.out` to launch the shell
* Type `exit` or `quit` or Press `Ctrl+D` to exit the shell

## Commands implemented
The following commands were coded for explicitly. All the other commands are supported by the shell using `execvp()`

### `pwd`
* Returns the present working directory
* Code available in pwd.c and Header files in pwd.h
* #### Usage example
* Input: `pwd`
* Output: /home/kushagra/Documents/A2k20/OS/Assign2/KuBash

### `echo [args]` 
* Prints the contents in `args` on the shell
* Quotations preserve spaces, tabs and carriage returns
* Code available in echo.c and Header files in echo.h
* #### Usage example
* Input: `echo "Operating Systems 2020"`
* Output: Operating Systems 2020

### `cd [dir]`
* Changes working directory to the directory given in `dir`
* If `dir` does not exist then error is flagged
* Both Relative and Absolute paths to the directory supported
* Path relative to cwd for the shell (called ~) is also implemented
* Code available in cd.c and Header files in cd.h
* #### Usage examples
* Input: `kushagra@kushagra:~ cd ~`
* Output: Prompt changes to `kushagra@kushagra:~`
* Input: `kushagra@kushagra:~ cd ~/../../Assign2`
* Output: Prompt changes to `kushagra@kushagra:/home/kushagra/Documents/A2k20/OS/Assign2`

### `ls [-a] [-l] [dir1] [dir2] [dir3]`
* Shows the contents of the various directories given in the arguements
* `-a` flag implemented: Shows hidden files
* `-l` flag implemented: Shows details about each file
* Any permutation of the flags and directories is supported
* Code available in ls.c and Header files in ls.h
* #### Usage examples
* Input: `ls -a ../exampledir`
* Output: `. .. prompt.c  main.c`
* Input: `ls -la ../exampledir`
* Output: <br>
`drwxrwxr-x 3 kushagra kushagra   4096 Sep 09 11:28 . `<br>
`drwxrwxr-x 6 kushagra kushagra   4096 Sep 09 11:50 .. `<br>
`-rw-rw-r-- 1 kushagra kushagra    504 Sep 04 01:55 prompt.c `<br>
`-rw-rw-r-- 1 kushagra kushagra   3865 Sep 09 01:39 main.c `<br>

### `pinfo [pid]`
* Shows the process related information for a process
* If pid is not given as an arguement the pid of the shell is used as default
* Code available in pinfo.c and Header files in pinfo.h
* #### Usage examples
* Input: `pinfo`
* Output: `pid -- 11403` <br>
`Process Status -- R` <br>
`Memory -- 2678784` <br>
`Executable Path -- ~/a.out`

### `history [count]`
* Shows the last count number of commands written in the shell
* The history is stored using history.txt and stores not more than 20 commands
* If no arguement is given then last 10 commands are shown
* Code available in main.c 
* #### Usage examples
* Input: `history 3`
* Output: `cd ~` <br>
`emacs &` <br>
`history 3`

### `setenv [var] [value]`
* Allows the user to set the value of the environment variable [var] to [value]
* If [value] is omitted, the variable's value is set to the empty string.
* It only takes 2 arguements
* Code available in setenv.c and Header files are in setenv.h
* #### Usage examples
* Input: `setenv kush 100`
* Output: On running `env` we see `kush=100`

### `unsetenv [var]`
* Removes the environment variable [var].
* It only takes 1 arguement
* Code available in unsetenv.c and Header files are in unsetenv.h
* #### Usage examples
* Input: `unsetenv kush`
* Output: On running `env` no entry for kush is found



### Background and Foreground processes
* If a command contains `&` as one of the arguements then it is considered a background process
* If a background process exits then the shell displays appropriate message using stderr
* The shell waits until a foreground process is finished

## File Details

### cd.c & cd.h
* Implement the `cd`  command
* Code in cd.c and Header files are in cd.h

### echo.c & echo.h
* Implement the `echo`  command
* Code in echo.c and Header files are in echo.h

### execute.c & execute.h
* Implement all the other commands which are not coded for explicitly
* Codes for background and foreground process handling
* Code in execute.c and Header files are in execute.h

### headers.h
* Contains header files required throughout all the files
* Defines global variables

### history.txt
* Stores last 20 commands written in the shell

### ls.c & ls.h
* Implement the `ls`  command
* Code in ls.c and Header files are in ls.h

### main.c
* Implement the shell and receives user input
* Calls the corresponding command file based on user input

### makefile
* Allows easy compilation of all the c files using a single command `make`

### pinfo.c & pinfo.h
* Implement the `pinfo`  command
* Code in pinfo.c and Header files are in pinfo.h

### prompt.c & prompt.h
* Print the shell prompt `kushagra@kushagra:[curdir]`

### pwd.c & pwd.h
* Implement the `pwd`  command
* Code in pwd.c and Header files are in pwd.h
