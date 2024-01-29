# Virtual Processor Project Test Plan

<details>
<summary>Table of Contents</summary>

- [Virtual Processor Project Test Plan](#virtual-processor-project-test-plan)
  - [1. Product Analysis](#1-product-analysis)
    - [1.2. Overview](#12-overview)
  - [2. Glossary](#2-glossary)
  - [3. Strategy](#3-strategy)
    - [3.1. Scope of Testing](#31-scope-of-testing)
      - [3.1.1. In-scope for Testing](#311-in-scope-for-testing)
      - [3.1.2. Out-of-scope for Testing](#312-out-of-scope-for-testing)
    - [3.2. Unit Tests](#32-unit-tests)
    - [3.3. Testing sessions](#33-testing-sessions)
      - [3.3.1. Overview](#331-overview)
      - [3.3.2. Smoke Testing](#332-smoke-testing)
        - [3.3.2.1. Smoke Testing Scope](#3321-smoke-testing-scope)
        - [3.3.2.2. Sequence of Smoke Testing](#3322-sequence-of-smoke-testing)
      - [3.3.3. Collaborative Testing Sessions](#333-collaborative-testing-sessions)-->
        - [3.3.3.1. Session Scope](#3331-session-scope)
    - [3.4. External tools](#34-external-tools)
      - [3.4.1. GitHub](#341-github)
        - [3.4.1.1. GitHub Overview](#3411-github-overview)
        - [3.4.1.2. GitHub Actions](#3412-github-actions)
          - [3.4.1.2.1. GitHub Actions Scope](#34121-github-actions-scope)
          - [3.4.1.2.2. Workflow](#34122-workflow)
          - [3.4.1.2.3. Configuration](#34123-configuration)
      - [3.4.2. GitHub Issues](#342-github-issues)
      - [3.4.3. Test Report and Meetings](#343-test-report-and-meetings)
      - [3.4.4. Bug Data Report Spreadsheet](#344-bug-data-report-spreadsheet)
        - [3.4.4.1. Spreadsheet Structure](#3441-spreadsheet-structure)
    - [3.5. Documentation](#35-documentation)
      - [3.5.1. GitHub Wiki](#351-github-wiki)
  - [4. Test Criteria](#4-test-criteria)
    - [4.1. Suspension Criteria](#41-suspension-criteria)
    - [4.2. Exit Criteria](#42-exit-criteria)
  - [5. Allocated Resources](#5-allocated-resources)
    - [5.1. Time](#51-time)
    - [5.2. People](#52-people)
    - [5.3. Testing Environment Requirements](#53-testing-environment-requirements)

</details>

---

## 1. Product Analysis

### 1.2. Overview

The project aims to create a virtual processor and an interpreter for running assembly code on that processor. The project would be developed in plain, portable, C language without the use of any external library beside 
C standard libraries. 

The assembly code would be created from scratch by us. It will deal with new names for several instructions and statements, while making sure that the purpose of an assembly language, which is to be more efficient and closer to the machine, is respected.

For further details, refer to the [functional specifications](../functional/"functional".md) document.


## 2. Glossary


| Term | Definition | Source |
| ---- | ---------- | ------ |
| **Assembly language** | A low-level programming language for a computer, or other programmable device, in which there is a very strong (generally one-to-one) correspondence between the language and the architecture's machine code instructions. | [Wikipedia](https://en.wikipedia.org/wiki/Assembly_language) |
| **Interpreter** | In this case, an interpreter is a computer program that directly executes instructions written in a programming or scripting language, without requiring them previously to have been compiled into a machine language program. | [Wikipedia](https://en.wikipedia.org/wiki/Interpreter_(computing)) |
| **Virtual Processor** | A processor (or processing unit) is an electrical component that performs operations on an external data source, usually memory or some other data stream. A virtual processor is basically a virtual machine that simulates the behavior of a processor. | [Wikipedia](https://en.wikipedia.org/wiki/Processor_(computing)) |
| **GitHub Actions** | A CI/CD tool that allows us to run tests automatically after various actions on the repository and avoid errors on the dev or main branch. | [GitHub](https://docs.github.com/en/actions) |
| **GitHub Issues** | A tool that allows us to create, manage, and assign issues to team members. | [GitHub](https://docs.github.com/en/issues) |
| **GitHub Wiki** | Every GitHub repository can be equipped with a wiki, to share long-form content about your project, such as how to use it, how you designed it, or its core principles. | [GitHub](https://docs.github.com/en/communities/documenting-your-project-with-wikis/about-wikis) |


---

## 3. Strategy

Here's the purpose of our testing strategy approach: <br> - **[Unit Tests](##32-unit-tests)** <br> - **[Testing sessions](#35-testing-sessions)** <br> - **[External tools](#36-external-tools)**

### 3.1. Scope of Testing

Tests serve as a tool for improving the quality of the product.<br>
Testing will focus on both memory allocating and basic instructions in assembly code to ensure that the quality of the required product is perfect. <br>The quality of all the product's features is mainly endorsed by Software Engineers and Quality assurances.

#### 3.1.1. In-scope for Testing

- 
- 
<!-- functional requirements -->

#### 3.1.2. Out-of-scope for Testing

- 
- 
<!-- non-functional requirements -->

---

### 3.2. Unit Tests

Unit testing is an important part of the process. These tests will be written by the Software Engineers throughout the project, in parallel with game development. <br> Then, the Quality Assurance will run these tests during tests cases. 


These unit tests serve three crucial objectives:

1. **Code Functionality:** Verify that each function performs as expected under various scenarios. 

2. **Code Quality:** Assess the clarity and quality of the code to promote maintainability and ease of collaboration among developers. 

3. **Code Coverage:** Guarantee comprehensive testing to prevent future changes from unintentionally altering the original behavior of the code.


---

### 3.3. Testing sessions


#### 3.3.1. Overview

We will perform manual 
testing, using a combination of **[Smoke Testing](#352-smoke-testing)** and **[Collaborative Testing Sessions](#353-collaborative-testing-sessions)** to ensure the quality of the game. 


#### 3.3.2. Smoke Testing

Testing sessions will take place during and after days dedicated to the project, they will serve as smoke tests. The primary goal of smoke testing is to quickly assess whether the essential functionalities of the project are working as expected after each build. This testing phase is designed to identify critical issues early in the development process, allowing for rapid feedback and swift resolution of potential show-stopping problems.

#### 3.3.2.1. Smoke Testing Scope

The smoke testing scope will focus on the fundamental aspects of the product, including:

1. **Process Launch:** Confirm that the product launches successfully without any critical errors or crashes.
2. **Instructions functionality:** Check that basic instructions work as intended.

#### 3.3.2.2. Sequence of Smoke Testing

During each smoke testing session, the following steps will be executed:

1. **Product Deployment:** Deploy the latest product in the testing environment.
2. **Test Execution:** Execute a set of [predefined test cases](./test_cases.md) covering the critical functionalities.
3. **Archiving results:** Archive the [test results](./test_reports.md) for future reference.
4. **Issue Reporting:** If critical issues are identified, we need to report them to the development team.

---

#### 3.3.3. Collaborative Testing Sessions
To obtain a better overview of the project, a collaboration with other teams' Quality Assurance was set up. This collaboration enables the teams to have an external view of the product and simply identify errors and bugs. The main advantage of this collaboration is to have several points of view on the same situation and to see or share new working methods. All the meetings' content will be written back in the [meetings reports](./meetings_reports.md) file.<br>
A meeting with the Software Engineers of the team 2 will be planned the day after each collaborative testing session.

##### 3.3.3.1. Session Scope

Sessions are designed primarily to:

1. **Verify that the product is working as expected:** Check that all the product's basic instructions and additional statements are working properly.
2. **Sharing tests:** Share tests between the teams to have a better overview of their product and to find easier bugs and errors.
3. **Identify bugs and errors:** Find bugs and errors in the product to improve it.
4. **Identify improvements and missing features:** Find improvements and missing features in the product to bring it as far as possible.

---

### 3.4. External tools

#### 3.4.1. GitHub

#### 3.4.1.1. GitHub Overview


GitHub serves as our central platform for version control, collaboration, and issue tracking.

---

#### 3.4.1.2. GitHub Actions


GitHub Actions are utilized for continuous integration and deployment. The workflow is triggered on each push to the main branch, ensuring the automatic execution of tests. (During the development phase, the workflow will also be triggered on each push to the dev branch.)

It will allow us to know if the code is unfunctional at some points, when it appeared and which changes caused it.


#### 3.4.1.2.1. GitHub Actions Scope

The GitHub Actions will be activated on pull requests on the dev and main branch and their scope is to:

1. **Launch and Interpret:** Launch the process and ensure there is no interpreting error.
2. **Run unit tests:** Run unit tests to ensure that the main functions of the product are working properly.
3. **Ensure that the code on the referenced branches is working** Ensure that the code on the main and dev branches is working properly and avoid creating new branches from code that doesn't work.

#### 3.4.1.2.2. Workflow

The workflow consists of the following steps:

1. **Checkout:** Retrieves the repository.
2. **Build:** Builds the project.
3. **Test:** Executes unit tests and testing scripts.
4. **Publish Test Results:** Publish the test results as artifacts.

If any of the steps fail, the workflow will be marked as failed and the development team will be notified at which step the error occurred.

#### 3.4.1.2.3. Configuration

Actions, such as interpreting and executing unit tests, will be performed on quality assurance's computer. These actions are enabled and synchronized with GitHub. Once the runner has been activated on the computer, it can be selected to execute the various workflow actions.

This allows us to have a runner available all time and to have a better overview of the errors that may occur.

---

#### 3.4.2. GitHub Issues

GitHub Issues is a built-in issue-tracking tool that allows us to create and manage issues and assign them to team members. This is mainly the role of the Quality Assurance to create as many GitHub Issues as there are problems regarding the product.

We define:

- **Bugs:** Unexpected problems or code errors.
- **Documentation:** Request for documentation on a specific function or group of functions in the code.
- **Task allocation:** Assignment and tracking of specific responsibilities.

**GitHub Issues Strategy:**

We are implementing a strategy for managing GitHub issues. Here are the key components of our strategy:

1. **Detailed Issue Descriptions:**
   - Issues should have clear and detailed descriptions to provide context and understanding.
   - Include steps to reproduce bugs or details about the feature request.
   - Specify the expected and actual behavior.

2. **Labeling System:**
   - Utilize labels to categorize issues, such as "bug," or "enhancement".
   - Labels help identifying the nature of the issue and prioritizing tasks quickly.

3. **Assignees and Responsibility:**
   - Assign issues to the appropriate team member or individuals responsible for addressing the problem.
   - Assignees take ownership of the task, improving accountability.

4. **Regular Issue Triage:**
    - Regularly review and triage open issues.
    - Prioritize tasks based on their urgency (Critical, High, Medium, Low).

By implementing these strategies, we aim to foster a more organized and efficient issue-tracking process on GitHub.

---

#### 3.4.3. Tests Report and Meetings

**Test Report:**

The [test report spreadsheet](https://docs.google.com/spreadsheets/d/1d-gDcUtc-J6af9MfQXIPr_xVtwP7XKyHaRIFd1-BpWI/edit?hl=fr#gid=0) will contain all the test reports of the project. Each test report will be listed and named with the ID of the test and the date of the test session.

**QA Meetings:**

The QA team could also have several meetings with the SE team, to talk about specific topics regarding the development. 

---

#### 3.4.4. Tests

To document and track easily test cases, their results, and overall testing progress, the tests would be divided into these three sections:

1. **Test Case Pattern:** 

We have to make a certain pattern for test cases to ensure the readability and consistency of the work:

![test case pattern](../images/qa_images/test_case_pattern.png)
For further details, refer to the [test case](./test_cases.md) document.

2. **Test reports Pattern:**

We also have to make a certain pattern for test reports to ensure the readability and consistency of the work:

![test report pattern](../images/qa_images/test_report_pattern.png)
For further details, refer to the [test report](./test_report.md) document.

3. **Progression:**
   - **Test Amount Representation:**
     - A visual schema representing the test cases based on the amount of their status (Passed, Failed, In Progress, Not Implemented).
     - Provides a visual snapshot of the overall testing status. <br>
   - **Example:** 
      - Passed: ![](https://geps.dev/progress/50)
      - Failed: ![](https://geps.dev/progress/25)
      - Work in Progress: ![](https://geps.dev/progress/85)
      - Not implemented: ![](https://geps.dev/progress/15)

### 3.5. Documentation

#### 3.5.1. GitHub Wiki
To enhance transparency, collaboration, and knowledge sharing within our development process, we are adopting a centralized documentation approach using GitHub Wiki. This platform will serve as a comprehensive repository for all documentation related to our codebase. 

- The GitHub Wiki will function as a centralized knowledge hub for our project, housing detailed documentation on code structure, functions, and project-related information.

- Documentation will be organized in a structured manner, with a table of contents for easy navigation.
Each complex function will have dedicated pages for in-depth information.
Flowcharts or diagrams will be integrated to enhance the understanding of complex processes.

- To facilitate developers in documenting their code effectively, we will provide a template that guides them on the essential information to include. The template will be available on the project GitHub [here](./code_documentation_template.md). Developers have to use it as a reference when documenting their code. 

- Centralized documentation simplifies onboarding for new team members by providing a single, accessible source of truth. Emphasize the importance of keeping documentation up-to-date, especially during onboarding periods, to ensure the documentation remains accurate and relevant.

- Implement a feedback mechanism or suggestion process within the Wiki to encourage continuous improvement and collaboration among team members.
---


## 4. Test Criteria

Setting up strict test criteria is crucial to guarantee the product's quality before its release. These criteria act as standards that need to be met before the product is distributed. By following clear rules for suspension and exit, the testing process aims to find and fix issues early on.

### 4.1. Suspension Criteria

Suspension criteria are established to define conditions under which testing activities may be temporarily halted. The following suspension criteria are identified:

1. **Critical Bug Threshold:**
   - If a predetermined threshold of critical bugs is reached during testing (10% of total test cases), testing will be suspended.
   - Critical bugs are those with a "High" impact on the core functionality of the software.

2. **Resource Unavailability:**
   - If essential testing resources, such as testing environments, tools, or personal, become unavailable for an extended period, testing may be suspended.
   - This criteria ensures that testing can resume only when necessary resources are accessible.

### 4.2. Exit Criteria

Before the product can be considered ready for distribution, certain benchmarks must be met. For instance, at least 80% of all test cases should pass successfully. This criteria ensures that the product meets the required quality standards before reaching the distribution phase.

1. **Test Case Coverage:**
   - A minimum test case coverage of 80% for all identified features and functionalities must be achieved before considering the test phase complete.
   - This ensures that almost all aspects of the software have been tested.

2. **Bug Resolution Rate:**
   - At least 90% of reported bugs must be addressed and resolved before exiting the testing phase.
   - This criteria emphasizes the importance of resolving identified issues to enhance the software's reliability
  
3. **Documentation Completeness:**
   - Comprehensive documentation, including test plans, test cases, test results, functional specifications, and technical specifications, must be finalized and reviewed for completeness.
   - Documentation should be easily understandable and accessible to all team members, ensuring a clear understanding of the testing process and results.

## 5. Allocated Resources

### 5.1. Time

<!-- Test Schedule -->
| Task | Start Date | End Date |
| ---- | ---------- | -------- |
| Review the documentation | January 15, 2024 | February 23, 2024 |
| First meeting with Dev team | January 23, 2024 | January 23, 2024 |
| Create and give template for GitHub Wiki documentation | January 29, 2024 | January 29, 2024 |
| Unit tests | November 27, 2023 | February 23, 2024 |
| First meeting with other teams' QA | January 29, 2024 | January 29, 2024 |
| Second meeting with Dev team | January 30, 2024 | January 30, 2024 |
| GitHub Actions | January 30, 2024 | February 23, 2024 |
| Second meeting with other teams' QA  | February 5, 2024 | February 5, 2024 |
| Third meeting with other teams' QA  | February 12, 2024 | February 12, 2024 |
| Third meeting with Dev team | February 13, 2024 | February 13, 2024 |
| Fourth meeting with other teams' QA | February 19, 2024 | February 19, 2024 |
| Fourth meeting with Dev team | February 20, 2024 | February 20, 2024 |

### 5.2. People

For this project, the people involved to perform tests are the Quality Assurance of team 2, but also Quality Assurances of other teams during the team test sessions:
- Enzo GUILLOUCHE - Team 2
- Séréna BAVAROIS - Team 1
- Maxime THIZEAU - Team 4
- Arthur LEMOINE - Team 3
- Atifa AMIRI - Team 

### 5.3. Testing Environment Requirements
  
1. **Code Editor:**
     - Visual Studio Code: Version 1.61.2 or later

2. **Desktop Platforms:**
     - Windows: 10 or later
     - macOS: Version 10.14 or later
