# AT2 Assembly Language
# Reference Manual

Table of Contents
- [Introduction](#introduction)
- [SYSTEM](#system)
    - [Registers](#registers)
    - [Lexical Conventaions](#lexical-conventions)
        - [Comments](#comments)
        - [Labels](#labels)
        - [Variables](#variables)
        - [Strings](#strings)
        - [Character](#character)
- [INSTRUCTIONS](#instructions)
    - [General-Purpose Instructions](#general-purpose-instructions)
        - [Data Transfer Instructions](#data-transfer-instructions)
        - [Binary Arithmetic Instructions](#binary-arithmetic-instructions)
        - [Logical Instructions](#logical-instructions)
        - [Shift Insctructions](#shift-insctructions)
        - [Data Transfer Instructions](#data-transfer-instructions)
        - [Control Transfer Instructions](#control-transfer-instructions)
        - [String Instructions](#string-instructions)
        - [I/O Insctuctions](#io-insctuctions)
        - [Operating System Support Instructions](#operating-system-support-instructions)
        - [?](#?)
        




    


## Introduction
text here

## SYSTEM
### Registers
The Virtual Processor is compposed by 8 registers of 16 bits each (value max of 0xFFFF), rg0 to rg3 (rg3 is reserved to the clock and he's in read only).

### Lexical Conventions
#### Comments
A comment can be appended to a statement. The comment consists of the double slash character (//)(ASCII 0x2F 0x2F) followed by the text of the comment. The comment is terminated by the newline that terminates the statement.

#### Labels
lab: ?

#### Variables
VAR ?

#### Strings
"" : 0b

#### Character
'' : 0x



## INSTRUCTIONS
### General-Purpose Instructions
#### Data Transfer Instructions
The data transfer instructions move data between memory and the general-purpose and segment registers, and perform operations such as conditional moves, stack access, and data conversion.
|AT2 Mnemonic|Description|Example|
| :- | :- | :- |
|mov|copy the data immediate value and paste it to another location|mov [rg0], [rg1]|
|push|push into stack|push [rg0]|
|pop|pop last from stack|pop|
|pusha| text here ||
|popa| text here||

#### Binary Arithmetic Instructions
The binary arithmetic instructions perform basic integer computions on operands in memory or the general-purpose registers.
|AT2 Mnemonic|Description|Example|
| :- | :- | :- |
|+|addition|+ [register], 2|
|-|substraction|- [register], 2|
|/|division|/ [register], 2|
|*|multiplication|* [register], 2|
|%|modulo|% [register], 2|
|\||or|+ [register], 2|
|&|and|+ [register], 2|
|^|xor|+ [register], 2|
|!|not|+ [register], 2|
|**neg**|||
|++|increment|++ [register]|
|--|decrement|-- [register]|
|if|compare|if [register], 2|
|else|compare|else [register], 4|

#### Logical Instructions
The logical instructions perform basic logical operations on their operands.
|AT2 Mnemonic|Description|Example|
| :- | :- | :- |
|&&|AND|&& [rg0], [rg1]|
|!|NOT|! [rg0], [rg1]|
|\|\||OR|\|\| [rg0], [rg1]|
|^|XOR|^ [rg0], [rg1]|
|<|inferior|< [rg0], [rg1]|
|>|superior|> [rg0], [rg1]|
|<=|inferior or equal|<= [rg0], [rg1]|
|>=|superior or equal|>= [rg0], [rg1]|
|=|equal|= [rg0], [rg1]|
|!=|not equal|!= [rg0], [rg1]|


#### Shift Insctructions
|AT2 Mnemonic|Description|Example|
| :- | :- | :- |
|>>|shift right|>> [register]|
|<<|shift left|<< [register]|

#### Control Transfer Instructions
The control transfer instructions control the flow of program execution.
|AT2 Mnemonic|Description|Example|
| :- | :- | :- |
|call|call procedure|call label|
|goto|go to procedure|goto label|
|ret|return where previous call was use|ret|

#### String Instructions
text here
|AT2 Mnemonic|Description|Example|
| :- | :- | :- |
|draw| text here |draw|

#### I/O Insctuctions
The input/output instructions transfer data between the processor's I/O ports, registers, and memory.
|AT2 Mnemonic|Description|Example|
| :- | :- | :- |
|get| text here ||

#### Operating System Support Instructions
text here
|AT2 Mnemonic|Description|Example|
| :- | :- | :- |
|clock| text here||
|ngr|exit the system call||

#### ?
?
|AT2 Mnemonic|Description|Example|
| :- | :- | :- |
|?|?|?|



