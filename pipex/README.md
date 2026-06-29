*This project has been created as part of the 42 curriculum by <dbrusent>.*

# Pipex

## Description

**Pipex** is a C project from the 42 curriculum that introduces UNIX process management and inter-process communication using pipes.

The objective is to recreate the behavior of the following shell command:
< file1 cmd1 | cmd2 > file2

The program must:

* open input and output files;
* create a pipe between two processes;
* execute commands using `fork()` and `execve()`;
* redirect standard input and output with `dup2()`;
* search executables using the `PATH` environment variable;
* correctly handle system errors and process exit codes;
* properly free allocated memory and close file descriptors.

This project provides practical experience with low-level UNIX programming, process creation, file descriptor management, and communication between processes.

---

# Instructions

## Usage

```sh
make
./pipex file1 "cmd1" "cmd2" file2
```

Example:

```sh
./pipex st_in.txt "grep hello" "wc -l" s_out.txt
```

Equivalent shell command:

```sh
< infile grep hello | wc -l > outfile
```

---

# Features

* Executes two commands connected by a UNIX pipe.
* Resolves executable paths using the `PATH` environment variable.
* Supports both relative and absolute executable paths.
* Handles input/output file redirection.
* Properly manages child processes using `fork()` and `waitpid()`.
* Returns the exit status of the last command, matching shell behavior.
* Cleans up allocated memory and file descriptors.

---

# Technical Overview

The program follows these steps:

1. Parse command-line arguments.
2. Locate executable paths from `PATH`.
3. Create a pipe.
4. Fork the first child:

   * redirect stdin from the input file;
   * redirect stdout to the pipe;
   * execute the first command.
5. Fork the second child:

   * redirect stdin from the pipe;
   * redirect stdout to the output file;
   * execute the second command.
6. Parent process closes unused file descriptors and waits for both children.
7. Exit with the status code of the last command.

---

# Resources

## Documentation

* man 2 pipe & man 2 fork
* man 2 dup & man 2 dup2
* man 2 execve
* peer learning
	Shout out to this guy:
* https://code-vault.net/course/46qpfr4tkz:1603732431896/lesson/cq9yhdt01i:1610029048404
* https://github.com/vfurmane/pipex-tester

---

## AI Usage

AI was used as a learning and productivity tool during the development of this project.
https://chatgpt.com/
https://www.perplexity.ai/

Specifically, AI assisted with:

* understanding process exit statuses and signal handling;
* explaining test cases from pipex-tester;
* answering other silly question, like:
>>I do not understand what is environ in linux C. How to use it? How to pass it into main()?
>>I still donot understand how branches work. Prisiecely: how to use them? Just if(pid > OR < 0)?
👉 You don’t “use branches with fork” — you interpret fork’s return value and let each process naturally fall into its own branch.
>>why not 644?<<	https://quickref.me/chmod.html
	 https://gist.github.com/juanarbol/c44e736be70279c1fd5d68aa24f9d8be
👉 Because 0644 is an octal literal in C, while 644 would be treated as a decimal number and produce the wrong permission bits.

* generating this README.