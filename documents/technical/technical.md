<!-- TODO:
- Changing the way I'm linking the definition for the glossary, removing the part "use" in it
- Complete the parts:
   - File architecture
   - Development environment
   - Adding a convention part with all the conventions used for the project (commits, etc...). Use technical of team 3 as a model
- Define C standard libraries in the glossary-->

### Technical Specifications Document
### ALGOSUP Project 3, 2024

# Virtual processor and interpreter for Assembly
| | |
| ----- | ----- |
| Author | Guillaume Deramchi |
| Team | 2 |
| Reviewers | Enzo Guillouche(QA), Mathias Gagnepain(PM), Paul Nowak and Maxime Caron(both SEs) |
| Created on | 01/22/2024 |
| Last updated | 01/26/2024 |

---

<details>
<summary>Table of contents</summary>

1. [Introduction](#1-introduction)
   1. [Project goal]()
   2. [Document purpose]()
   1. [File architecture](#11-file-architecture)
   2. [Target audience](#12-target-audience)
   3. [Development environment](#13-development-environment))
   4. [Functional and technical requirements](#14-functional-and-technical-requirements)
   5. [Constraints](#15-constraints)
   6. [Out of scope](#16-out-of-scope)
   7. [Algorithm architecture](#17-algorithm-architecture)
2. [Project overview](#2-project-overview)
3. [Technical specifications]()
   1. [Virtual processor](#31-virtual-processor)
   4. [Interpreter](#44-interpreter)
4. [AT2 language specifications](#4-at2-language-specifications)
   1. [Instruction set](#41-instruction-set)
   2. [Syntax and conventions](#42-syntax-and-conventions)
   <!--3. [Input and output handling](#43-input-and-output-handling)-->
   4. [Interpreter](#44-interpreter)
5. [Development tools](#5-development-tools)
   1. [Assembler](#51-assembler)
   2. [Debugger](#52-debugger)
   3. [Testing framework](#53-testing-framework)
   4. [Code organization](#54-code-organization)
6. [Testing and validation](#6-testing-and-validation)
   1. [Unit testing](#61-unit-testing)
   2. [Integration testing](#62-integration-testing)
   3. [Performance testing](#63-performance-testing)
7. [Risks and challenges](#7-risks-and-challenges)
   1. [Risks](#71-risks)
   2. [Challenges](#72-challenges)
8. [Documentation](#8-documentation)
9. [Appendices](#9-appendices)
   1. [References](#91-references)
   2. [Glossary](#92-glossary)
</details>

---

## 1. Introduction

### 1.1 Project goal

The goal of this project is to create an **[interpreter](#interpreter)** to run a new **[Assembly language](#Assembly-language)** on its **[virtual processor](#virtual-processor)** that we created on our own, whether from scratch or by inspiring of already existing Assembly. We chose to focus the development of the project on small and limited 16 bits processor. 

### 1.2 Document purpose

The methodology outlined in the document will provide valuable insights to other stakeholders and project owners, benefiting them greatly. Additionally, it can serve as a reliable point of reference for future maintenance purposes.

#### 1.2.1 Target audience

**This document is meant mainly for:**

- Software engineers - to help them understand the technical as well as the client requirements and to provide direction for planning and decision-making. Assist them in understanding the risk and difficulties, customer demands, extra technical specifications, and decisions taken.

- Program manager - to verify against client expectations and the functional specification.

- Quality assurance - to help with test plan preparation and to validate issues with it.

- Project manager - to assist in determining dependencies and hazards.

### 1.3 File architecture

``` folder
|-- 2023-2024-project-3-virtual-processor-team-2 (root)
|   |-- documents
|   |   |-- functional
|   |   |   |-- 2023-2024 Project 3 Virtual Processor.pdf
|   |   |   |-- AT2-Assembly-Language-Documentation.md
|   |   |   |-- Functional Specification Document Template.md
|   |   |-- management
|   |   |   |-- weekly_reports
|   |   |   |   |-- cumulative.md
|   |   |   |   |-- week_1.md
|   |   |   |   |-- week_2.md
|   |   |   |   |-- week_3.md
|   |   |   |   |-- week_4.md
|   |   |   |   |-- week_5.md
|   |   |   |   |-- week_6.md
|   |   |   |   |-- week_7.md
|   |   |   |   |-- week_8.md
|   |   |   |   |-- management_artifact.md
|   |   |-- qa
|   |   |   |-- test_plan.md
|   |   |-- technical
|   |   |   |-- roadmap.md
|   |   |   |--technical.md
```

### 1.4 Development environment

**TODO**

### 1.5 Functional and technical requirements

#### Functional requirements

- **Programmer efficiency**: Easy-to-understand syntax for efficient Assembly programming.
- **Educational value**: Clarity in demonstrating low-level programming and processor architecture interaction.
- **Emulator accuracy**: Realistic emulation of a 16-bit processor for testing and debugging.
- **Error handling**: Clear, informative error messages from the assembler and emulator for quick issue resolution.

The complete functional specifications document here: [functional specification](../functional/Functional%20Specification%20Document%20Template.md)

#### Technical requirements

- **Architecture**: Emulates a 16-bit processor environment, including registers, memory, and basic I/O.
- **Development**: Written in C, using standard libraries for compatibility and efficiency.
- **Documentation**: Comprehensive and exhaustive guides for both users and developers.
- **Testing**: Comprehensive unit and integration testing for ensuring system integrity.

### 1.6 Project constraints

- We can only use C standard libraries for the project
- It has to be plain and portable C

### 1.7 Out of scope

- The product does not require to have an advanced UI.
- The product has no purpose to be an assembler to return binary files. 

---

## 2. Project overview

The project's scope includes the creation of a small and limited 16 bits virtual processor and its interpreter with new specifications. We inspired from old devices with small and limited processor for typical features and functionalities.


We chose the C99 version of C language to develop our virtual processor. We chose it for its modern features that enhance code readability and maintainability, its support for performance optimization through inline functions, and its widespread platform compatibility, ensuring our virtual processor and interpreter development is efficient and broadly applicable.

---

## 3. Virtual processor specifications 

### 3.1 Virtual processor

#### Processor details 
- 16-bit processor
- 8 registers (including 1 dedicated to the clock)

#### Processor capabilities
- Basic arithmetic operations
- Input/output operations

#### Processor runner
- Runner for a **[processor](#processor)**, with common functionalities of small and limited 16 bits processor.

### 4.4 Interpreter

#### Interpreter functions
![Alt text](../images/technical_images/archi_interpreter_diagram.jpg)

- **Parser** <br>The parser is the first part of the interpreter: 
   - Reads input files.
   - Analyses the instructions.
   - Put the instructions in an algorithmic structure.
- **Builder**<br>The builder is the second part of the interpreter:
   - Reads the algorithmic structure.
   - Replaces some parts to make them readable for the Virtual processor.
- **Virtual processor**<br>The last part of the interpreter:
   - Executes the program regarding the algorithmic structure.

# WE LAST STOPPED HERE 

- **Execution flow control**: It manages the flow of execution based on control instructions like loops, conditional statements, and jumps.
- **Error handling**: Includes robust error detection and reporting mechanisms to handle syntax and logical errors in the AT2 code.

#### Integration with virtual processor
- **Execution**: The interpreter works closely with the virtual processor to ensure smooth execution of AT2 programs, simulating a real processor's behavior.
- **Resource management**: It efficiently manages the processor's resources, such as memory and registers, during the execution of AT2 code.

#### User interaction
- **Interactive mode**: The interpreter allows for users to enter and execute AT2 instructions one at a time, which is beneficial for learning and debugging.

---

## 4. AT2 language specifications
Our new Assembly language will be named AT2 (Assembly Team 2). Its extension will be .aop (Assembly Operation Processor). 

### 4.1 **[Instruction set](#instruction-set)**
- **Arithmetic and [bitwise operations](#bitwise-operation)**:
  - `add`, `+`: Addition operation. Adds values of two **[registers](#register)** or a register and an immediate value.
  - `sub`, `-`: Subtraction operation. Subtracts the second **[operand](#operand)** from the first.
  - `div`, `/`: Division operation. Divides the first operand by the second.
  - `mul`, `*`: Multiplication operation. Multiplies two operands.
  - `mod`, `%`: Modulus operation. Computes the remainder of division of two operands.
  - `shr`, `>>`: Right shift operation. Shifts bits of the operand to the right.
  - `shl`, `<<`: Left shift operation. Shifts bits of the operand to the left.
  - `or`, `|`: Bitwise OR operation. Performs bitwise OR on two operands.
  - `and`, `&`: Bitwise AND operation. Performs bitwise AND on two operands.
  - `not`, `!`: Bitwise NOT operation. Inverts the bits of the operand.
  - `xor`, `^`: Bitwise XOR operation. Performs bitwise exclusive OR on two operands.

#### Comparison types (`cmpKind`)
- **Logical operations for conditional processing**:
  - `or`, `||`: Logical OR comparison. Evaluates to true if either of the operands is true.
  - `and`, `&&`: Logical AND comparison. Evaluates to true only if both operands are true.
  - `not`, `!`: Logical NOT comparison. Inverts the truth value of the operand.
  - `xor`, `^`: Logical XOR comparison. Evaluates to true if operands are different.

#### Action types (`actionKind`)
- **Control flow instructions**:
  - `if`: Conditional execution. Executes the AT2 language following block if the condition is true.
  - `else`: Else block for a conditional. Executes if the `if` condition is false.
  - `loop`: Begins a loop structure. Continues execution until a condition is met.
  - `exit`: Marks the end of a control flow block, like the end of an if-else or loop.
  - `mov`: Move operation. Transfers data from one register to another or to/from memory.
  - `jmp`, `goto`: Unconditional jump. Alters the flow of execution to a new address.
  - `call`: Calls a subroutine. Jumps to subroutine address and maintains return address.
  - `ret`: Return from subroutine. Returns control to the calling function.
  - `clk`: Retrieves the current value of the system clock.

#### Register types (`regKind`)
- **Register enumeration for the virtual processor**:
  - `rg0`, `rg1`, ..., `rg6`: Enumeration of registers available in the virtual processor. These registers are used for storing temporary data, performing operations, and maintaining state within the processor.  
  - `rg7`: Dedicated for the clock.

#### Variables declarations
  - `var name, value` will be the convention for a variable declaration.
#### Function declaration
  - `lab name` will be the convention for a function declaration.
#### File inclusion
  - `get "filename.aop"` will be the convention for a file inclusion.


### 4.2 Syntax and conventions

The **[syntax](#syntax)** and conventions of the AT2 language are designed to be intuitive and aligned with standard practices in Assembly language programming. This section outlines the fundamental syntax rules for instructions, registers, **[memory addressing](#memory-addressing1)**, and data types.

#### Instruction syntax
- **Format**: Instructions generally follow the format of `instruction arg0, arg1`. Operands can be registers, immediate values, or memory addresses.
- **Example**: `+ rg0, rg1` - This instruction adds the content of `rg1` to `rg0`.

#### Register syntax
- **Usage**: Registers are referred to by their names, such as `rg0`, `rg1`, etc.
- **Context**: Used as operands in instructions for operations like data movement, arithmetic operations, etc.

#### Data types
- **Immediate values**: Constants or literals directly used in instructions. For example, `+ rg0, 5` adds the value `5` to the content of `rg0`.
- **Binary and hexadecimal support**: The language supports both **[binary](#binary)** and **[hexadecimal](#hexadecimal)**  literals for ease of low-level programming. However, you need to specify the type of your literal. For instance, `0b` for binary and `0x` for hexadecimal at the beginning.
- **Strings**: Strings should be defined with double quotes: `"string"`.
- **Characters**: Characters should be defined with simple quotes: `'q'`.

#### Conventions
- **Case sensitivity**: All instructions and register names must be used in the correct case:
   - Each functions name will be written in snake_case.

   - Variable names will be written in camelCase.

   - All variable will be written at the same place.

   - All #define will be written in SNAKE_CASE and in uppercase.

   - All #define will be written at the same place.
- **Whitespace**: Whitespace is used to separate the elements of an instruction but is otherwise not significant.
- **Comments**: Comments start with `//` for one-line comments, the same comments convention as C language. For example: `// This is a comment`

---

## 5. Development tools

<!-- NOT SURE ABOUT THE FACT THAT ITS ASSEMBLER AND NOT INTERPRETER, NEED TO CHECK IT BY MAXIME CARON-->
### 5.1 Assembler
- **Functionality**: The **[assembler](#assembler)** is responsible for converting AT2 code into a format that can be executed by the virtual processor. It parses the textual AT2 code and translates it into an internal representation suitable for execution.
- **Error handling**: The assembler will include robust error handling to provide meaningful feedback on syntax and semantic errors in the AT2 code.
- **Support for directives**: In addition to instruction translation, the assembler will handle various directives that help in the AT2 process, such as data allocation and setting starting points for execution.

### 5.2 Debugger
- **Capabilities**: The **[debugger](#debugger)** will allow users to step through their code, inspect the contents of registers and memory, and set breakpoints.
- **User interface**: The debugger will have a user-friendly interface, displaying understandable information.
- **Integration with assembler**: A good integration with the assembler ensures that users can quickly identify and fix issues in their code.

### 5.3 Testing framework
- **Automated testing**: The framework will support automated testing of AT2 programs, enabling systematic verification of program functionality against predefined test cases.
- **Performance analysis**: Tools for analyzing the performance of AT2 programs, such as execution time and resource usage, will be included, assisting in optimizing code for efficiency.
- **Extensibility**: The testing framework will be designed to be extensible, allowing additional tests and functionalities to be added as the project evolves.

### 5.4 Code organization
- **Header files (`.h`)**: The prototype and comments of the functions are in the header files. All enumerations and structures/typedefs are also defined in these files. This approach helps in providing a clear interface for each module.
- **Implementation files (`.c`)**: The function definitions (implementations) are in the `.c` files. Comments explaining the implementation details should also be included in these files. This separation of interface and implementation facilitates maintainability and readability of the code.

---

## 6. Testing and validation

While a detailed testing document will be provided separately by the Quality Assurance, this section briefly outlines the general approach to testing and validation for the virtual processor and AT2 language.

### General testing philosophy
- The project adheres to a rigorous testing philosophy to ensure reliability and accuracy for our virtual processor.
- Testing encompasses a range of methods, from unit tests for individual components to integration tests that assess the whole system.

### Coordination with QA
- The development team will closely collaborate with the Quality Assurance team to align testing strategies and ensure complete coverage of all functionalities.
- Feedback from QA testing will be integral to the iterative development process, guiding enhancements and refinements in the virtual processor and AT2 language.

### Reference to QA document
- For detailed testing procedures, methodologies, and specific test cases, refer to the dedicated [test plan](../QA/test_plan.md) prepared by the Quality Assurance.

---

## 7. Risks and challenges

### 7.1 Risks 
- Risk: Developing an accurate and efficient interpreter for a custom assembly language is technically complex. There's a risk of underestimating the development time and resources needed.

- Mitigation: Allocate sufficient time for research and development. Conduct regular reviews and assessments to adjust timelines and resources as needed.
---
- Risk: The interpreter might not perform optimally, leading to slow execution of assembly code, which can frustrate users.

- Mitigation: Focus on performance optimization from the start. Benchmark regularly and optimize critical parts of the code.
---
- Risk: The interpreter may face compatibility issues on different operating systems or hardware configurations.

- Mitigation: Test the interpreter across multiple platforms early and regularly. Use portable libraries and follow standard programming practices.
---
- Risk: Difficulty in gaining traction and adoption among the target user base, potentially due to a steep learning curve or lack of awareness.

- Mitigation: Develop comprehensive documentation and tutorials. Engage with the community through forums, social media, and workshops.
---
- Risk: There's a possibility of misinterpretation or bugs in how assembly instructions are processed, leading to incorrect program behavior.

- Mitigation: Implement extensive testing, including unit tests, integration tests, and user testing, to catch and fix bugs early.
---
- Risk: Inadequate documentation and learning resources can hinder user understanding and adoption.

- Mitigation: Invest in creating detailed, user-friendly documentation and interactive learning materials. Update these resources regularly.
---
- Risk: The interpreter may not be scalable or flexible enough to accommodate future enhancements or changes in technology.

- Mitigation: Design the interpreter with scalability in mind. Use modular architecture to facilitate future enhancements.
---
- Risk: Potential security vulnerabilities in the interpreter could lead to exploitation, especially if it becomes widely used.

- Mitigation: Conduct regular security audits and incorporate security best practices in the development process.
---
- Risk: Mismanagement of resources or poor project management could lead to project delays or failure.

- Mitigation: Use effective project management tools and methodologies. Ensure clear communication and responsibilities within the project team.

### 7.2 Challenges
- Creating a comprehensive and functional 16-bit processor architecture from scratch, balancing simplicity with the need for essential features.

- Ensuring the virtual processor accurately simulates the behavior of a typical 16-bit processor, including handling of memory, arithmetic operations, and control flows.

- Defining an intuitive yet powerful AT2 language suited for a 16-bit processor, considering the limited address space and data width.

- Ensuring the interpreter executes the AT2 code efficiently, a challenge given the inherent overhead of interpretation.

- Optimizing the execution speed to provide a smooth development and testing experience for users.

- Developing the interpreter to work consistently across different operating systems, addressing platform-specific challenges.

- Ensuring a uniform user experience in various environments, including differing file systems and user interfaces.

- Implementing robust error detection in the interpreter for syntactical and runtime errors in AT2 code.

- Providing clear, helpful error messages and diagnostics to aid in debugging and code correction.

- Compiling comprehensive documentation that clearly explains how to use the interpreter and write code in the new AT2 language.

- Keeping documentation aligned with updates and enhancements to the interpreter and AT2 language.

- Actively incorporating user insights and suggestions into ongoing development for continuous improvement.



---

## 8. Documentation

### Documentation strategy
- **Comprehensive coverage**: All aspects of the project, from design and development to testing and deployment, will be thoroughly documented. This includes technical specifications, user manuals, and developer guides.
- **Clarity and accessibility**: Documentation will be written in clear, concise language to ensure it is accessible to all team members and stakeholders, regardless of their technical background.

### Types of documentation
- **Technical specifications**: Detailed descriptions of the virtual processor's architecture, the AT2 language's syntax and semantics, and the development tools.
- **User manuals**: Guides for end-users on how to use the virtual processor and write programs in the AT2 language. This will include examples and tutorials.
- **Developer guides**: Instructions and best practices for developers working on the project, covering coding standards, project setup, and contribution guidelines.
- **QA Testing document**: A separate document provided by the Quality Assurance team, detailing testing methodologies, test cases, and results.

### Version control and updates
- **Regular updates**: Documentation will be regularly updated to reflect the latest changes and additions to the project.
- **Version control**: All documentation will be maintained under version control, ensuring that changes are tracked, and historical versions are accessible.

### Collaboration and review
- **Team involvement**: All team members will be encouraged to contribute to and review documentation to ensure accuracy and completeness.
- **Continuous improvement**: Feedback on documentation will be actively sought and used to make continuous improvements, ensuring that the documentation remains relevant and useful.

---

## 9. Appendices

### 9.1 References

1. "Assembly language." Gentoo Wiki. Overview and resources related to Assembly language programming. Available at: [wiki.gentoo.org](https://wiki.gentoo.org/wiki/Assembly_language)
2. Streanga, L. "Assembler Project." GitHub repository. An Assembler for converting Assembly language for a virtual processor into machine code. Available at: [github.com/lucas-streanga/Assembler-Project](https://github.com/lucas-streanga/Assembler-Project)
3. Edu4Java, "Compiler, interpreter and virtual machine.", educational website. Provides tutorials and explanations on compilers, interpreters, and virtual machines. Available at: [edu4java.com/en/concepts/compiler-interpreter-virtual-machine](http://www.edu4java.com/en/concepts/compiler-interpreter-virtual-machine.html)


## 9.2 Glossary

| Term             | Definition | Use in Project |
|------------------|------------|----------------|
| <a id="assembler"></a>**Assembler**   | A tool that converts Assembly language code into a **[machine code](#machine-code)** or an executable format. | Used to translate written Assembly code into a format that the virtual processor can execute. |
| <a id="Assembly-language"></a>**Assembly language** | A low-level programming language used to write instructions that a processor can understand directly. | The primary language used for programming the virtual processor. |
| <a id="binary"></a>**Binary**      | A base-2 numerical system used in digital electronics and computing. | Fundamental representation of data in the virtual processor. |
| <a id="bitwise-operation"></a>**Bitwise operation** | An operation that directly manipulates bits. | Used in Assembly language for low-level data manipulation. |
| <a id="debugger"></a>**Debugger**    | A tool used to test and debug programs. | Utilized for identifying and resolving issues in Assembly code. |
| <a id="hexadecimal"></a>**Hexadecimal** | A base-16 number system used in computing. | Used for representing binary data in a more readable format in Assembly code. |
| <a id="instruction-set"></a>**Instruction set** | The collection of instructions that a processor can execute. | Defines the capabilities of the virtual processor. |
| <a id="interpreter"></a>**Interpreter** | A program that executes instructions written in a programming or scripting language without requiring them to be compiled into machine language. | Responsible for reading and executing the AT2 language instructions on the virtual processor, acting as the bridge between the AT2 code and the virtual hardware. |
| <a id="machine-code"></a>**Machine code** | The lowest-level programming language, consisting of binary code. | The end product of the assembler, run by the virtual processor. |
| <a id="memory-addressing1"></a>**Memory addressing** | The method by which a processor can access data stored in memory. | Essential for the emulator's handling of memory operations. |
| <a id="opcode"></a>**Opcode**      | The part of a machine language instruction that specifies the operation. | Used in defining the functionality of AT2 instructions. |
| <a id="operand"></a>**Operand**     | The part of a computer instruction that specifies what data is to be operated on. | Used in AT2 instructions for specifying data or memory locations. |
| <a id="processor"></a>**Processor**   | The component that performs the instructions of a computer program. | The virtual processor is the central component of the emulator. |
| <a id="ram"></a>**RAM (Random Access Memory)** | Memory that can be accessed randomly, used for storing working data and machine code. | Simulated in the emulator for temporary data storage during program execution. |
| <a id="register"></a>**Register**    | A small, quickly accessible storage location in a processor. | Used in the virtual processor for holding temporary data and intermediate computation results. |
| <a id="rom"></a>**ROM (Read-Only Memory)** | Non-volatile memory used in computers and other devices. | Emulated to store the firmware and immutable data of the virtual processor. |
| <a id="syntax"></a>**Syntax**      | The rules defining the structure of correctly formatted programs in a language. | Decides how AT2 language code is written for the emulator. |
| <a id="virtual-processor"></a>**Virtual processor** | A software-based emulation of a processor. | Executes AT2 language programs as if running on an actual small and limited 16 bits processor processor. |

---
