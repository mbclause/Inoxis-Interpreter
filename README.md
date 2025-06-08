# Inoxis Interpreter

**Inoxis** is a memory-safe, statically-typed programming language inspired by Rust's ownership model, but with C++-like syntax. This repository contains a full interpreter for the language, built using C/C++ and ANTLR, and running on a custom virtual machine.

---

## Features

- Rust-style memory safety (ownership, borrowing, mutability)
- C++-like syntax
- Stack- and heap-allocated arrays
- Custom instruction set for a stack-based virtual machine
- Manual lexer, ANTLR-generated parser
- Three-pass AST walker:
  - Symbol resolution
  - Memory safety checking
  - Intermediate representation (IR) generation
- Detailed error reporting with line numbers and messages

---

## Example

```cpp
int main()
{
    int mut *x = new int;
    *x = 10;
    int &y = & mut x;
    cout << "*y = " << *y << endl;
    return 0;
}
```

## Project Structure

main.cpp – Entry point: loads source and starts interpretation

Interpreter.* – Core logic for parsing and execution flow

myLexer.* – Custom lexer implementation

symbolTable.*, MemSafetyPass.*, VMInputPass.* – Three AST passes

VMInput.*, VirtualMachine.*, VMInstruction.* – Virtual machine backend

.antlr/ – ANTLR-generated parser files

Inoxis.g4, lexRules.g4 – Grammar definition for parser and lexer


## Installation

Clone the repository:

    git clone https://github.com/mbclause/Inoxis-Interpreter

Install GLib using vcpkg:

    ./vcpkg install glib:x64-windows-static

Open the solution in Visual Studio 2022 and build it.

Note: The ANTLR runtime and generated parser files are included in the repo, but GLib must be installed separately.

## Usage

From the directory containing the executable:

    Inoxis-Interpreter.exe <input-file.txt>

Ensure iconv-2.dll and your input file are in the same directory as the executable.

## Dependencies

Visual Studio 2022

ANTLR4 (requires Java 8+, JDK 23, and Python 3)

GLib (via vcpkg)

## Test Suite

Over 50 manually written test programs validate the interpreter. These include:

Ownership and borrowing semantics

Memory safety enforcement

Control flow: if, elif, else, while

Pointer/reference usage

Function calls and returns

## Future Work

Planned Improvements

- Add data types: float, double, bool, char, string, etc.

- Support void functions, and more flexible parameter lists

- Add operators: multiplication, division, modulus, and expression parentheses

- Implement optimization passes (peephole, loop)

- Improve scoping using parse tree metadata instead of string search

- Improve interpretation speed with better scope-resolution algorithms

- Fix evaluation order issues in arithmetic expressions

## License

MIT License
