
# bobcat-cli-tool



bobcat-cli-tool is a command-line utility written in C that mimics the functionality of the `cat` command but does not support any of its options. This project serves as a refresher for building software in the C programming language, with a focus on Linux system calls, buffering file I/O, and memory management.

## Project Goal

The primary goal of this project is to implement a command-line tool, `bobcat`, that reads files sequentially and writes their contents to the standard output. If no files are specified, or if a dash (`-`) is provided as a file operand, `bobcat` reads from the standard input.

## Features

-   Reads files and writes their contents to the standard output.
-   Supports reading from standard input when no files are specified or when a dash (`-`) is used as a file operand.
-   Handles multiple files and standard input interchangeably in command-line order.
-   Efficiently buffers file input and output to ensure reasonable time efficiency.
-   Limits memory usage to at most 1MB regardless of the input size.
-   Ensures no memory leaks by freeing all allocated memory.
-   Utilizes `read` and `write` system calls instead of stdio functions like `fwrite` and `fread`.
-   Produces appropriate error messages and exit codes.

## Usage

The `bobcat` command is invoked with zero or more file operands:

`./bobcat [file ...]` 

### Examples

1.  Print the contents of `file1` to the standard output:
    
    
    `./bobcat file1` 
    
2.  Print the contents of `file1`, then read from standard input, print the contents of `file2`, read from standard input again, and finally print the contents of `file3`:
    
    
    `./bobcat file1 - file2 - file3` 
    
3.  Read from standard input (as no files are specified):
    

    
    `./bobcat` 
    
4.  Print the contents of `file1`, show an error for `hello` (if it does not exist), and then print the contents of `file2`:
    
    
    `./bobcat file1 hello file2` 
    

## Implementation Notes

-   `bobcat` should buffer file input and output for efficiency.
-   Memory usage is limited to 1MB.
-   The tool should not crash and must handle errors gracefully.
-   Uses `read` and `write` system calls exclusively for file operations.
-   All source files are formatted using `clang-format` with the command `make format`.

## Development Setup

**1.  Clone the repository**:
    
    
    `git clone git@github.com:rajatmaheshwari17/bobcat-cli-tool.git` 
    
**2.  Build the project**:
    
   
    `make` 
    
**3.  Format the source files**:

    
    `make format` 
    
**4.  Run the tool**:
    
    
    
    `./bobcat [file ...]` 
    

## Testing and Validation

-   Use `echo $?` to check the return code of the program.
-   Use `valgrind --leak-check=full` to check for memory leaks.
-   Ensure the code works in the specified development environment.

#
_This README is a part of the bobcat-cli-tool Project by Rajat Maheshwari._
