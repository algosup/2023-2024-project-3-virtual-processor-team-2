This document contains the main management artifacts:
- [Project Charter](#project-charter)
- [Tasks \& schedules](#tasks--schedules)
- [RACI matrix](#raci-matrix)
- [Risks and Assumptions](#risks-and-assumptions)
- [Work Breakdown Structure](#work-breakdown-structure)
- [MoSCoW](#moscow)
- [Key Performance Indicators](#key-performance-indicators)
- [Post Mortem](#post-mortem)
- [Appendix](#appendix)
    - [1. Product Logo](#1-product-logo)
    - [2. Management Tools](#2-management-tools)
    - [3. Statement Of Work](#3-statement-of-work)

You can also take a look at [cumulative weekly reports](weekly_reports/cumulative.md) file.

As a new student, I chose to use a familiar environment for management and focus my time and energy on performing useful tasks. That's why I chose to use Google Spreadsheets for a major part of my management documentation.

# Project Charter

For this project, the meeting we had with the client on 01/16/2024 served as the project charter. The summary of the meeting can be consulted [HERE](../communications/minutes_of_meeting_01_16_2024.pdf).

# Tasks & schedules

The breakdown of the tasks, their assignment, as well as the planned and actual schedule of those tasks can be found [HERE](https://docs.google.com/spreadsheets/d/1nawLT6dMtwPcFpHMa4k32Nxjinokl4ZmX4GMZl1Fatc/edit?usp=sharing).

# RACI matrix

The RACI matrix is as follows:

| Name                      | Project Manager | Program Manager | Technical Leader | Software Engineer | Quality Assurance | Client | Stakeholders |
| ------------------------- | --------------- | --------------- | ---------------- | ----------------- | ----------------- | ------ | ------------ |
| Project brief             | I               | I               | I                | I                 | I                 | R / A  | C            |
| Project charter           | R / A           | C / I           | C / I            | C / I             | C / I             | C      | C / I        |
| Schedule / Gantt chart    | R / A           | C / I           | C / I            | C / I             | C / I             | -      | I            |
| Functional specifications | C               | R / A           | C                | -                 | C / I             | C      | I            |
| Technical specifications  | C               | C               | R / A            | C                 | C / I             | C      | I            |
| Code                      | -               | -               | R                | R / A             | I                 | -      | -            |
| Code review               | I               | -               | R / A            | R                 | R                 | -      | -            |
| Code documentation        | -               | I               | C                | R / A             | C / I             | I      | -            |
| Usage instructions        | -               | I               | C                | R / A             | C / I             | I      | -            |
| Testing plan              | I               | C               | C                | C                 | R / A             | I      | -            |

Key:
| Letter | Name        | Description                                                                                                                                       |
| ------ | ----------- | ------------------------------------------------------------------------------------------------------------------------------------------------- |
| R      | Responsible | Work to complete the task.                                                                                                                        |
| A      | Accountable | must sign off (approve) work that responsible provides. The one to praised or blame.                                                              |
| C      | Consulted   | Those whose opinions are sought, typically subject-matter experts, and with whom there is two-way communication.                                  |
| I      | Informed    | Those who are kept up-to-date on progress, often only on completion of the task or deliverable, and with whom there is just one-way communication |
|        | -           | Not involved                                                                                                                                      |

A readable and colored RACI spreadsheet can be found [HERE](https://docs.google.com/spreadsheets/d/17-31PYeuYhOWX956qyZJER-_5GFUCzEy7xImLAHIEhA/edit?usp=sharing).

# Risks and Assumptions

| ID  | Description                                                                                         | Risks                                                                                                                | Impact | Likelihood | Solution                                                                                                                                      |
| --- | --------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------- | ------ | ---------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| 1   | Create our own assembly language and its Interpreter is an exhausting work.                         | We may not finish on time, misunderstood the client requirements.                                                  | High   | Medium     | Start with the most simple and fundamental tasks and go to more detailed ones.                                                                |
| 2   | The new team highlights the possible issue of having different conventions within the team members. | The communication may suffer from  having different coding or documentation styles.                                  | Medium | Medium     | We will define precise specifications to ensure this does not happen.                                                                         |
| 3   | Compatibility between different hardwares is hardly possible.                                       | If the client decides to use our language and our interpreter on real hardware, our program may not work.            | Medium | Low        | We will endeavor to make it cross-platform.                                                                                                   |
| 4   | The client may decide to change the requirements of the project.                                    | We would reconsider a new path to take, possibly delaying us if we were already done.                                | Medium | Medium     | We will often communicate with the client to ensure the current specifications are relatable.                                                 |
| 5   | Winter is here, sicknesses and transport issues could come up easier.                               | Team members may be late or even missing, possibly for multiple days.                                                | Medium | High       | The work of absent members will either be shared to others, done later, or done remotely.                                                     |
| 6   | Inadequate Testing                                                                                  | If testing is not comprehensive, it may lead to undetected bugs and errors in the interpreter.                       | High   | Medium     | Implement rigorous testing protocols throughout development and regularly conduct test reviews.                                               |
| 7   | Limited Documentation                                                                               | Insufficient documentation could impede future development or troubleshooting.                                       | Medium | Medium     | Establish a documentation plan and ensure all team members adhere to documentation standards.                                                 |
| 8   | Team Member Turnover                                                                                | If key team members leave, it could disrupt project progress and knowledge transfer.                                 | High   | Low        | Cross-train team members on critical tasks and maintain documentation to facilitate knowledge sharing.                                        |
| 9   | Technology Obsolescence                                                                             | Rapid advancements in technology may make the chosen technology stack outdated, affecting project compatibility.     | Medium | Medium     | Regularly review and update the technology stack to incorporate the latest advancements and ensure long-term compatibility.                   |
| 10  | Intellectual Property Disputes                                                                      | Disputes over intellectual property ownership may arise, leading to legal challenges and project disruption.         | High   | Low        | Clearly define ownership and usage rights in project contracts, and seek legal advice to minimize the risk of intellectual property disputes. |
| 11  | Insufficient Backup and Recovery Mechanisms                                                         | Data loss due to inadequate backup and recovery mechanisms may result in setbacks and compromised project integrity. | High   | Medium     | Implement robust backup and recovery procedures to safeguard critical project data and ensure a quick recovery in case of data loss.          |
| 12  | Network and Infrastructure Issues                                                                   | Unforeseen issues with the network or infrastructure may disrupt project activities and communication.               | Medium | Medium     | Implement redundancy in critical systems, regularly monitor network performance, and have contingency plans for infrastructure failures.      |
| 13  | Team Member Burnout                                                                                 | Excessive workload and stress may lead to team member burnout, impacting productivity and morale.                    | High   | Medium     | Monitor team workload, encourage work-life balance, and provide support mechanisms to prevent and address burnout.                            |

# Work Breakdown Structure

![](../images/management/workBreakdownStructure.svg)

# MoSCoW

| Must Have                                                                                                                       | Should Have                                            | Could Have | Won't Have                                                    |
| ------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------ | ---------- | ------------------------------------------------------------- |
| - Create custom assembly language (AT2)<br>- Create an assembler (2AT2)<br>- Implement a fully functional virtual processor<br> | - Optimized AT2 Code<br>- Handle Error in AT2 code<br> | - Debugger | - Real hardware compatibility<br>- More than 16bits registers |

# Key Performance Indicators

The spreadsheet for the KPI's data and graphs can be found [HERE](https://docs.google.com/spreadsheets/d/13n8fdWMEYFlJKhJ_OWILYcpX_c6CvLBpt4ebboLiU18/edit?usp=sharing).

# Post Mortem

|  | What you learned | Problem encountered | How do you handle it | What to improve | What you liked | What you don't liked | What are you proud |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| Mathias<br>(SCRUM Master) | - Communication<br>- English<br>- Management | - First time in management, no real guidance from other students<br>- Difficulty to blame other  | - Lot of research on internet<br>- Asking some advice to Franck (Superior) | - I need to develop more and more my KPIs<br>- I need to do more documentation at the beginning of the project to help everyone to stay on track | - The atmosphere of work, It was very close to work in companies' open-space | - I didn't code a lot in C, it didn't improved my C understanding and utility | - I'm proud of the project<br>- How the team has worked efficiently |
| Guillaume Des | - Learn a bit of C<br>- Learn a lot of team work | - Global overview of the project | - Making schematics and sketches | - make more research about the topic<br> | - Great Management<br>- Full English | - Didn't ask to the PM more document (MoSCoW, etc...) <br>- Maxime | - Understand a lot of the code.<br>- Proud of the synergy of the team |
| Guillaume Der | - English improvement<br>- REAL Basics of basics of C<br>- How to use GitHub | - Copy pasted another team's technical forcing him to restart from scratch <br>- Not enough skills led to a lack of motivation and an abandon of project<br>- Difficulty to understand what maxime explained multiple times<br>- Problem of communication with the rest of the team | - We need to explain him what to do | - Overall motivation, keeping it during the project duration | - Speaking in English but was disappointed at start<br>- A great Project Management<br>- Maxime knowledge in C<br>- Good atmosphere<br>- Everyone worked | - Being dismotivated and doing shit on internet | - Result of the project<br>- Team English progress<br>- To help a bit on the code |
| Paul | - memory allocation<br>- Basics of CMake | - Difficulty to install CMake and the compiler | - Maxime helped him to install everything | - Needed to find the best way to run the code (cmd or run button)<br>- Learned more about CMake and the other assisting systems | - Knowing what he has to do<br>- Fun to work with new students<br>- to be useful in the project<br>- Be more confident to ask and answer questions | - No enough coding | - Finding the idea to simplify the error system |
| Maxime | - Communication<br>- English (whole project in english) | - He accepted to replace the tech lead due to a lack of knowledge from him<br>- Struggled with the time due to a non-global project overview | - He worked more, worked on his free time (proud of the final product) | - first phase, better stepback and a global overview | - Speaking English during the whole project<br>- Calm work environment which helped us to be focus<br>- Worked with a lot a first years who are sometimes better than previous promotions | - Guillaume Der didn't work as hard as other members | - proud of the English improvement<br>- paul's work<br>- Guillaume's der advancement |
| Enzo | - C programming language<br>- How to really work as a team<br>- How to emphases the quality of a product | - When he set up the GitHub action, he had difficulties to understand how to do<br>- Understand as well the architecture of the project<br>- No native behavior to open GitHub issues | - Helped by maxime, looked how to setup a runner<br>- Reading it, created unit tests<br>- forced to do it and it became native | - best understanding at the beginning<br>- Be more motivated on a project that doesn't feel exiting, because we learn from each project<br>- Project global overview | - Only English in project sessions<br>- The QA role<br>- Maxime knew more C than us and brought us further in the project | - Maxime did 95% of the product | - Himself because he learned new things about GitHub and programming, Great QA job<br>- The team, we worked well and we have a quite nice product<br>- Proud of the english improvement of the entire team |

# Appendix

### 1. Product Logo

&emsp; For our product logo, we chose to give the team the opportunity to vote for their favorite design.
<br>&emsp; You can see the results [HERE](https://docs.google.com/spreadsheets/d/13H7NKF3Axvht02Pguh0YWgaVgjaN4GnWWcN4PkJFUns/edit?usp=sharing).

### 2. Management Tools

To efficiently manage the team I created a dedicated internal spreadsheets you can take a look [HERE](https://docs.google.com/spreadsheets/d/1jLRtSmWg94Tbuk7_OjGEhZ1jr0yF2lB5bi-84bGERh0/edit).

### 3. Statement Of Work

A statement of work (SOW) is a document which is the narrative description of a project's work requirement. It defines project-specific activities, deliverables and timelines for a vendor providing services to the client. The SOW typically also includes detailed requirements and pricing, with standard regulatory and governance terms and conditions.

You can take a look on this document [HERE](sow.md)