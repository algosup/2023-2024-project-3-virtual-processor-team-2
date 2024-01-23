﻿# **ALGOSUP Team 2**
### **Development team**
## **Functional Specification Document**
### **Unamed for now**

### **DOCUMENT VERSION 0.1**

**01/22/2024**

*

**AUTHORS**

|**Name**|**Role**|
| :-: | :-: |
|DESPAUX Guillaume|Program Manager|


**DOCUMENT HISTORY**

|**Date**|**Version**|**Document Revision Description**|**Document Author**|
| :-: | :-: | :-: | :-: |
|1/22/2024|0.1|?|DESPAUX Guillaume|
|1/23/2024|0.2|?|DESPAUX Guillaume|
|||||
|||||
|||||


**APPROVALS**

|**Approval Date**|**Approved Version**|**Approver Role**|**Approver**|
| :-: | :-: | :-: | :-: |
|?|0.1|QA?PM?||
|||||
|||||
|||||

- [**Table of Contents**](#table-of-content)
- [1. Introduction](#1-introduction)
   - [1.1   Purpose of the document](#11-purpose-of-the-document)
   - [1.2	Project Scope](#12-project-scope)
   - [1.3	Scope of the document](#13-scope-of-the-document)
   - [1.4 	Related documents](#14-related-documents)
   - [1.5   Glossary](#15-glossary)
   - [1.6   Risks and Assumptions](#16-risks-and-assumptions)
- [2.	System/Solution Overview](#2-system-solution-overview)
   - [2.1   Context Diagram/ Interface Diagram/ Data Flow Diagram, Application Screen Flow, Sitemap, Process Flow](#21-context-diagram-interface-diagram-data-flow-diagram-application-screen-flow-sitemap-process-flow)
   - [2.2   System Actors](#22-system-actors)
   - [2.3  Dependencies and Change Impacts](#23-dependencies-and-change-impacts)
- [3.	Functional Specifications](#3-functional-specifications)
   - [3.1 Title](#31-title)
      - [3.1.1 Purpose/ Description](#311-purpose-description)
      - [3.1.2 Use case](#312-use-case)
      - [3.1.3 Mock up](#313-mock-up)
      - [3.1.4 Functional Requirement](#314-functional-requirements)
      - [3.1.5 Field level specification](#315-field-level-specifications)
- [4.	System Configurations](#4-system-configurations)
- [5.	Other System Requirements/ Non-Functional Requirements](#5-other-system-requirements-non-functional-requirements)
- [6.	Reporting Requirements](#6-reporting-requirements)
- [7.	Integration Requirements](#7-integration-requirements)
   - [7.1	Exception Handling/ Error Reporting](#71-exception-handling-error-reporting)
- [8.	Data Migration/ Conversion Requirements](#8-data-migration-conversion-requirements)
   - [8.1	Data Conversion Strategy](#81-data-conversion-strategy)
   - [8.2	Data Conversion Preparation](#82-data-conversion-preparation)
   - [8.3	Data Conversion Specifications](#83-data-conversion-specifications)
- [9.	References](#9-references)
- [10.	Open Issues](#10-open-issues)
- [11. Appendix](#11-appendix)
- [11.2 Assembly Language](#112-assembly-language)


# **1. Introduction**

The goal of the project is to create a virtual processor and an interpreter for running assembly code on that processor. We need to create our [own assembly language](#112-assembly-language), create a [C](#11-appendix) program using [C standard librairies](#11-appendix) which can read text file(*.txt or can be something else?*), detect a *bad* semantic and syntatical errors. We also need to implement a virtual system displaying text in a virtual terminal, that can be accessed from the assembly code.

## **1.1 Purpose of the document**
   __Describe what a Functional Specification Document is and its intended purpose for the audience.  Included below is a standard purpose of the FSD, but modify the description as needed.__

The Functional Specification Document is a document that provides detailed information on *how* the system solution will function and the requested behavior.  This document is created based on the high-level requirements identified in the Business Requirements Document and provides traceability on the functional specifications back to the business requirements.  Included in this document will be the detailed functional requirements including use cases, system inputs and outputs, process flows, diagrams, and mock ups.

## **1.2 Project Scope**
1. The main goal is to develop a more understandable version of assembly, along with an interpreter capable of reading and compiling these files. The compiled code can then be run on an emulated old mobile phone, providing users with an extended range of functionalities.

     - We aim to enhance the functionality of an old classic phones by providing developers with the opportunity to create new applications or games for these vintage mobile devices. 
     - Our objective is to offer a new way of using a compact phone primarily for calls and texts, while also allowing it to serve as a simple entertainment device for moments such as waiting in queues or sitting in waiting rooms. 
     - Our intention is to promote a balanced usage, avoiding smartphone addiction, and revitalizing the appeal of old consoles and flip phones by introducing additional utilities.

2. We have outlined certain out-of-scope features designed to assist developers and clients in comprehending the product's capabilities:
 
   - Implementation of a debugger, facilitating a clear understanding of program execution and helping in comprehending how the Virtual Processor interprets the language.
   - Creation of a basic application, such as a Snake Game, to showcase how our language can enhance the overall user experience.

## **1.3 Scope of the document**  

   This document aims to explain the project without delving too deeply into technical explanations, making it understandable for everyone.

## **1.4 	Related documents**
Add any related documentation that is relevant and related to the FSD. Some examples are the Project Charter, etc..

|**Component**|**Name (with link to the document)**|**Description**|
| :- | :- | :- |
||||

## **1.5      Glossary** 
State any terms and its definition that are described in the functional specifications.  Include any acronyms that are mentioned in the document.

|**Term/Acronym**|**Definition**|**Description**|
| :- | :- | :- |
| Own Assembly Language | Assembly Language: Low-level programming language specific to a computer architecture. | A language who looks like Assembly but most easier to use and to understand created by ourself. |

## **1.6      Risks and Assumptions**
List any assumed factors and identified risks that could affect the functional design of the system.  Included can be third-party or commercial components that will be used, issues around the operating environment, or any constraints.

### Risks

- **Technical challenges:**

  - Unforeseen technical challenges in the virtual processor functioning, interpreter compilation or other development aspects may lead to delays or difficulties in achieving the desired functionality.
  
- **Resource constraints:**

   - Unexpected shortages or constraints in resources, including human resources or software tools, may impact the project's ability to meet deadlines or maintain quality standards.
  
- **Unpredictable technical issues:**

   - Unpredictable technical issues, such as compatibility problems on different systems or devices, may arise during the testing phase.

### Assemptions

- **Technical expertise:**

  - The development team possesses the necessary technical expertise in assembly language and parser to successfully create it.
  - The team has done a lot of research based on virtual processor functioning and architecture.
  
- **User engagement:**

  - There is an assumption that users will engage positively with our own assembly language, fostering community participation for use it and potential future enhancements.

- **Timely completion:**

  - The project assumes that it will be completed within the specified timeline, avoiding significant delays or disruptions.
  
- **Quality assurance:**

  - The testing and quality assurance processes will effectively identify and address any bugs or issues, ensuring a polished and functional virtual processor with our language and our interpreter.

#   **2.  System/ Solution Overview**
Provide a short description of the software and solution being specified and its purpose, including relevant benefits, objectives, and goals.

## **2.1     Context Diagram/ Interface Diagram/ Data Flow Diagram, Application Screen Flow, Sitemap, Process Flow**
Provide any appropriate graphical representations that are relevant to the system and project such as a context/interface/data flow diagram, application screen flow, site map, or process flow.  Add as many as needed.

__NONE FOR NOW__

## **2.2     System Actors**

### **2.2.1     User Roles and Responsibilities**

--------------------------------------------------------------------------------------------------

|**User/Role**|**Example**|**Frequency of Use**|**Security/Access, Features Used**|**Additional Notes**|
| :-: | :-: | :-: | :-: | :-: |
|include the specified user/role such as Purchasing Manager, Dept Admin, Faculty, Student, etc|include examples of real people  in the role|describes how often they use the system. State Frequent, Occasional or Rare|describe the features of the system available for the role and any security/access permissions that should be stated|add any additional notes or supporting documentation as necessary|

## **2.3  Dependencies and Change Impacts**

### **2.3.1      System Dependencies**
List and identify any dependencies the proposed solution will have on other systems.

### **2.3.2      Change Impacts**	
List and identify existing systems that will be impacted by the implementation of the proposed solution.

# **3.   Functional Specifications**
   Start describing the specifications related to the overall system here. You may want to create a table/ index of all functionalities explained in the sections below and link them to the items below

If no separate reference/ traceability document is created for the project, use this section to map the business requirements, use cases, functional requirements and the test cases

Group your functional specifications as appropriate for your project. You may want to divide them by screens, functional areas, user role, JIRA tickets or high-level functions Vs detailed functions or any other way that works for your project

## **3.1 Title**

### **3.1.1 Purpose/ Description**

Include a high-level description and purpose of the specifications covered in the section. 

### **3.1.2 Use case**
Map the functional requirement to one or more use cases mentioned in the Business Requirements document. If the use case is not described in detail in the Business Requirements document, describe the use case here. This typically includes the element s in the following table.

|**UC-1** |**Use case name** |
| :-: | :-: |
|**Primary Actor(s)**| primary actors that participate in this use case|
|**Stakeholders and Interest**|One sentence describing other stakeholders|
|**Trigger**|Condition/action that initiates/starts the use-case|
|**Pre-conditions**|Condition assumed to be true before the first step |
|**Post-conditions**|Condition after the use case is successfully executed  |
|**Main Success Scenario**|1. visit STARTING-POINT2. Step3. Step4. Make sure GOAL-ACHIEVED|
|**Extensions**|If Condition, then Alternative StepsList any extended steps/ scenarios that occur, other than the main success scenario.|
|**Priority**|indicate priority of high, medium or low|
|**Special Requirements**|Any system related special requirements needed to fulfill the use case |
|**Open Questions**|*Notes and questions*|

### **3.1.3 Mock-up**

Provide the mock-up of the functionality or a mock-up of the entire page

### **3.1.4  Functional Requirements**
*Describe the page level details that are not captured in section 3.1.5 below.  These may include any requirements related to Navigation Menu, Actions, transaction status, verification and validation requirements etc. 

*Make sure each specification has a reference number and is explained in the following format.

|**Spec ID**|**Specification Description**|**Business Rules/ Data Dependency**|
| :-: | :-: | :-: |
|Specification Identifier|Short explanation of the specification|Any validation rules or business rules|

Note: Section 3.1.4 and section 3.1.5 may be combined if there are a few functionalities on a particular page

### **3.1.5 Field level specifications**
*Specify all the field data elements related to the functional requirement in both tables below.

**Form Elements:**

|**Call-out**|**Field Label**|**UI Control**|**Mand?**|**Editable**|**Data Type**|**Value Set**|**Default Value**|**Data Example**|**Data Source**|
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
|mock-up reference|Label name|specify what UI control will be on screen|specify if field is mandatory|specify if field is editable|Specify the data type that will be used for this field|If value is from the set, specify the entire value set here|Specify if it should be defaulted to any value|Provide an example of the data|Specify the source of the data|
|Example: Call-out 1|User name|textbox|Yes|Yes|Alpha-numeric|none|NA|agujar|User entry|

**Form Business Rules and Dependencies:**

|**Field Label**|**Validation / Business Rules**|**Error Messages**|**Data Dependencies**|**Additional Info/ Notes**|
| :-: | :-: | :-: | :-: | :-: |
|Label name|Specify the validation rules and/ or business rules applicable to the form element|List the error message that should be displayed and under what conditions|Specify if there are any date dependencies|Provide any additional information here|
|Example: User name|User name shall be a valid Stanford Sunet ID|For incorrect user name display on setFocusOff: “Please provide a valid user name”|None|Access prohibited only to Stanford affiliates. For non-Stanford affiliates, check call-out 3.1|

**Buttons, Links and Icons:**

|**Button, Link, Icon Label**|**OnClick Event**|**Other Event**|**Visible**|**Enabled Vs Disabled**|**Navigate To**|**Validation**|**Dependencies**|
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
|Button label name|Specify the operation that would be performed on an on-click event|Specify the operation that would be performed on other events|Specify default visibility of the button|Specify if button is enabled or disabled and the condition, if any|Specify the link where the page will be re-directed, if any|Specify the validation rules on operation of the button|Mention if there are any dependencies on other form elements and/ or buttons|
|Example: Submit|Verify if user name and password are correct. If yes, log the user into the system.|OnMouseHover display the following message: “Please provide your web-authentication details to sign in|Yes, always|Disabled, by default.Enabled, after first key entered in either username or password field.|User Dashboard page|Verify if Username is a valid sunet ID and user name and password match with registry data.|Disable the New user functionality on subsequent pages if user logs in through this button.|


# **4.   System Configurations**
   Provide an overview of all the steps or the set ups required to configure an application/program. Also state the intent or purpose behind each set up or configuration. Discuss the possible alternatives, customizations, workaround’s, conditions and dependencies in a particular configuration. In case of Oracle applications, please list all applicable BR100’s or Application set up documents

# **5.   Other System Requirements/ Non-Functional Requirements**
   *This section is used in contrast with stated functional requirements to highlight the additional details on the quality related aspects as well as other behavioral aspects of a system. This section is used to capture the stakeholders’ implicit expectations about how well the system will work under a given circumstance. Here you can  state the specific SLA’s related to system response times (Data search and retrieval), Performance needs and metrics, Latencies in a particular timeframe or during high volume transactions, System failures and recovery management, Security levels and accessibility constraints, Data Backup and archiving Capabilities, Legal compliance needs etc. The broader definition of the term ‘system’ also includes integrations with all types of Mobile platforms, Mobile devices, Tablets and Smart phones. 

# **6.   Reporting Requirements**
   *This section is used to capture the reporting needs, including but not limited to the scope and format of the report, data elements and contents required on the report, file types and extraction mechanisms, user base and accessibility levels, frequency of report extractions etc. Also provide the mock up of the report if needed.  If necessary, create a separate document for reporting requirements. 

# **7.   Integration Requirements**
   Identify the integration needs and state all required interfaces with anything external to this solution including hardware, software, and users. Include Architectural overview diagrams, high level data flow diagrams, table structures and schema, interface protocols, API’s, Error conditions, Error validations and messaging needs, Auto processing requirements etc. You can optionally state hardware and software dependencies, Upgrade requirements, compatibility issues with existing frameworks and solutions, etc

(Data Flow Diagrams, Interface Diagrams – if necessary)

## **7.1  Exception Handling/ Error Reporting**
This is where you can explain the error conditions/Exceptions that normally happen in Interfaces or cross flow system integrations. Explain the nature of exception, Error Id, Root cause of the error and also the strategy to handle the scenario. You can also indicate if there are any concurrent programs designed to automatically handle the error records or error conditions. State if there are any error reports generated or notifications utilized to alarm the support teams and system Administrators during the interface failures or outages


|**Exception/ Error ID**|**Error**|**Cause**|**Solution Strategy**|
| :-: | :-: | :-: | :-: |
|||||
# **8.   Data Migration/ Conversion Requirements**
   Explain in brief the data conversion plan. Provide full identifying information for the automated system, application, or situation for which the Data Conversion Plan applies. Describe briefly any assumptions, constraints or risks regarding the data conversion effort. (Provide details in section 1.6)

## **8.1 Data Conversion Strategy**
*Include the overall strategy for the Data Conversion. This includes how and when you will perform the conversion - the approach used to extract, transform and load data during the conversion process, the conversion schedule, and test plan for testing the converted data.

## **8.2 Data Conversion Preparation**
*Provide details on any prerequisites necessary for the conversion. Discuss the backup strategy, restoration process in case the conversion fails.

## **8.3 Data Conversion Specifications**

|**Source**|**Source Data Element**|**Target**|**Target Data Element**|**Conversion Rules**|**Notes**|
| :-: | :-: | :-: | :-: | :-: | :-: |
|Source location|Source Data Element Identifier |Target location|Target Data Element Identifier|Describe rules for Data conversion|Additional notes|

# **9.   References**
   List all references to external material used as background information or knowledge for the FSD. Examples may include a compliancy website, Stanford website, etc

# **10.  Open Issues**

|**Issue ID**|**Issue**|**Raised By**|**Raised On**|**Solution/ Decision**|**Resolved By**|**Resolved On**|**Status**|
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
|||||||||
# **11.  Appendix**
## **11.1**
## **11.2 ASSEMBLY LANGUAGE**
January 22, 2024

