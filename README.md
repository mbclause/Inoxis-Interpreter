# Inoxis Interpreter

Inoxis is a memory-safe, statically-typed programming language inspired by Rust's ownership model, but with C++-like syntax. This repository contains a full interpreter for the language, built using C/C++ and ANTLR, and running on a custom virtual machine.
Features

    Rust-style memory safety (ownership, borrowing, mutability)

    C++-like syntax

    Stack- and heap-allocated arrays

    Custom instruction set for a stack-based virtual machine

    Manual lexer, ANTLR-generated parser

    Three-pass AST walker: symbol resolution, memory safety checking, and IR generation

    Detailed error reporting with line numbers and messages

Example Code

int main()
{
    int mut *x = new int;
    *x = 10;
    int &y = & mut x;
    cout << "*y = " << *y << endl;
    return 0;
}

Project Structure

    main.cpp – Entry point: loads source and starts interpretation

    Interpreter.* – Core logic for parsing and execution flow

    myLexer.* – Custom lexer implementation

    symbolTable.*, MemSafetyPass.*, VMInputPass.* – Three AST passes

    VMInput.*, VirtualMachine.*, VMInstruction.* – Virtual machine backend

    .antlr/ – ANTLR-generated parser files

    Inoxis.g4 – ANTLR grammar definition

Installation

    Clone the repository:

git clone https://github.com/mbclause/Inoxis-Interpreter

Install GLib via vcpkg:

    ./vcpkg install glib:x64-windows-static

    Build using Visual Studio 2022.

Usage

To run a compiled .exe:

Inoxis-Interpreter.exe <input-file.txt>

Ensure iconv-2.dll and your input file are in the same directory as the executable.
Dependencies

    Visual Studio 2022

    ANTLR4 (Java 8+, JDK 23, Python 3)

    GLib (via vcpkg)

Test Suite

Over 50 test programs validate the interpreter. These include:

    Memory safety violations (ownership/borrow checking)

    Pointer/reference usage

    Control flow constructs (if/elif/else, while)

    Function calls and return semantics

Limitations & Future Work

    No variable declarations or return inside control blocks

    No pointer/reference/array function arguments

    Fixed array sizes only

    Planned: more data types, operator support, optimization passes

License

MIT License
