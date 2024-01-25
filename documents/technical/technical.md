### Technical Specifications Document
### ALGOSUP Project 3, 2024

# Virtual Processor and Assembly Language for Old Mobile Phone Emulation

### Version: 0.2
### Date: 01/25/2024

---

## Table of Contents
1. [Introduction](#1-introduction)
2. [Project Overview](#2-project-overview)
3. [Hardware Specifications](#3-hardware-specifications)
   1. [Virtual Processor](#31-virtual-processor)
   2. [Memory](#32-memory)
   3. [Display](#33-display)
   4. [Keypad Input](#34-keypad-input)
   5. [Sound and Audio](#35-sound-and-audio)
   6. [Power Management](#36-power-management)
4. [Assembly Language Specifications](#4-assembly-language-specifications)
   1. [Instruction Set](#41-instruction-set)
   2. [Syntax and Conventions](#42-syntax-and-conventions)
   3. [Memory Management](#43-memory-management)
   4. [Input and Output Handling](#44-input-and-output-handling)
5. [Development Tools](#5-development-tools)
   1. [Assembler](#51-assembler)
   2. [Debugger](#52-debugger)
   3. [Testing Framework](#53-testing-framework)
   4. [Code Organization](#54-code-organization)
6. [Testing and Validation](#6-testing-and-validation)
   1. [Unit Testing](#61-unit-testing)
   2. [Integration Testing](#62-integration-testing)
   3. [Performance Testing](#63-performance-testing)
7. [Documentation](#7-documentation)
8. [Appendices](#8-appendices)
   1. [References](#81-references)
   2. [Glossary](#82-glossary)

---

## 1. Introduction

This project involves developing a virtual processor and a custom assembly language to emulate the typical environment of old mobile phones. It aims to create a virtualized system that accurately simulates the functionalities of these devices, focusing on general characteristics common to this category.

---

## 2. Project Overview

The project's scope encompasses the creation of a generalized old mobile phone emulator, using a virtual processor with custom specifications, not limited to any specific existing hardware like the ARM7TDMI. The Nokia 3310 is used as a reference point for typical features and functionalities found in old mobile phones.

---

## 3. Hardware Specifications

### 3.1 Virtual Processor

#### Processor Specifications
- Custom-designed processor specifications, tailored to emulate common functionalities of old mobile phones.
- The processor will be inspired by typical characteristics of old mobile phone processors.

#### Processor Capabilities
- Capabilities include basic arithmetic operations, input/output operations, and interaction with emulated components.

### 3.2 Memory
- Memory architecture details, including ROM and RAM specifications for the emulator.

### 3.3 Display
- Emulating a basic monochrome LCD typical of old mobile phones, with text and simple graphics capabilities.

### 3.4 Keypad Input
- Simulating keypad input, including numeric and function keys typical of old mobile phones.

### 3.5 Sound and Audio
- Emulating audio functions such as monophonic ringtones and beeps.

### 3.6 Power Management
- The emulator will show a static battery level, either consistently at 100% or mirroring the host computer's battery status.

---

## 4. Assembly language specifications

### 4.1 Instruction set
- **Arithmetic and Bitwise Operations**:
  - `OP_ADD`: Addition operation. Adds values of two registers or a register and an immediate value.
  - `OP_SUB`: Subtraction operation. Subtracts the second operand from the first.
  - `OP_DIV`: Division operation. Divides the first operand by the second.
  - `OP_MUL`: Multiplication operation. Multiplies two operands.
  - `OP_MOD`: Modulus operation. Computes the remainder of division of two operands.
  - `OP_R_SHIFT`: Right shift operation. Shifts bits of the operand to the right.
  - `OP_L_SHIFT`: Left shift operation. Shifts bits of the operand to the left.
  - `OP_B_OR`: Bitwise OR operation. Performs bitwise OR on two operands.
  - `OP_B_AND`: Bitwise AND operation. Performs bitwise AND on two operands.
  - `OP_B_NOT`: Bitwise NOT operation. Inverts the bits of the operand.
  - `OP_B_XOR`: Bitwise XOR operation. Performs bitwise exclusive OR on two operands.

#### Comparison Types (`cmpKind`)
- **Logical Operations for Conditional Processing**:
  - `CMP_OR`: Logical OR comparison. Evaluates to true if either of the operands is true.
  - `CMP_AND`: Logical AND comparison. Evaluates to true only if both operands are true.
  - `CMP_NOT`: Logical NOT comparison. Inverts the truth value of the operand.
  - `CMP_XOR`: Logical XOR comparison. Evaluates to true if operands are different.

#### Action Types (`actionKind`)
- **Control Flow Instructions**:
  - `ACT_IF`: Conditional execution. Executes the following block if the condition is true.
  - `ACT_ELSE`: Else block for a conditional. Executes if the `ACT_IF` condition is false.
  - `ACT_LOOP`: Begins a loop structure. Continues execution until a condition is met.
  - `ACT_END`: Marks the end of a control flow block, like the end of an if-else or loop.
  - `ACT_MOV`: Move operation. Transfers data from one register to another or to/from memory.
  - `ACT_JMP`: Unconditional jump. Alters the flow of execution to a new address.
  - `ACT_CALL`: Calls a subroutine. Jumps to subroutine address and maintains return address.
  - `ACT_RET`: Return from subroutine. Returns control to the calling function.
  - `ACT_GET_CLK`: Retrieves the current value of the system clock or timer.

#### Instruction Types (`instKind`)
- **Categorization of Assembly Instructions**:
  - `INST_OP`: Denotes an operation instruction, performing arithmetic or bitwise computation.
  - `INST_CMP`: Represents a comparison instruction, used in conditional statements.
  - `INST_ACT`: Action instruction that influences the control flow or performs a specific task.
  - `INST_LABEL`: A label instruction, used as a marker or target for jumps and calls.

#### Register Types (`regKind`)
- **Register Enumeration for the Virtual Processor**:
  - `RG_0`, `RG_1`, ..., `RG_7`: Enumeration of registers available in the virtual processor. These registers are used for storing temporary data, performing operations, and maintaining state within the processor.


### 4.2 Syntax and Conventions

The syntax and conventions of the assembly language are designed to be intuitive and aligned with standard practices in assembly language programming. This section outlines the fundamental syntax rules for instructions, registers, memory addressing, and data types.

#### Instruction Syntax
- **Format**: Instructions generally follow the format of `INSTRUCTION <operands>`. Operands can be registers, immediate values, or memory addresses.
- **Example**: `OP_ADD RG_0, RG_1` - This instruction adds the contents of `RG_1` to `RG_0`.

#### Register Syntax
- **Usage**: Registers are referred to by their names, such as `RG_0`, `RG_1`, etc.
- **Context**: Used as operands in instructions for operations like data movement, arithmetic operations, etc.

#### Memory Addressing
- **Direct Addressing**: Accesses the memory directly using an address. For example, `[address]` where `address` is a memory location.
- **Indirect Addressing**: Uses a register to point to a memory address. For example, `[RG_0]` would access the memory location pointed to by `RG_0`.

#### Data Types
- **Immediate Values**: Constants or literals directly used in instructions. For example, `OP_ADD RG_0, 5` adds the value `5` to the contents of `RG_0`.
- **Binary and Hexadecimal Support**: The language supports both binary (`0b0101`) and hexadecimal (`0x1A`) literals for ease of low-level programming.

#### Conventions
- **Case Sensitivity**: The language is case-sensitive. All instructions and register names must be used in the correct case.
- **Whitespace**: Whitespace is used to separate the elements of an instruction but is otherwise not significant.
- **Comments**: Comments start with a semicolon (`;`) and continue to the end of the line. For example, `OP_ADD RG_0, RG_1 ; Add RG_1 to RG_0`.

### 4.3 Memory management

#### Memory Architecture
- **Memory Types**: The virtual processor will simulate a basic memory architecture comprising both ROM (Read-Only Memory) and RAM (Random Access Memory).
- **ROM**: Used to store the emulator's firmware and immutable data. It mimics the non-volatile memory of a mobile phone.
- **RAM**: Utilized for executing programs and temporary data storage. It represents the volatile working memory of the device.

#### Memory Allocation and Access
- **Static Memory Allocation**: The emulator follows a simple, static allocation model, where the size and location of memory segments are predetermined.
- **Direct and Indirect Addressing**: The assembly language supports both direct addressing (accessing memory by specific addresses) and indirect addressing (using registers to point to memory addresses).

#### Data Handling
- **Data Storage**: Data can be stored in memory as immediate values, binary data, or ASCII characters.
- **Data Retrieval**: Instructions can retrieve data from memory for processing and manipulate it as required by the program.

#### Memory Operations
- **Load and Store Instructions**: Specific instructions will be used for loading data from memory into registers (`LOAD`) and storing data from registers back into memory (`STORE`).
- **Memory Safety**: Basic memory safety mechanisms will be implemented to prevent unauthorized access and ensure data integrity.

#### Memory Mapping
- **Mapping Scheme**: A simple mapping scheme will be used to define the relationship between the memory addresses and the corresponding data or instructions.
- **I/O Mapping**: Special memory addresses may be reserved for I/O operations, enabling interaction with the virtual hardware components like the display and keypad.

### 4.4 Input and Output Handling

#### Display Output Handling
- **Display Interface**: Instructions specific to display operations will enable the manipulation of the virtual screen, such as writing text or drawing basic graphics.
- **Output Commands**: The assembly language will include commands like `DISP_WRITE` to output data to the screen. These commands will handle the conversion of data (numeric or character) into a visual representation on the emulator's display.
- **Screen Buffering**: A screen buffer will be implemented, where output data is first written to a buffer before being rendered on the screen. This allows for efficient screen updates and control over how and when display changes occur.

#### Keypad Input Handling
- **Input Polling**: The assembly language will support polling methods to check the state of the keypad. This involves instructions to read the current input state, allowing the program to react to user inputs.
- **Key Mapping**: Each key on the virtual keypad will be mapped to a specific value. Assembly programs can use these values to determine which key was pressed and execute corresponding actions.
- **Interrupts for Input**: Optionally, the system may support interrupt-driven input, where the program can execute a specific routine in response to a keypress, improving the responsiveness and efficiency of input handling.

#### Combined I/O Operations
- **Synchronization**: Mechanisms to synchronize input and output operations will ensure that the display and keypad interactions do not conflict, maintaining a smooth user experience.
- **I/O in Program Flow**: The assembly language will enable the integration of I/O operations within the flow of the program, allowing for dynamic and interactive applications that respond to user inputs and provide immediate feedback.

---

## 5. Development Tools

### 5.1 Assembler
- **Functionality**: The assembler is responsible for converting assembly language code into a format that can be executed by the virtual processor. It parses the textual assembly code and translates it into an internal representation suitable for execution.
- **Error Handling**: The assembler will include robust error handling to provide meaningful feedback on syntax and semantic errors in the assembly code.
- **Support for Directives**: In addition to instruction translation, the assembler will handle various directives that aid in the assembly process, such as data allocation and setting starting points for execution.

### 5.2 Debugger
- **Capabilities**: The debugger will allow users to step through their assembly code, inspect the contents of registers and memory, and set breakpoints. This tool is vital for understanding program flow and diagnosing issues in assembly code.
- **User Interface**: The debugger will feature a user-friendly interface, displaying key information in an easily understandable format and providing intuitive controls for program execution and inspection.
- **Integration with Assembler**: Seamless integration with the assembler ensures that users can quickly identify and fix issues in their code.

### 5.3 Testing Framework
- **Automated Testing**: The framework will support automated testing of assembly programs, enabling systematic verification of program functionality against predefined test cases.
- **Performance Analysis**: Tools for analyzing the performance of assembly programs, such as execution time and resource usage, will be included, assisting in optimizing code for efficiency.
- **Extensibility**: The testing framework will be designed to be extensible, allowing additional tests and functionalities to be added as the project evolves.

### 5.4 Code Organization
- **Header Files (`.h`)**: The prototype and comments of the functions are in the header files. All enumerations and structures/typedefs are also defined in these files. This approach aids in providing a clear interface for each module.
- **Implementation Files (`.c`)**: The function definitions (implementations) are in the `.c` files. Comments explaining the implementation details should also be included in these files. This separation of interface and implementation facilitates maintainability and readability of the code.

---

## 6. Testing and Validation

While a detailed testing document will be provided separately by the Quality Assurance, this section briefly outlines the general approach to testing and validation for the virtual processor and assembly language.

### General Testing Philosophy
- The project adheres to a rigorous testing philosophy to ensure reliability and accuracy in the emulation of old mobile phone functionalities.
- Testing encompasses a range of methods, from unit tests for individual components to integration tests that assess the system as a whole.

### Coordination with QA
- The development team will closely collaborate with the Quality Assurance team to align testing strategies and ensure comprehensive coverage of all functionalities.
- Feedback from QA testing will be integral to the iterative development process, guiding enhancements and refinements in the emulator and assembly language.

### Reference to QA Document
- For detailed testing procedures, methodologies, and specific test cases, refer to the dedicated testing document prepared by the Quality Assurance team.

---

## 7. Documentation

### Documentation Strategy
- **Comprehensive Coverage**: All aspects of the project, from design and development to testing and deployment, will be thoroughly documented. This includes technical specifications, user manuals, and developer guides.
- **Clarity and Accessibility**: Documentation will be written in clear, concise language to ensure it is accessible to all team members and stakeholders, regardless of their technical background.

### Types of Documentation
- **Technical Specifications**: Detailed descriptions of the virtual processor's architecture, the assembly language's syntax and semantics, and the development tools.
- **User Manuals**: Guides for end-users on how to use the virtual processor and write programs in the assembly language. This will include examples and tutorials.
- **Developer Guides**: Instructions and best practices for developers working on the project, covering coding standards, project setup, and contribution guidelines.
- **QA Testing Document**: A separate document provided by the Quality Assurance team, detailing testing methodologies, test cases, and results.

### Version Control and Updates
- **Regular Updates**: Documentation will be regularly updated to reflect the latest changes and additions to the project.
- **Version Control**: All documentation will be maintained under version control, ensuring that changes are tracked, and historical versions are accessible.

### Collaboration and Review
- **Team Involvement**: All team members will be encouraged to contribute to and review documentation to ensure accuracy and completeness.
- **Continuous Improvement**: Feedback on documentation will be actively sought and used to make continuous improvements, ensuring that the documentation remains relevant and useful.

---

## 8. Appendices

### 8.1 References
1. Meiners, J. "Write your Own Virtual Machine." Tutorial on writing a virtual machine that can run assembly language programs. Available at: [www.jmeiners.com](https://www.jmeiners.com)
2. "Assembly Language." Gentoo Wiki. Overview and resources related to assembly language programming. Available at: [wiki.gentoo.org](https://wiki.gentoo.org/wiki/Assembly_language)
3. "How to create your own virtual machine." CodeProject. Tutorial on creating an emulator targeting a specific computer. Available at: [www.codeproject.com](https://www.codeproject.com)
4. Streanga, L. "Assembler Project." GitHub repository. An Assembler for converting assembly language for a virtual processor into machine code. Available at: [github.com/lucas-streanga/Assembler-Project](https://github.com/lucas-streanga/Assembler-Project)
5. "Introduction to Assembly Language." Baeldung on Computer Science. A guide covering the basics of assembly language. Available at: [www.baeldung.com](https://www.baeldung.com/cs/assembly-language-intro)
6. "Virtualization for Cost-Effective Teaching of Assembly Language Programming." IEEE Xplore. Discusses a virtual system that emulates an ARM-based processor machine for teaching assembly language. Available at: [ieeexplore.ieee.org](https://ieeexplore.ieee.org/document/5619589)

## 8.2 Glossary

| Term            | Definition | Use in Project |
|-----------------|------------|----------------|
| **Assembler**   | A tool that converts assembly language code into a machine code or an executable format. | Used to translate written assembly code into a format that the virtual processor can execute. |
| **Assembly Language** | A low-level programming language used to write instructions that a processor can understand directly. | The primary language used for programming the virtual processor. |
| **Binary**      | A base-2 numerical system used in digital electronics and computing. | Fundamental representation of data in the virtual processor. |
| **Bitwise Operation** | An operation that directly manipulates bits. | Used in assembly language for low-level data manipulation. |
| **Debugger**    | A tool used to test and debug programs. | Utilized for identifying and resolving issues in assembly code. |
| **Emulator**    | Software that enables one computer system to behave like another computer system. | Core of the project, emulating old mobile phone hardware. |
| **Hexadecimal** | A base-16 number system used in computing. | Used for representing binary data in a more readable format in assembly code. |
| **Instruction Set** | The collection of instructions that a processor can execute. | Defines the capabilities of the virtual processor. |
| **Machine Code** | The lowest-level programming language, consisting of binary code. | The end product of the assembler, run by the virtual processor. |
| **Memory Addressing** | The method by which a processor can access data stored in memory. | Essential for the emulator's handling of memory operations. |
| **Opcode**      | The part of a machine language instruction that specifies the operation. | Used in defining the functionality of assembly instructions. |
| **Operand**     | The part of a computer instruction that specifies what data is to be operated on. | Used in assembly instructions for specifying data or memory locations. |
| **Processor**   | The component that performs the instructions of a computer program. | The virtual processor is the central component of the emulator. |
| **RAM (Random Access Memory)** | Memory that can be accessed randomly, used for storing working data and machine code. | Simulated in the emulator for temporary data storage during program execution. |
| **Register**    | A small, quickly accessible storage location in a processor. | Used in the virtual processor for holding temporary data and intermediate computation results. |
| **ROM (Read-Only Memory)** | Non-volatile memory used in computers and other devices. | Emulated to store the firmware and immutable data of the virtual mobile phone. |
| **Syntax**      | The rules defining the structure of correctly formatted programs in a language. | Governs how assembly language code is written for the emulator. |
| **Virtual Processor** | A software-based emulation of a processor. | Executes assembly language programs as if running on an actual old mobile phone processor. |

This glossary provides definitions of key terms and their specific applications within the project, enhancing understanding and relevance to the virtual processor development.

---
