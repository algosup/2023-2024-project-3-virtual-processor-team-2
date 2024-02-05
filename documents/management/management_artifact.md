This document contains the main management artifacts:
- [Project Charter](#project-charter)
- [Tasks \& schedules](#tasks--schedules)
- [RACI matrix](#raci-matrix)
- [Risks and Assumptions](#risks-and-assumptions)
- [Key Performance Indicators](#key-performance-indicators)
- [Appendix](#appendix)
    - [1. Product Logo](#1-product-logo)

You can also take a look at [cumulative weekly reports](weekly_reports/cumulative.md) file.

As a new student, I chose to use a familiar environment for management and focus my time and energy on performing useful tasks. That's why I chose to use Google Spreadsheets for a major part of my management documentation.

# Project Charter

For this project, the meeting we had with the client on 01/16/2024 served as the project charter. You can consult the summary of the meeting [HERE](../communications/minutes_of_meeting_01_16_2024.pdf).

# Tasks & schedules

The breakdown of the tasks, their assignment, as well as the planned and actual schedule of those tasks can be found here:
[Link](https://docs.google.com/spreadsheets/d/1nawLT6dMtwPcFpHMa4k32Nxjinokl4ZmX4GMZl1Fatc/edit?usp=sharing).

# RACI matrix

The RACI matrix is as follows:

| Name                      | Project Manager | Program Manager | Technical Leader | Software Engineer | Quality Assurance | Client | Stakeholders |
| ------------------------- | --------------- | --------------- | ---------------- | ----------------- | ----------------- | ------ | ------------ |
| Project brief             | I               | I               | I                | I                 | I                 | R / A  | C            |
| Project charter           | R / A           | C / I           | C / I            | C / I             | C / I             | C      | C / I        |
| Schedule / Gantt chart    | R / A           | C / I           | C / I            | C / I             | C / I             |        | I            |
| Functional specifications | C               | R / A           | C                |                   | C / I             | C      | I            |
| Technical specifications  | C               | C               | R / A            | C                 | C / I             | C      | I            |
| Code                      |                 |                 | R                | R / A             | I                 |        |              |
| Code review               | I               |                 | R / A            | R                 | R                 |        |              |
| Code documentation        |                 | I               | C                | R / A             | C / I             | I      |              |
| Usage instructions        |                 | I               | C                | R / A             | C / I             | I      |              |
| Testing plan              | I               | C               | C                | C                 | R / A             | I      |              |

Key:
| Letter | Name        | Description                                                                                                                                       |
| ------ | ----------- | ------------------------------------------------------------------------------------------------------------------------------------------------- |
| R      | Responsible | Work to complete the task.                                                                                                                        |
| A      | Accountable | must sign off (approve) work that responsible provides. The one to praised or blame.                                                              |
| C      | Consulted   | Those whose opinions are sought, typically subject-matter experts, and with whom there is two-way communication.                                  |
| I      | Informed    | Those who are kept up-to-date on progress, often only on completion of the task or deliverable, and with whom there is just one-way communication |
|        | -           | Not involved                                                                                                                                      |

RACI colored spreadsheet easily readable can be found here: [Link](https://docs.google.com/spreadsheets/d/17-31PYeuYhOWX956qyZJER-_5GFUCzEy7xImLAHIEhA/edit?usp=sharing)

# Risks and Assumptions

| ID  | Description                                                                                         | Impact                                                                                                               | Impact | Likelihood | Solution                                                                                                                                      |
| --- | --------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------- | ------ | ---------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| 1   | Create our own assembly language and its Interpreter is an exhausting work.                         | We may not finish on time, miss understood the client requirements.                                                  | High   | Medium     | Start with the most simple and fundamental tasks and go to more detailed ones.                                                                |
| 2   | The new team highlights the possible issue of having different conventions within the team members. | The communication may suffer from  having different coding of documentation styles.                                  | Medium | Medium     | We will define precise specifications to ensure this does not happen.                                                                         |
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

# Key Performance Indicators

The spreadsheet for the KPI's data and graphs can be found here: [Link](https://docs.google.com/spreadsheets/d/13n8fdWMEYFlJKhJ_OWILYcpX_c6CvLBpt4ebboLiU18/edit?usp=sharing)

# Appendix

### 1. Product Logo

&emsp; For our product logo, we chose to give the team the opportunity to vote for their favorite design.
<br>&emsp; You can see the results  [HERE](https://docs.google.com/spreadsheets/d/13H7NKF3Axvht02Pguh0YWgaVgjaN4GnWWcN4PkJFUns/edit?usp=sharing).
<br>&emsp; *(Feel free to change these logo to fit to your company/projects)*

