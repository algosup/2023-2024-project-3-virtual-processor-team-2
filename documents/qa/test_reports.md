## This is the template of how the test reports will be documented for this project.

| ID | Date  |  Priority | Description                                  | Steps     | Expected Results                                                | Status    |Comment                   |
| -- | --- | -------- |------------------------------------------------------------------------------------------ | ------ | --------------------------------- | --------- | ----------------------------------------------------------------------------------------------------------------- |
| 01/001 | 01/01/1970 | HIGH | check function works | run the program | displays "Hello World" | Passed | The function works perfectly |

**ID**<br>
The ID of the test case. It will follow a certain pattern: 
- The first numbers are the version of the tested product -> `01`/001<br>
The versions are:
    - 01 = the 1st parser
    - 02 = the 2nd parser
    - 03 = the builder
    - 04 = the bin exporter
    - 05 = the virtual processor
- The last numbers are the number of the test -> 01/`001`

**Date**<br>
Set the date when the bug has been discovered.

**Priority**<br>
The priority level of the test case (High, Medium, Low)
- High: An issue about a major feature needs to be fixed as soon as possible.
- Medium: An issue about a feature that could be important needs to be fixed.
- Low: An issue about a non-required feature needs to be fixed.

**Description** <br>
A clear and concise description of what the test deals with. If the Priority is 'High', the tester needs to precise what the piece of code that has been tested is.

**Steps**<br>
Conditions applied during testing, add some steps to reproduce the behavior:

1. Go to '...'
2. Click on '....'
3. Scroll down to '....'
4. See error

**Expected results**<br>
A clear and concise description of what you expected to happen.
For Unit tests, it would be preferable to use "Expected as", and then the result the developers expect.

**Status:**<br> 
The current status of the test case (Passed, Failed, In Progress, Not Implemented).

**Comment**<br>
Add any other context about the problem here (recommended, especially for 'Failed' status).

## You can go the [spreadsheet](https://docs.google.com/spreadsheets/d/1_UT7jAKQBPeN4hyx2i_c3qdPqmBhTuxuURp5x7rv-hU/edit?usp=sharing) where the test reports will be documented.