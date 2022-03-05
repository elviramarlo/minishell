# ALLOWED FUNCTIONS

## Readline utils

| Function								| Description																| Other Info / Links															|
|---------------------------------------|---------------------------------------------------------------------------|-------------------------------------------------------------------------------|
| ```char *readline(char *prompt)```							| Waits for user input and returns it as a string	| https://tiswww.case.edu/php/chet/readline/readline.html or ```man```			|
| ```void rl_clear_history()```									| Clear the history list by deleting all of the entries, in the same manner as the History library’s clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list. | http://bashcookbook.com/bashinfo/source/readline-7.0/doc/readline.pdf	|
| ```int rl_on_new_line(void) ``` 								| Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline. | http://bashcookbook.com/bashinfo/source/readline-7.0/doc/readline.pdf	|
| ```void rl_replace_line(const char *text, int clear_undo)```	| Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.	| http://bashcookbook.com/bashinfo/source/readline-7.0/doc/readline.pdf |
| ```void rl_redisplay(void)```									| Change what’s displayed on the screen to reflect the current contents of rl_line_buffer. | http://bashcookbook.com/bashinfo/source/readline-7.0/doc/readline.pdf |
| ```(?) add_history(char *line)```								| Adds a line to readline's history 				| https://web.mit.edu/gnu/doc/html/rlman_2.html									|

## File access

| Function																		| Description													| Other Info / Links	|
|-------------------------------------------------------------------------------|---------------------------------------------------------------|-----------------------|
| ```int access(const char *path, int mode)```									| Used to check file accesibility								| ```man```				|
| ```int open(const char *path, int oflag, ...)```								| Open or create a file for reading or writing					| ```man```				|
| ```ssize_t read(int fildes, void *buf, size_t nbyte)```						| Read from file descriptor										| ```man```				|
| ```int close(int fildes)```													| Close open file												| ```man```				|
| ```char *getcwd(char *buf, size_t size);```									| Get current working directory									| ```man```				|
| ```int chdir(const char *path)```												| Change current working directory								| ```man```				|
| ```int stat(const char *restrict path, struct stat *restrict buf)```			| Get file status												| ```man```				|
| ```int lstat(const char *restrict path, struct stat *restrict buf)```			| Get file status												| ```man```				|
| ```int fstat(int fildes, struct stat *buf)```									| Get file status												| ```man```				|
| ```int unlink(const char *path)```											| Remove directory entry										| ```man```				|
| ```int execve(const char *path, char *const argv[], char *const envp[])```	| Executes a program with args and env vars						| ```man```				|
| ```int dup(int fildes)```														| Duplicate an existing file descriptor							| ```man```				|
| ```int dup2(int fildes, int fildes2)```										| Duplicate an existing file descriptor							| ```man```				|
| ```int pipe(int fildes[2]);```												| Create descriptor pair for interprocess communication			| ```man```				|
| ```DIR *opendir(const char *filename)```										| Opens a directory												| ```man```				|
| ```struct dirent *readdir(DIR *dirp)```										| Reads a directory												| ```man```				|
| ```int closedir(DIR *dirp);```												| Closes a directory											| ```man```				|

## Process control

| Function																								| Description							| Other Info / Links	|
|-------------------------------------------------------------------------------------------------------|---------------------------------------|-----------------------|
| ```pid_t fork(void)```																				| Creates a new process					| ```man```				|
| ```pid_t wait(int *stat_loc)```																		| Waits for process termination			| ```man```				|
| ```pid_t wait3(int *stat_loc, int options, struct rusage *rusage)```									| Waits for process termination			| ```man```				|
| ```pid_t wait4(pid_t pid, int *stat_loc, int options, struct rusage *rusage)```						| Waits for process termination			| ```man```				|
| ```pid_t waitpid(pid_t pid, int *stat_loc, int options)```											| Waits for pid's process termination	| ```man```				|
| ```void (*signal(int sig, void (*func)(int)))(int)```													| Simplified signal processing			| ```man```				|
| ```int sigaction(int sig, const struct sigaction *restrict act, struct sigaction *restrict oact)```	| Signal processing						| ```man```				|
| ```int kill(pid_t pid, int sig)```																	| Send signal to a process				| ```man```				|
| ```void perror(const char *s)```																		| Process error messages				| ```man```				|
| ```char *strerror(int errnum)```																		| System error messages					| ```man```				|

## TTY Control

| Function																					| Description								| Other Info / Links									|
|-------------------------------------------------------------------------------------------|-------------------------------------------|-------------------------------------------------------|
| ```int isatty(int fd)```																	| Checks if File Descriptor is a terminal	| ```man```												|
| ```char *ttyname(int fd)```																| Gets terminal name						| ```man```												|
| ```int ttyslot(void);```																	| Gets user's terminal						| https://man7.org/linux/man-pages/man3/ttyslot.3.html	|
| ```int ioctl(int fildes, unsigned long request, ...)```									| Manipulates a device						| ```man```												|
| ```char *getenv(const char *name)```														| Gets env varible by name					| ```man```												|
| ```int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p)```	| Sets term attributes						| ```man```												|
| ```int tcgetattr(int fildes, struct termios *termios_p)```								| Gets term attributes						| ```man```												|
| ```int tgetent(char *bp, const char *name)```												| Termcap util or smthng (Need more info)	| ```man```												|
| ```int tgetnum(char *id)```																| Termcap util or smthng (Need more info)	| ```man```												|
| ```char *tgetstr(char *id, char **area)```												| Termcap util or smthng (Need more info)	| ```man```												|
| ```char *tgoto(const char *cap, int col, int row)```										| Termcap util or smthng (Need more info)	| ```man```												|
| ```int tputs(const char *str, int affcnt, int (*putc)(int))```							| Termcap util or smthng (Need more info)	| ```man```												|

## Common

| Function		| Description	| Other Info / Links	|
|---------------|---------------|-----------------------|
| ```printf```	|				| ```man```				|
| ```malloc```	|				| ```man```				|
| ```free```	|				| ```man```				|
| ```write```	|				| ```man```				|
| ```exit```	|				| ```man```				|
