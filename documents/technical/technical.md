### Technical Specifications Document
### ALGOSUP Project 3, 2024

# Virtual processor and Assembly language for old mobile phone emulation

### Version: 0.2
### Date: 01/25/2024

---

## Table of contents
1. [Introduction](#1-introduction)
2. [Project overview](#2-project-overview)
3. [Hardware specifications](#3-hardware-specifications)
   1. [Virtual processor](#31-virtual-processor)
   2. [Memory](#32-memory)
   3. [Display](#33-display)
   4. [Keypad input](#34-keypad-input)
   5. [Sound and audio](#35-sound-and-audio)
   6. [Power management](#36-power-management)
4. [Our new Assembly language specifications](#4-our-new-assembly-language-specifications)
   1. [Instruction set](#41-instruction-set)
   2. [Syntax and conventions](#42-syntax-and-conventions)
   3. [Memory management](#43-memory-management)
   4. [Input and output handling](#44-input-and-output-handling)
5. [Development tools](#5-development-tools)
   1. [Assembler](#51-assembler)
   2. [Debugger](#52-debugger)
   3. [Testing framework](#53-testing-framework)
   4. [Code organization](#54-code-organization)
6. [Testing and validation](#6-testing-and-validation)
   1. [Unit testing](#61-unit-testing)
   2. [Integration testing](#62-integration-testing)
   3. [Performance testing](#63-performance-testing)
7. [Documentation](#7-documentation)
8. [Appendices](#8-appendices)
   1. [References](#81-references)
   2. [Glossary](#82-glossary)

---

## 1. Introduction

This project involves developing a **[virtual processor](#virtual-processor)** and a custom **[Assembly language](#Assembly-language)** to emulate the typical environment of old mobile phones. It aims to create a virtualized system that accurately simulates the functionalities of these devices, focusing on general characteristics common to this category.

---

## 2. Project overview

The project's scope encompasses the creation of a generalized old mobile phone **[emulator](#emulator)**, using a virtual processor with custom specifications, not limited to any specific existing hardware like the ARM7TDMI. The Nokia 3310 is used as a reference point for typical features and functionalities found in old mobile phones.

---

## 3. Hardware specifications

### 3.1 Virtual processor

#### Processor specifications
- Custom-designed **[processor](#processor)** specifications, tailored to emulate common functionalities of old mobile phones.
- The processor will be inspired by typical characteristics of old mobile phone processors.

#### Processor capabilities
- Capabilities include basic arithmetic operations, input/output operations, and interaction with emulated components.

### 3.2 Memory
- Memory architecture details, including **[ROM](#rom)** and **[RAM](#ram)** specifications for the emulator.

### 3.3 Display
- Emulating a basic monochrome LCD typical of old mobile phones, with text and simple graphics capabilities.

### 3.4 Keypad input
- Simulating keypad input, including numeric and function keys typical of old mobile phones.

### 3.5 Sound and audio
- Emulating audio functions such as monophonic ringtones and beeps.

### 3.6 Power management
- The emulator will show a static battery level, either consistently at 100% or mirroring the host computer's battery status.

---

## 4. Our new Assembly language specifications

### 4.1 **[Instruction set](#instruction-set)**
- **Arithmetic and [bitwise operations](#bitwise-operation)**:
  - `OP_ADD`: Addition operation. Adds values of two **[registers](#register)** or a register and an immediate value.
  - `OP_SUB`: Subtraction operation. Subtracts the second **[operand](#operand)** from the first.
  - `OP_DIV`: Division operation. Divides the first operand by the second.
  - `OP_MUL`: Multiplication operation. Multiplies two operands.
  - `OP_MOD`: Modulus operation. Computes the remainder of division of two operands.
  - `OP_R_SHIFT`: Right shift operation. Shifts bits of the operand to the right.
  - `OP_L_SHIFT`: Left shift operation. Shifts bits of the operand to the left.
  - `OP_B_OR`: Bitwise OR operation. Performs bitwise OR on two operands.
  - `OP_B_AND`: Bitwise AND operation. Performs bitwise AND on two operands.
  - `OP_B_NOT`: Bitwise NOT operation. Inverts the bits of the operand.
  - `OP_B_XOR`: Bitwise XOR operation. Performs bitwise exclusive OR on two operands.

#### Comparison types (`cmpKind`)
- **Logical operations for conditional processing**:
  - `CMP_OR`: Logical OR comparison. Evaluates to true if either of the operands is true.
  - `CMP_AND`: Logical AND comparison. Evaluates to true only if both operands are true.
  - `CMP_NOT`: Logical NOT comparison. Inverts the truth value of the operand.
  - `CMP_XOR`: Logical XOR comparison. Evaluates to true if operands are different.

#### Action types (`actionKind`)
- **Control flow instructions**:
  - `ACT_IF`: Conditional execution. Executes theAssembly language following block if the condition is true.
  - `ACT_ELSE`: Else block for a conditional. Executes if the `ACT_IF` condition is false.
  - `ACT_LOOP`: Begins a loop structure. Continues execution until a condition is met.
  - `ACT_END`: Marks the end of a control flow block, like the end of an if-else or loop.
  - `ACT_MOV`: Move operation. Transfers data from one register to another or to/from memory.
  - `ACT_JMP`: Unconditional jump. Alters the flow of execution to a new address.
  - `ACT_CALL`: Calls a subroutine. Jumps to subroutine address and maintains return address.
  - `ACT_RET`: Return from subroutine. Returns control to the calling function.
  - `ACT_GET_CLK`: Retrieves the current value of the system clock or timer.

#### Instruction types (`instKind`)
- **Categorization of assembly instructions**:
  - `INST_OP`: Denotes an operation instruction, performing arithmetic or bitwise computation.
  - `INST_CMP`: Represents a comparison instruction, used in conditional statements.
  - `INST_ACT`: Action instruction that influences the control flow or performs a specific task.
  - `INST_LABEL`: A label instruction, used as a marker or target for jumps and calls.

#### Register types (`regKind`)
- **Register enumeration for the virtual processor**:
  - `RG_0`, `RG_1`, ..., `RG_7`: Enumeration of registers available in the virtual processor. These registers are used for storing temporary data, performing operations, and maintaining state within the processor.


### 4.2 Syntax and conventions

The **[syntax](#syntax)** and conventions of the Assembly language are designed to be intuitive and aligned with standard practices in Assembly language programming. This section outlines the fundamental syntax rules for instructions, registers, **[memory addressing](#memory-addressing1)**, and data types.

#### Instruction syntax
- **Format**: Instructions generally follow the format of `INSTRUCTION <operands>`. Operands can be registers, immediate values, or memory addresses.
- **Example**: `OP_ADD RG_0, RG_1` - This instruction adds the contents of `RG_1` to `RG_0`.

#### Register syntax
- **Usage**: Registers are referred to by their names, such as `RG_0`, `RG_1`, etc.
- **Context**: Used as operands in instructions for operations like data movement, arithmetic operations, etc.

#### Memory addressing
- **Direct Addressing**: Accesses the memory directly using an address. For example, `[address]` where `address` is a memory location.
- **Indirect addressing**: Uses a register to point to a memory address. For example, `[RG_0]` would access the memory location pointed to by `RG_0`.

#### Data types
- **Immediate values**: Constants or literals directly used in instructions. For example, `OP_ADD RG_0, 5` adds the value `5` to the contents of `RG_0`.
- **Binary and hexadecimal support**: The language supports both **[binary](#binary)** (`0b0101`) and **[hexadecimal](#hexadecimal)** (`0x1A`) literals for ease of low-level programming.

#### Conventions
- **Case sensitivity**: The language is case-sensitive. All instructions and register names must be used in the correct case.
- **Whitespace**: Whitespace is used to separate the elements of an instruction but is otherwise not significant.
- **Comments**: Comments start with either "//" for one-line comments or "/*........*/" for multiple-lines comments, the same comments convention as C language. For example "// Add the value 3 to myFunction"

### 4.3 Memory management

#### Memory architecture
- **Memory types**: The virtual processor will simulate a basic memory architecture comprising both ROM (Read-Only Memory) and RAM (Random Access Memory).
- **ROM**: Used to store the emulator's firmware and immutable data. It mimics the non-volatile memory of a mobile phone.
- **RAM**: Utilized for executing programs and temporary data storage. It represents the volatile working memory of the device.

#### Memory allocation and access
- **Static memory allocation**: The emulator follows a simple, static allocation model, where the size and location of memory segments are predetermined.
- **Direct and indirect addressing**: The Assembly language supports both direct addressing (accessing memory by specific addresses) and indirect addressing (using registers to point to memory addresses).

#### Data handling
- **Data storage**: Data can be stored in memory as immediate values, binary data, or ASCII characters.
- **Data retrieval**: Instructions can retrieve data from memory for processing and manipulate it as required by the program.

#### Memory operations
- **Load and store instructions**: Specific instructions will be used for loading data from memory into registers (`LOAD`) and storing data from registers back into memory (`STORE`).
- **Memory safety**: Basic memory safety mechanisms will be implemented to prevent unauthorized access and ensure data integrity.

#### Memory mapping
- **Mapping scheme**: A simple mapping scheme will be used to define the relationship between the memory addresses and the corresponding data or instructions.
- **I/O mapping**: Special memory addresses may be reserved for I/O operations, enabling interaction with the virtual hardware components like the display and keypad.

### 4.4 Input and output handling

#### Display output handling
- **Display interface**: Specific instructions to display operations will enable the manipulation of the virtual screen, such as writing text or drawing basic graphics.
- **Output commands**: The Assembly language will include commands like `DISP_WRITE` to output data to the screen. These commands will handle the conversion of data (numeric or character) into a visual representation on the emulator's display.
- **Screen buffering**: A screen buffer will be implemented, where output data is first written to a buffer before being rendered on the screen. This allows for efficient screen updates and control over how and when display changes occur.

#### Keypad input handling
- **Input polling**: The Assembly language will support polling methods to check the state of the keypad. This involves instructions to read the current input state, allowing the program to react to user inputs.
- **Key mapping**: Each key on the virtual keypad will be mapped to a specific value. Assembly programs can use these values to determine which key was pressed and execute corresponding actions.
- **Interrupts for input**: Optionally, the system may support interrupt-driven input, where the program can execute a specific routine in response to a keypress, improving the responsiveness and efficiency of input handling.

#### Combined I/O operations
- **Synchronization**: Mechanisms to synchronize input and output operations will ensure that the display and keypad interactions do not conflict, maintaining a smooth user experience.
- **I/O in program flow**: The Assembly language will enable the integration of I/O operations within the flow of the program, allowing for dynamic and interactive applications that respond to user inputs and provide immediate feedback.

---

## 5. Development tools

### 5.1 Assembler
- **Functionality**: The **[assembler](#assembler)** is responsible for converting Assembly language code into a format that can be executed by the virtual processor. It parses the textual Assembly code and translates it into an internal representation suitable for execution.
- **Error handling**: The assembler will include robust error handling to provide meaningful feedback on syntax and semantic errors in the Assembly code.
- **Support for directives**: In addition to instruction translation, the assembler will handle various directives that aid in the Assembly process, such as data allocation and setting starting points for execution.

### 5.2 Debugger
- **Capabilities**: The **[debugger](#debugger)** will allow users to step through their Assembly code, inspect the contents of registers and memory, and set breakpoints. This tool is vital for understanding program flow and diagnosing issues in Assembly code.
- **User interface**: The debugger will feature a user-friendly interface, displaying key information in an easily understandable format and providing intuitive controls for program execution and inspection.
- **Integration with assembler**: Seamless integration with the assembler ensures that users can quickly identify and fix issues in their code.

### 5.3 Testing framework
- **Automated testing**: The framework will support automated testing of Assembly programs, enabling systematic verification of program functionality against predefined test cases.
- **Performance analysis**: Tools for analyzing the performance of Assembly programs, such as execution time and resource usage, will be included, assisting in optimizing code for efficiency.
- **Extensibility**: The testing framework will be designed to be extensible, allowing additional tests and functionalities to be added as the project evolves.

### 5.4 Code organization
- **Header files (`.h`)**: The prototype and comments of the functions are in the header files. All enumerations and structures/typedefs are also defined in these files. This approach helps in providing a clear interface for each module.
- **Implementation files (`.c`)**: The function definitions (implementations) are in the `.c` files. Comments explaining the implementation details should also be included in these files. This separation of interface and implementation facilitates maintainability and readability of the code.

---

## 6. Testing and validation

While a detailed testing document will be provided separately by the Quality Assurance, this section briefly outlines the general approach to testing and validation for the virtual processor and Assembly language.

### General testing philosophy
- The project adheres to a rigorous testing philosophy to ensure reliability and accuracy in the emulation of old mobile phone functionalities.
- Testing encompasses a range of methods, from unit tests for individual components to integration tests that assess the whole system.

### Coordination with QA
- The development team will closely collaborate with the Quality Assurance team to align testing strategies and ensure comprehensive coverage of all functionalities.
- Feedback from QA testing will be integral to the iterative development process, guiding enhancements and refinements in the emulator and Assembly language.

### Reference to QA document
- For detailed testing procedures, methodologies, and specific test cases, refer to the dedicated [test plan](../QA/test_plan.md) prepared by the Quality Assurance team.

---

## 7. Documentation

### Documentation strategy
- **Comprehensive coverage**: All aspects of the project, from design and development to testing and deployment, will be thoroughly documented. This includes technical specifications, user manuals, and developer guides.
- **Clarity and accessibility**: Documentation will be written in clear, concise language to ensure it is accessible to all team members and stakeholders, regardless of their technical background.

### Types of documentation
- **Technical specifications**: Detailed descriptions of the virtual processor's architecture, the Assembly language's syntax and semantics, and the development tools.
- **User manuals**: Guides for end-users on how to use the virtual processor and write programs in the Assembly language. This will include examples and tutorials.
- **Developer guides**: Instructions and best practices for developers working on the project, covering coding standards, project setup, and contribution guidelines.
- **QA Testing document**: A separate document provided by the Quality Assurance team, detailing testing methodologies, test cases, and results.

### Version control and updates
- **Regular updates**: Documentation will be regularly updated to reflect the latest changes and additions to the project.
- **Version control**: All documentation will be maintained under version control, ensuring that changes are tracked, and historical versions are accessible.

### Collaboration and review
- **Team involvement**: All team members will be encouraged to contribute to and review documentation to ensure accuracy and completeness.
- **Continuous improvement**: Feedback on documentation will be actively sought and used to make continuous improvements, ensuring that the documentation remains relevant and useful.

---

## 8. Appendices

### 8.1 References
1. Meiners, J. "Write your Own Virtual Machine." Tutorial on writing a virtual machine that can run Assembly language programs. Available at: [www.jmeiners.com](https://www.jmeiners.com)
2. "Assembly language." Gentoo Wiki. Overview and resources related to Assembly language programming. Available at: [wiki.gentoo.org](https://wiki.gentoo.org/wiki/Assembly_language)
3. "How to create your own virtual machine." CodeProject. Tutorial on creating an emulator targeting a specific computer. Available at: [www.codeproject.com](https://www.codeproject.com)
4. Streanga, L. "Assembler Project." GitHub repository. An Assembler for converting Assembly language for a virtual processor into machine code. Available at: [github.com/lucas-streanga/Assembler-Project](https://github.com/lucas-streanga/Assembler-Project)
5. "Introduction to Assembly language." Baeldung on Computer Science. A guide covering the basics of Assembly language. Available at: [www.baeldung.com](https://www.baeldung.com/cs/Assembly-language-intro)
6. "Virtualization for Cost-Effective Teaching of Assembly language Programming." IEEE Xplore. Discusses a virtual system that emulates an ARM-based processor machine for teaching Assembly language. Available at: [ieeexplore.ieee.org](https://ieeexplore.ieee.org/document/5619589)

## 8.2 Glossary

| Term            | Definition | Use in project |
|-----------------|------------|----------------|
| <a id="assembler"></a>**Assembler**   | A tool that converts Assembly language code into a **[machine code](#machine-code)** or an executable format. | Used to translate written Assembly code into a format that the virtual processor can execute. |
| <a id="Assembly-language"></a>**Assembly language** | A low-level programming language used to write instructions that a processor can understand directly. | The primary language used for programming the virtual processor. |
| <a id="binary"></a>**Binary**      | A base-2 numerical system used in digital electronics and computing. | Fundamental representation of data in the virtual processor. |
| <a id="bitwise-operation"></a>**Bitwise operation** | An operation that directly manipulates bits. | Used in Assembly language for low-level data manipulation. |
| <a id="debugger"></a>**Debugger**    | A tool used to test and debug programs. | Utilized for identifying and resolving issues in Assembly code. |
| <a id="emulator"></a>**Emulator**    | Software that enables one computer system to behave like another computer system. | Core of the project, emulating old mobile phone hardware. |
| <a id="hexadecimal"></a>**Hexadecimal** | A base-16 number system used in computing. | Used for representing binary data in a more readable format in Assembly code. |
| <a id="instruction-set"></a>**Instruction set** | The collection of instructions that a processor can execute. | Defines the capabilities of the virtual processor. |
| <a id="machine-code"></a>**Machine code** | The lowest-level programming language, consisting of binary code. | The end product of the assembler, run by the virtual processor. |
| <a id="memory-addressing1"></a>**Memory addressing** | The method by which a processor can access data stored in memory. | Essential for the emulator's handling of memory operations. |
| <a id="opcode"></a>**Opcode**      | The part of a machine language instruction that specifies the operation. | Used in defining the functionality of Assembly instructions. |
| <a id="operand"></a>**Operand**     | The part of a computer instruction that specifies what data is to be operated on. | Used in Assembly instructions for specifying data or memory locations. |
| <a id="processor"></a>**Processor**   | The component that performs the instructions of a computer program. | The virtual processor is the central component of the emulator. |
| <a id="ram"></a>**RAM (Random Access Memory)** | Memory that can be accessed randomly, used for storing working data and machine code. | Simulated in the emulator for temporary data storage during program execution. |
| <a id="register"></a>**Register**    | A small, quickly accessible storage location in a processor. | Used in the virtual processor for holding temporary data and intermediate computation results. |
| <a id="rom"></a>**ROM (Read-Only Memory)** | Non-volatile memory used in computers and other devices. | Emulated to store the firmware and immutable data of the virtual mobile phone. |
| <a id="syntax"></a>**Syntax**      | The rules defining the structure of correctly formatted programs in a language. | Governs how Assembly language code is written for the emulator. |
| <a id="virtual-processor"></a>**Virtual processor** | A software-based emulation of a processor. | Executes Assembly language programs as if running on an actual old mobile phone processor. |

---
