This document contains the main management artifacts:
- [Tasks \& schedules](#tasks--schedules)
- [RACI matrix](#raci-matrix)
- [Risks and Assumptions](#risks-and-assumptions)
- [Key Performance Indicators](#key-performance-indicators)

You can also take a look at [cumulative weekly reports](weekly_reports/cumulative.md) file.

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
| Code                      |                 |                 | R                | R / A             |                   |        |              |
| Code review               | I               |                 | R / A            | R                 | R                 |        |              |
| Code documentation        |                 | I               | C                | R / A             | C / I             | I      |              |
| Usage instructions        |                 | I               | C                | R / A             | C / I             | I      |              |
| Testing plan              | I               | C               | C                | C                 | R / A             | I      |              |

Key:
| Letter | Name        | Description                                               |
| ------ | ----------- | --------------------------------------------------------- |
| R      | Responsible | Work to complete the task.                                        |
| A      | Accountable | must sign off (approve) work that responsible provides. The one to praised or blame. |
| C      | Consulted   | Those whose opinions are sought, typically subject-matter experts, and with whom there is two-way communication.                    |
| I      | Informed    | Those who are kept up-to-date on progress, often only on completion of the task or deliverable, and with whom there is just one-way communication                      |
|        | -           | Not involved                                              |

RACI colored spreadsheet easily readable can be found here: [Link](https://docs.google.com/spreadsheets/d/17-31PYeuYhOWX956qyZJER-_5GFUCzEy7xImLAHIEhA/edit?usp=sharing)

# Risks and Assumptions

| ID  | Description                                                                   | Impact                                                                                     | Impact | Likelihood | Solution                                                                                                          |
| --- | ----------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------ | ------ | ---------- | ----------------------------------------------------------------------------------------------------------------- |
| 1   | Create a Virtual Processor and a Interpreter is a big work                     | We may not finish on time, miss understand the client requirements.                                    | High   | Medium     | Start with the most simple and fundamental tasks and go to more detailed ones.    |
| 2   | New team add the possible issue of members without the same conventions.                                 | The communication might suffer from this by having different styles.                       | Medium | Medium     | We will define precise specifications to ensure this does not happen.                                             |
| 3   | Compatibility between different hardware is hardly possible.                  | If the client decides to use our language and our interpreter on real hardware, our program may not work.                  | Medium | Low        | We will try to stay closer as possible than a real old mobile phone.                                                        |
| 4   | The client may decide to change the requirements of the project.              | We would have to reasses a new path to take, possibly delaying us if we were already done. | Medium | Medium     | We will communicate often with the client to ensure that the specifications are correctly defined from the start. |
| 5   | Winter is here, health and transport issues are more likely to come up. | Team members may be late or even missing, possibly for multiple days.                      | Medium | High       | The work of missing member will either be shared to other, done later, or done remotely.                          |


# Key Performance Indicators

The spreadsheet for the KPI's data and graphs can be found here: [Link (WIP)]()