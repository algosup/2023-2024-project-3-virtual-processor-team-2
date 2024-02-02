<!-- TODO:
- Link the functional specifications document in my part "before reading"
- Make sure the image is properly linked in my part "parser"
- Make sure the image is properly linked in my part "architecture"
- Tailor the table of contents to the parts I added in the architecture part
- Complete the parts I added in the architecture part
- Need to have the parts I already written in the archi part checked by Maxime Caron to make sure everything's in order.
- Make the diagrams when needed
- Complete the Appendices chapter
-->

| | |
| ----- | ----- |
| Title | Technical specifications for ALGOSUP's virtual processor project |
| Author | Guillaume Deramchi |
| Team | 2 |
| Created on | 01/22/2024 |
| Last updated | 02/02/2024 |  

---

# Approvals

| Reviewer           | Role              | Approved | Date |
| ------------------ | ----------------- | -------- | ---- |
| Enzo Guillouche    | Quality Assurance |          |      |
| Mathias Gagnepain  | Project Manager   |          |      |
| Guillaume Despaux  | Program Manager   |          |      |
| Guillaume Deramchi | Technical Leader  |          |      |
| Maxime Caron       | Software Engineer |          |      |
| Paul Nowak         | Software Engineer |          |      |

---

<details>
<summary>Table of contents</summary>

- [Before reading](#before-reading)
- [1 - Overview](#1---overview)
  - [1.1 - Goals](#11---goals)
  - [1.2 - Objectives](#12---objectives)
  - [1.3 - Success criteria](#13---success-criteria)
- [2 - Usage](#2---usage)
  - [2.1 - Requirements](#21---requirements)
  - [2.2 - Installation](#22---installation)
    - [2.2.1 - Installation with Bash](#221---installation-with-bash)
    - [2.2.2 - Installation with GitHub Desktop](#222---installation-with-github-desktop)
  - [2.3 - Running](#23---running)
- [3 - Scope](#3---scope)
  - [3.1 - In Scope](#31---in-scope)
  - [3.2 - Out of Scope](#32---out-of-scope)
- [4 - Overall Description](#4---overall-description)
  - [4.1 - Hardware & software](#41---hardware--software)
  - [4.2 - Project Folder Structure](#42---project-folder-structure)
  - [4.3 - Conventions](#43---conventions)
    - [4.3.1 - Naming Conventions](#431---naming-conventions)
      - [4.3.1.1 - Folders & files](#4311---folders--files)
      - [4.3.1.2 - Variables](#4312---variables)
      - [4.3.1.3 - Constants](#4313---constants)
    - [4.3.2 - Formatting Conventions](#432---formatting-conventions)
      - [4.3.2.1 - Indentation](#4321---indentation)
      - [4.3.2.2 - Line Length](#4322---line-length)
      - [4.3.2.3 - Line Breaks](#4323---line-breaks)
      - [4.3.2.4 - Comments](#4324---comments)
      - [4.3.2.5 - Whitespace](#4325---whitespace)
- [5 - About AT2](#5---about-at2)
- [6 - Software Architecture](#6---software-architecture)
  - [6.1 - Parsing](#61---parsing)
    - [6.1.1 - `parser.c`](#611---parserc)
    - [6.1.2 - `parser.h`](#612---parserh)
  - [6.2 - Building](#62---building)
    - [6.2.1 - `builder.c`](#621---builderc)
    - [6.2.2 - `builder.h`](#622---builderh)
  - [6.3 - Interpreting](#63---interpreting)
    - [6.3.1 - `iat2.c`](#631---iat2c)
    - [6.3.2 - `iat2.h`](#632---iat2h)
  - [6.4 - Running](#64---running)
    - [6.4.1 - `runner.c`](#641---runnerc)
    - [6.4.2 - `runner.h`](#642---runnerh)
  - [6.5 - Debugging](#65---debugging)
    - [6.5.1 - `debug.c`](#651---debugc)
    - [6.5.2 - `debug.h`](#652---debugh)
  - [6.6 - Testing](#66---testing)
    - [6.6.1 - `test.cc`](#661---testcc)
  - [6.7 - Other files](#67---other-files)
    - [6.7.1 - `ast.h`](#671---asth)
    - [6.7.2 - `stringPlus.c`](#672---stringplusc)
    - [6.7.3 - `stringPlus.h`](#673---stringplush)


- [7 - Appendices]
  - Glossary
  - Contributors
  - acknowledgments
  - related documents
  - License
  - References


</details>

---

# Before reading

Make sure to read the [functional specifications]<!--TOLINK--> before reading this document, it will provide you useful information about what we aim to do for this project, as the functional is more focused on the "What" and the technical is more focused on the "How".

---
# 1 - Overview

## 1.1 - Goals

The objective of this project is to create a virtual processor and an interpreter for a customized assembly language. By using C standard libraries, the main aim is to develop a concise assembly language and construct a C program interpreter that can execute and validate assembly code. This solution is specifically designed for educational purposes and software developers who are keen on delving into low-level programming and processor emulation.

## 1.2 - Objectives

The project aims to achieve the following objectives:

1. Create a concise assembly language with an ample range of instructions.
2. Construct an interpreter that can effectively execute assembly code.
3. Construct an interpreter that can validate assembly code for errors.
4. Design the interpreter to be user-friendly and easily accessible.
5. Ensure compatibility of the interpreter with various operating systems.

## 1.3 - Success criteria

The project's success will be determined by meeting the following conditions:

1. The interpreter must have the ability to execute assembly code effectively.
2. The interpreter should be compatible with the widely used operating systems.
3. All the instructions in the set must be implemented completely.

# 2 - Usage

The interpreter is designed to provide a user-friendly and easy-to-use experience. It is developed to integrate with popular operating systems and can execute assembly code while also checking for errors. Additionally, the interpreter can display the output of the assembly code. Below are the instructions for installing and running the interpreter.

## 2.1 - Requirements

To run your custom assembly code, you will need to install the following dependencies:

- [VS Code](https://code.visualstudio.com/download) - Visual Studio Code is a free source-code editor made by Microsoft for Windows, Linux and macOS.
- [C/C++ for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) - C/C++ for Visual Studio Code is an extension for VS Code that provides IntelliSense, debugging, and code browsing support for C and C++ code.
- [GCC](https://gcc.gnu.org/install/) - GCC, the GNU Compiler Collection, is a free collection of compilers for C, C++, Objective-C, Fortran, Ada, Go, and D programming languages.
- [CMake](https://earthly.dev/blog/installandrun-cmake-on-windows/) - CMake is an open-source, cross-platform family of tools designed to build, test, and package software by managing the compilation process across different systems.

Our software is developed using the C99 version of the C language.

## 2.2 - Installation

To install the interpreter, you will need clone the repository on your local machine.

### 2.2.1 - Installation with Bash

Open a terminal and run the following commands:

If you are on macOS:

```bash
git clone https://github.com/algosup/2023-2024-project-3-virtual-processor-team-2.git
cd 2023-2024-project-3-virtual-processor-team-2
```

### 2.2.2 - Installation with GitHub Desktop

Download and open GitHub Desktop and click on `File > Clone Repository`. Select the URL tab and enter the following URL:

```bash
https://github.com/algosup/2023-2024-project-3-virtual-processor-team-2.git
```

Then click on `Clone`.

## 2.3 - Running

To run the interpreter, you will need to follow these steps:

1. Create a bin folder.
2. Compile it with CMake (using the CMakeLists.txt file).
3. Add the interpreter to your computer path.

# 3 - Scope

## 3.1 - In scope

The project encompasses the following functionalities:

1. Fundamental assembly language with a concise set of instructions.
2. An interpreter that can execute assembly code.
3. An interpreter that can check errors in the assembly.
4. A user-friendly usage.
5. Compatibility with prevalent operating systems.

## 3.2 - Out of scope

The following features will be excluded from the project:

1. Sophisticated assembly language with a intricate array of instructions.
2. Graphical user interface.
3. Debugging tools.
4. Compatibility with specific hardware configurations.
5. Compatibility with other programming languages.
6. Real-time performance analysis.
7. Advanced memory management.

---

# 4 - Overall description

## 4.1 - Hardware & software

The interpreter is designed to be compatible with the most prevalent hardware configurations and will undergo testing on the hardware listed below:

| Specification    | Lenovo ThinkBook 14  | Lenovo ThinkBook 14  | Lenovo ThinkPad 2023 |
| ---------------- | -------------------- | -------------------- | -------------------- |
| Processor        | Intel Core I7-1065G7 | Intel Core i7-1255U  | Intel Core i7-1355U  |
| RAM              | 16GB                 | 16 GB                | 16GB                 |
| Operating System | Windows 11 Pro       | Windows 11 Pro       | Windows 11 Pro       |

The interpreter will undergo compatibility testing on Windows 11 pro, version 22H2.

## 4.2 - Project folder structure

The folder structure for the project will be as follows:


``` folder
├── 2023-2024-project-3-virtual-processor-team-2 (root)
|   ├── documents
|   |   ├── communications
|   |   |   ├── minutes_of_meeting_01_16_2024.pdf
|   |   ├── functional
|   |   |   ├── 2023_2024_project_3_virtual_processor.pdf
|   |   |   ├── at2_assembly_language_documentation.md
|   |   |   ├── functional_specification_document_template.md
|   |   ├── images
|   |   |   ├── functional_images
|   |   |   |   ├── interpreter_mockup.png
|   |   |   |   ├── virtual_terminal.png
|   |   |   ├── qa_images
|   |   |   |   ├── test_case_pattern.png
|   |   |   |   ├── test_report_pattern.png
|   |   |   ├── technical_images
|   |   |   |   ├── state_diagram_parser_c.jpg
|   |   |   |   ├── archi_interpreter_diagram.jpg
|   |   |   |   ├── data_structure_diagram.jpg
|   |   ├── management
|   |   |   ├── weekly_reports
|   |   |   |   ├── cumulative.md
|   |   |   |   ├── week_1.md
|   |   |   |   ├── week_2.md
|   |   |   |   ├── week_3.md
|   |   |   |   ├── week_4.md
|   |   |   |   ├── week_5.md
|   |   |   |   ├── week_6.md
|   |   |   |   ├── week_7.md
|   |   |   |   ├── week_8.md
|   |   |   ├── management_artifact.md
|   |   ├── qa
|   |   |   ├── code_documentation_template.md
|   |   |   ├── meetings_reports.md
|   |   |   ├── qa_collaboration.md
|   |   |   ├── test_cases.md
|   |   |   ├── test_plan.md
|   |   |   ├── test_reports.md
|   |   ├── technical
|   |   |   ├── roadmap.md
|   |   |   ├── technical.md
|   ├── .gitignore
|   ├── CODE_OF_CONDUCT.md
|   ├── CONTRIBUTING.md
|   ├── LICENSE
|   ├── README.md
|   ├── SECURITY.md
```

## 4.3 - Conventions

### 4.3.1 - Naming Conventions

It is crucial to adhere to naming conventions in order to maintain a well-organized directory structure. Our project will adopt the subsequent naming conventions.

#### 4.3.1.1 - Folders & files

All the folders and files will be written in `snake_case`. 
Apart the following files that will be written in `UPPER_SNAKE_CASE`:
- `CODE_OF_CONDUCT.md`
- `CONTRIBUTING.md`
- `LICENSE`
- `README.md`
- `SECURITY.md`
And the `.gitignore` will be written this way.

#### 4.3.1.2 - Variables

Variable and functions names will be written in `camelCase`.

#### 4.3.1.3 - Constants

- Constant names will be written in `UPPER_SNAKE_CASE`.
- All #define will be written at the same place.

### 4.3.2 - Formatting Conventions

Formatting conventions are important to keep a clear, concise and readable code, Our project will adhere to the subsequent formatting conventions.

#### 4.3.2.1 - Indentation

Indentation will be done with 1 tab.

<!--TOCHECK-->
#### 4.3.2.2 - Line Length 

Lines will be limited to 64 characters, whether it's a line of code or a comment.

<!--TOCHECK-->
#### 4.3.2.3 - Line Breaks

- Break the line:
  - Two spaces before a function call or declaration.
  - One space between each variable declaration.
- Do not break the line:
  - Between a function name and its parameters.
  - In an `if` or a `switch` statement.
  - In a `for` or a `while` loop.

#### 4.3.2.4 - Comments

Comments will be written in English, on the line above the code they refer to and in `Sentence case`.

#### 4.3.2.5 - Whitespace

Whitespace is used to separate the elements of an instruction but is otherwise not significant.

# 5 - About AT2

We decided to rename our custom assembly language to "AT2"(Assembly Team 2). Its extension will be `.aop` (Assembly Operation Processor).  

For the complete reference manual, which includes the entire set of instructions with concrete examples, please refer to the **[AT2 language documentation](../functional/at2_language_documentation.pdf)**.

**Please make sure to read and understand it completely before going further in this document**.


# 6 - Software Architecture

The processor emulated will be a 16 bits processor, with 8 registers of 16 bits each, with one dedicated for the clock only, so 7 usable registers.

The interpreter will work as follows: 

<!--LINK THE ARCHITECTURE DIAGRAM HERE-->

**Diagram explanantion**:

- **Parser**<br>The parser is the first part of the interpreter: 
   - Reads input files.
   - Analyses the instructions.
   - Put the instructions in an algorithmic structure.

- **Builder**<br>The builder is the second part of the interpreter:
   - Reads the algorithmic structure.
   - Replaces some parts to make them readable for the Virtual processor.

- **Virtual processor**<br>The last part of the interpreter:
   - Executes the program regarding the algorithmic structure.


## 6.1 - Parsing

### 6.1.1 - `parser.c`

This component is accountable for the retrieval and analysis of AT2 code from a file. Its main tasks encompass reading lines from the file, analyzing the instructions, converting them into an algorithmic structure, and arranging the data for subsequent processing. It employs a range of functions to manage file operations, manipulate strings, and structure the data.

**The `parser.c` file will have these key features**:

- `parseArgs`: This function is designed to parse command-line arguments. It checks the number of arguments and sets flags based on the arguments provided. It handles cases like too many arguments, invalid flags, and help/version/debug/verbose flags.

- `flagsSet`: This function is responsible for setting specific flags based on the command-line argument provided. It compares the argument with known flags like `-h/--help`, `-v/--version`, `-d/--debug`, and `-V/--verbose` and sets the corresponding flag in the `flags_t` structure.

- `parseFile`: This function opens and reads an assembly file line by line. It checks if the file exists and validates its extension. For each line in the file, it creates an instruction node by parsing the line and then adds the node to an instruction list.

- `parseLine`: This function checks if a line from the input file is empty or a comment. If not, it parses the line to extract an instruction and its arguments, and creates an instruction node `(instNode_t)`. It also determines the type of instruction (operation, action, or declaration) and sets the corresponding fields in the node.

- `isOp`: This function checks if a given string represents an operation instruction. It compares the string with known operation mnemonics like `add`, `sub`, `mul`, etc., and sets the appropriate operation type in the node.

- `isAct`: Similar to `isOp`, this function checks if a string represents an action instruction. It handles action instructions like `goto`, `mov`, `call`, etc., and sets the corresponding action type in the node.

- `isDecla`: This function identifies declaration instructions like `lab` and `var` and sets the instruction type in the node accordingly.

- `getInst`: Extracts the instruction (first word) from a given line. It tokenizes the line to get the instruction name.

- `getInstArgs`: Splits a given line into arguments using a comma as a delimiter. It tokenizes the line to extract two possible arguments and returns them in an array.

- `checkAOPFile`: This function checks if the provided filename has the correct `.aop` extension, ensuring that the file is of the expected type for parsing.

**Utilization**: This file enables the parsing of an assembly file into a structured format, setting up the groundwork for further processing by the interpreter.

**Diagram**:  

![Parser.c](../images/technical_images/State-Diagram-parserC.jpg)

### 6.1.2 - `parser.h`

The `parser.h` file defines the interface for the parsing component of the interpreter.

**The `parser.h` file will have these key features**:

- `flags_t` Structure: Used to store flags indicating how the program should run, based on command-line arguments.

- `parseArgs`: Takes command-line arguments and sets flags in the `flags_t` structure accordingly.

- `flagsSet`: Sets specific flags in the `flags_t` structure based on the given flag string.

- `parseFile`: Reads the file, line by line, and converts each line into structured instruction nodes.

- `parseLine`: Converts a single line from the file into an instruction node with the relevant details like instruction type, arguments, etc.

- `isOp`: Checks if a line represents an operation and updates the instruction node if it does.

- `isAct`: Determines if a line is an action instruction and updates the instruction node accordingly.

- `isDecla`: Identifies if a line is a label or variable declaration and updates the instruction node.

- `getInst`: Extracts the instruction from a line.

- `getInstArgs`: Splits a line into its arguments (if any) and returns them.

- `checkAOPFile`: Ensures that the file being parsed has the correct `.aop` extension.

Each function and the structure in `parser.h` provide the necessary tools for breaking down and interpreting assembly code into a format that the interpreter can understand and work with.


## 6.2 - Building

### 6.2.1 - `builder.c`

The `builder.c` file processes parsed instruction nodes, constructing a structured executable program suitable for interpretation by the virtual processor.

**The `builder.c` file will have these key features**:

1. **Build Function (`build`)**:
   - Initializes a Last-In-First-Out (LIFO) structure for handling if/else statements.
   - Iterates through the list of parsed instructions (`nodeList`).
   - Builds appropriate structures based on the type of node (operation, action, label).

2. **Action Node Building (`buildActNode`)**:
   - Checks if the current instruction node (`instNode_t`) is an action.
   - If so, it delegates the building process to specific functions based on the action type.

3. **Comparison Node Building (`buildCmpNode`)**:
   - Handles comparison statements (if, else, end) within the instruction node.
   - Manages the flow of conditional statements using the LIFO stack for tracking nested comparisons.
   - Sets goto labels for else and end statements in conditional blocks.

4. **Label Node Building (`buildLabelNode`)**:
   - Checks for and handles label declarations in the instruction list.
   - Adds new labels to the label list (`labelList_t`), ensuring no duplicate labels.

5. **Label List Management (`addLabel`, `incLabelList`)**:
   - `addLabel`: Adds a new label to the label list.
   - `incLabelList`: Increases the size of the label list if it's full, reallocating memory accordingly.

6. **LIFO Stack Management (`pushCmpLifo`, `popCmpLifo`)**:
   - Manages a LIFO stack for comparison nodes.
   - `pushCmpLifo`: Adds a new comparison node to the stack.
   - `popCmpLifo`: Removes the top comparison node from the stack and returns it.

### 6.2.2 - `builder.h`

The `builder.h` file defines functions and data structures for building the executable structure of the virtual processor's program from the parsed instruction nodes.

**The `builder.h` file will have these key features**:

- `lifoCmpNode_t` Structure: Defines a LIFO (Last In, First Out) data structure to manage if/else statement construction during the build process.

- `build`: Reads nodes from the instruction list and constructs the program, integrating actions, comparisons, and labels.

- `buildActNode`: Constructs an action node from an instruction node, interpreting it in the context of the program flow.

- `buildCmpNode`: Builds a comparison node, essential for if/else and similar conditional constructs in the program.

- `buildLabelNode`: Creates a label node to manage goto statements and label definitions in the program.

- `addLabel`: Adds a new label to the label list, which is crucial for referencing different parts of the program.

- `incLabelList`: Expands the label list size to accommodate more labels, ensuring dynamic scalability.

- `pushCmpLifo`: Adds a comparison node to the lifo, aiding in the construction of nested and complex conditional statements.

- `popCmpLifo`: Removes the top comparison node from the lifo, assisting in resolving conditional structures.

These functions enable the virtual processor to interpret and execute the code by providing a clear organizational framework and handling the complexity of conditional logic and program flow control.

## 6.3 - Interpreting

### 6.3.1 - `iat2.c`

We chose to name the interpreter files of the project "iat2"(Interpreter of the Assembly Team 2). We thought it could be a sort of subtile differenciation with other's projects.

**The `iat2.c` file will have these key features**:
<!--TODO-->

### 6.3.2 - `iat2.h`
<!--TODO-->

## 6.4 - Running

### 6.4.1 - `runner.c`
<!--TODO-->

### 6.4.2 - `runner.h`
<!--TODO-->

## 6.5 - Debugging

### 6.5.1 - `debug.c`
<!--TODO-->

### 6.5.2 - `debug.h`
<!--TODO-->

## 6.6 - Testing

### 6.6.1 - `test.cc`
<!--TODO-->

## 6.7 - Other files

### 6.7.1 - `ast.h`
<!--TODO-->

### 6.7.2 - `stringPlus.c`
<!--TODO-->

### 6.7.3 - `stringPlus.h`
<!--TODO-->

## 6.8 - Code organization

- **Header files (`.h`)**: The prototype and comments of the functions are in the header files. All enumerations and structures/typedefs are also defined in these files. This approach providES a clear interface for each module.

- **Implementation files (`.c`)**: The function definitions (implementations) are in the `.c` files. Comments explaining the implementation details should also be included in these files. This separation of interface and implementation facilitates maintainability and readability of the code.

## 6.9 - Error system

The error system will work as follows:











# Glossary

| Term | Definition |
| ---- | ---------- |
| Assembly Language | A low-level programming language used to communicate with a computer's hardware, using symbolic code rather than binary. |
| Interpreter | A program that directly executes instructions written in a programming or scripting language, without requiring them to be compiled into a machine language program. |
| Parser | A component that interprets text data to convert it into a format understandable by the computer. |
| Builder | In the context of programming, a builder constructs a final product or executable from source code. |
| Virtual Processor | A simulated version of a computer processor, used to emulate the functionality of a physical processor. |
| LIFO (Last-In-First-Out) | A method of processing data where the most recently added item is the first to be removed. |
| GitHub Desktop | A graphical user interface for managing GitHub repositories on a personal computer. |
| Bash | A Unix shell and command language, often used for scripting in various operating systems. |
| `.aop` Extension | A custom file extension, used for files containing AT2 code. |
| Debugging | The process of identifying and resolving bugs or errors in computer software. |
