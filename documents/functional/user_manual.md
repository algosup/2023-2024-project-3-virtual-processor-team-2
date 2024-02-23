<img src="../images/IAT2/png/iat2_logo_256px.png" alt="IAT2 Logo" style="display: block; margin: auto;">

# User Manual

## Table of Contents
- [User Manual](#user-manual)
  - [Table of Contents](#table-of-contents)
  - [1. Introduction](#1-introduction)
  - [2. Getting Started](#2-getting-started)
    - [2.1 Installation](#21-installation)
  - [3. Execution](#3-execution)
    - [IAT2](#iat2)
      - [Assembler](#assembler)
      - [Virtual Processor](#virtual-processor)
  - [4. Troubleshooting](#4-troubleshooting)
    - [4.1 Common Issues](#41-common-issues)
    - [4.2 FAQs](#42-faqs)
      - [Can I use negative numbers ?](#can-i-use-negative-numbers-)
      - [Can I use VAT2 to execute my own binary file ?](#can-i-use-vat2-to-execute-my-own-binary-file-)
      - [Can I execute 2AT2's binary on real hardware ?](#can-i-execute-2at2s-binary-on-real-hardware-)
  - [5. Appendix](#5-appendix)
    - [5.1 Glossary](#51-glossary)
    - [5.2 AT2 documentation](#52-at2-documentation)

## 1. Introduction

Welcome to the User Manual for [IAT2](#iat2-id). This guide is designed to help you understand and use the features of our product efficiently.

## 2. Getting Started

### 2.1 Installation

Follow these steps to install [IAT2](#iat2-id):
*if you don't have git installed [CLICK HERE TO DOWNLOAD](https://git-scm.com/download/win).*
*if you don't have gcc installed [CLICK HERE TO DOWNLOAD](https://www.devdungeon.com/content/install-gcc-compiler-windows-msys2-cc).*
*if you don't have msys2 installed [CLICK HERE TO DOWNLOAD](https://www.msys2.org/).*

  1. Clone the repository: ``git clone https://github.com/algosup/2023-2024-project-3-virtual-processor-team-2.git``
  2. Go at the project root
  3. Build the project
     - How to use with mingw: (Windows)
       - Execute cmake -S . -B Build -G "MinGW Makefiles"
       - Execute cd Build
       - Execute mingw32-make
     - How to use with msys2: (Windows)
       - Execute cmake -S . -B Build -G "MSYS Makefiles"
       - Execute cd Build
       - Execute make

## 3. Execution

### [IAT2](#iat2-id)

[IAT2](#iat2-id) is planned to compile and execute in a single step, if you want to compile and execute separatly your can refer to [Assembler (Compile)](#assembler) and [Virtual Processor (Execute)](#virtual-processor).

#### Assembler
| Command | alias | Usage | output |
|---|---| --- | --- |
| ``2at2 <path/file.aop> [param]``| | Compile your [.aop](#aop-id) file | binary file |
| ``2at2 --help`` | ``2at2 -h`` | Display the list of command for [2at2](#2at2-id) | |
| ``2at2 --version`` | ``2at2 -v`` | Display the version of [2at2](#2at2-id) | |
| ``2at2 <file> --debug`` | ``2at2 <file> -d`` | Compile the program with the debugger | 2at2.log |
| ``2at2 <file> --verbose`` | ``2at2 <file> -V`` | Compile the pragram with the advanced debugger | 2at2.log |

#### Virtual Processor

Type: ``vat2`` to run the virtual processor and open the virtual terminal.

*Virtual terminal commands:*

| Command | Usage |
|---|--- |
| ``<path/binary_file>``| Execute your binary file |
| ``help`` |  Display the list of command for [vat2](#vat2-id) |
| ``clear`` | Clear the terminal |
| ``exit`` | Close the terminal | 

## 4. Troubleshooting

### 4.1 Common Issues

|Issue | Solution |
|---|---|
|||

Your issue is not here ?<br>
You can also refer to [GitHub Issues](https://github.com/algosup/2023-2024-project-3-virtual-processor-team-2/issues).

### 4.2 FAQs

#### Can I use negative numbers ?
- **No**, unfortunatly negative number are not handle yet, but planned for the V2.

#### Can I use [VAT2](#vat2-id) to execute my own binary file ?
- **Yes and No**, You can only if you use the same binary syntax as [2AT2](#2at2-id).

#### Can I execute [2AT2](#2at2-id)'s binary on real hardware ?
- **Probably No**, unless you find a real hardware using the same syntax *(If you found tell it to us)*

## 5. Appendix

### 5.1 Glossary

| Name | Definition |
| --- | --- |
| <span id="iat2-id">IAT2</span> | Integral Assembler Team 2 (Assembler + Virtual Processor) |
| <span id="2at2-id">2AT2</span> | Assembler Assembly Team 2 |
| <span id="vat2-id">VAT2</span> | Virtual processor Assembly Team 2 |
| <span id="aop-id">.aop</span> | [Aop](#aop-id) Original Program (extension of AT2 language) |
| <span id="at2-id">AT2</span> | Assembly Team 2 |

### 5.2 [AT2](#at2-id) documentation

You can refer to the [AT2]((#at2-id))'s documentation [HERE](../functional/at2_language_documentation.pdf).