## This is the template of how the test cases will be documented for this project.


| ID | Date  | Priority | Test case Scenario                                  | Test case Description     | Pre-conditions    | Test Steps                   | Expected Results                                                |
| -- | --- | -------- |------------------------------------------------------------------------------------------ | ------ | --------------------------------- | --------- | ----------------------------------------------------------------------------------------------------------------- |
| 01/001 | 01/01/1970 | HIGH | run the program, and see what's displayed | make sure the 'printf' function works correctly | have the most up-dated version of the product | 1. run the program 2. see the result | "Hello World" is displayed |

**ID**<br>
The ID of the test case. It will follow a certain pattern: 
- The first numbers are the version of the tested product -> `01`/001 <br>
The versions are:
    - 01 = the 1st parser
    - 02 = the 2nd parser
    - 03 = the builder
    - 04 = the bin exporter
- The last numbers are the number of the test -> 01/`001`

**Date**<br>
The date when the bug has been discovered.

**Priority**<br>
The priority level of the test case (High, Medium, Low).
- High: A major feature needs to be tested as soon as possible.
- Medium: A feature that could be important needs to be tested.
- Low: A non-required feature needs to be tested.

**Test case Scenario**<br>
The description of the scenario during testing. 

**Test case Description** <br>
A clear and concise description of what the purpose of the test case is. The tester will need to precise if he tests an Unit test.

**Pre-conditions**<br>
The requirements the tester could need to perform the test.

**Test Steps**<br>
The steps to reproduce the behavior:

1. Run '. . .'
2. Go to '. . .'
2. Click on '. . .'
3. Scroll down to '. . .'
4. See the result

**Expected results**<br>
A clear and concise description of what you expected to happen.
For Unit tests, it would be preferable to use "Expected as", and then the result the developers expect.

## You can go the [spreadsheet](https://docs.google.com/spreadsheets/d/1_UT7jAKQBPeN4hyx2i_c3qdPqmBhTuxuURp5x7rv-hU/edit?usp=sharing) where the test cases will be documented.
