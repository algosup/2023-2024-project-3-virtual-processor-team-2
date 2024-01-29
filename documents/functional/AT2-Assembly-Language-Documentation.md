# AT2 Assembly Language
# Reference Manual

<details>
<summary>Table of Contents</summary>

 - [1. Introduction](#1-introduction)

</details>

## General-Purpose Instructions
### Data Transfer Instructions
The data transfer instructions move data between memory and the general-purpose and
segment registers, and perform operations such as conditional moves, stack access, and data conversion.

### Binary Arithmetic Instructions
The binary arithmetic instructions perform basic integer computions on operands in memory or the general-purpose registers.
|AT2 Mnemonic|Description|
| :- | :- |
|+|addition|
|-|substraction|
|/|division|
|*|multiplication|
|%|modulo|
|>>|shift right|
|<<|shift left|
|\||or|
|&|and|
|^|xor|
|!|not|
|**neg**||
|++|increment|
|--|decrement|

### Logical Instructions
The logical instructions perform basic logical operations on their operands.
|AT2 Mnemonic|Description|
| :- | :- |
|&&|AND|
|!|NOT|
|\|\||OR|
|^|XOR|

### Control Transfer Instructions
The control transfer instructions control the flow of program execution.
CALL -> CALL
JMP -> GOTO
*LOOP -> ?*
RET -> RET

### Shift and Rotate Instructions
The shift and rotate instructions shift and rotate the bits in their operands.
R SHIFT -> <<
L SHIFT -> >>

# REGISTER 0-7 16bits(7th for clock)
R0 -> ?x
R1 -> ?x
R2 -> ?x
R3 -> ?x
R4 -> ?x
R5 -> ?x
R6 -> ?x
R7 -> Reserved for clock

# IMPROVEMENT {ELSE IF} STATEMENT

TO IMPLEMENT 
*END*
*GETCLOCK*
*LABEL:*

