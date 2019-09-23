# AUEP

## Schedule from 2019-07-11

- `2019-07-11` Chapter 3.4
- `2019-07-11` Chapter 3.6
- `2019-07-12` Chapter 3.12
- `2019-07-12` Chapter 3.14
- `2019-07-13` Chapter 3.16
- `2019-07-14` Exercises 3.4
- `2019-07-15` Chapter 4.8
- `2019-07-22` Chapter 4.14
- `2019-07-22` Chapter 4.19
- `2019-07-23` Exercises 4.4
- `2019-07-29` Chapter 5.4
- `2019-07-30` Chapter 6.1
- `2019-08-05` Chapter 7.1
- `2019-08-19` Chapter 7.5
- `2019-08-27` Chapter 7.9
- `2019-08-30` Chapter 7.11
- `2019-09-01` Chapter 8.3
- `2019-09-06` Chapter 8.4
- `2019-09-08` Chapter 8.10
- `2019-09-14` Chapter 8.12

## Exercises not solved

- Exercise 5.7 [hard]
- Exercise 7.4 [can't understand]

## Exervises writed more

- ch07/e7-3.md, "my tipical solution approach".

## Excerpts from the book

- `[f8.17, p255] -> [shell prompt print, p234]`
Note that the shell prints its prompt when the original process
terminates, which is before the second child prints its parent process ID.

-  `[ch8.11, p255] -> [set-user-ID bit, p99]`
When we execute a program file, the effective user ID of the process is usually
the real user ID, and the effective group ID is usually the real group ID.
However, we can also set a special flag in the file's mode word (st_mode) that
says, "When this file is executed, set the effective user ID of the process to
be the owner of the file (st_uid)."
For example, if the owner of the file is the superuser and if the file's
set-user-ID bit is set, then while that program file is running as a process, it
has superuser privileges. This happens regradless of the real user ID of the
process that executes the file. As an example, the UNIX system program that
allows anyone to change his or her password, `passwd`, is a set-user-ID program.
This is required so that the program can write new password to the password file
, typically either `/etc/passwd` or `/etc/shadow`, files that should be writable
only by the superuser. Because a process that is running set-user-ID to some
other user usually assumes extra permissions, it must be written carefully.

- `[ch8.13, p264] put a time-and-date stamp into a certain file`
We could use the functions described in Section 6.10 to do this: call `time` to
get the current calendar time, then call `localtime` to convert it to a
broken-down time, then call `strftime` to format the result, the finally write
the result to the file.

- `[ch8.10, p254] set arg0 in exec functions to be the filename`
Note also that we set the first argument, `argv[0]` in the new prgram, to be the
filename componment of the pathname. Some shell set this argument to be the
complete pathname. This is a convention only; we can set `argv[0]` to any string
we like.

