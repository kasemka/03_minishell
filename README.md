## Minishell

> The aim of the writing project is to learn how to work with processes and file descriptors in C.

<!--### Contents
* [General Info](#general-information)
* [Technologies Used](#technologies-used)
* [Features](#features)
* [Screenshots](#screenshots)
* [Setup](#setup)
* [Usage](#usage)
* [Project Status](#project-status)
* [Room for Improvement](#room-for-improvement)
* [Acknowledgements](#acknowledgements)
* [Contact](#contact) -->


### General Information
Minishell is an attempt to build our own shell, just a small command-line interpreter.

Command output works like in bash. It can be run by calling program in the terminal. 


![1](https://user-images.githubusercontent.com/83021442/149616957-0a6f8637-7596-4986-aeda-ece2ca86a08c.png)


<!--- What problem does it (intend to) solve?
- What is the purpose of your project?
- Why did you undertake it?-->
<!-- You don't have to answer all the questions - just the ones relevant to your project. -->

<!--
## Technologies Used
- Tech 1 - version 1.0
- Tech 2 - version 2.0
- Tech 3 - version 3.0 -->


### Features
- Executes commands from bin.
- Shows a prompt when waiting for a new command.
- Has a working History.
- ctrl-C ctrl-D ctrl-\ should work like in bash.
- Redirects output (<, >, >>), "<<" reads input from the current source until delimiter is seen.
- Has working pipes
- Returns exit status

![2](https://user-images.githubusercontent.com/83021442/149620306-bf0e0552-f5de-44aa-bcd0-446067e392ac.png)


### Setup
There is a Makefile in root directory, so all neccessary files can by compiled by runnig "make" command from minishell root directory.
It was tested on MacOS

<!--
## Usage
How does one go about using it?
Provide various use cases and code examples here.-->


### Project Status
Finished

<!--
## Room for Improvement
Include areas you believe need improvement / could be improved. Also add TODOs for future development.

Room for improvement:
- Improvement to be done 1
- Improvement to be done 2

To do:
- Feature to be added 1
- Feature to be added 2


## Acknowledgements
Give credit here.
- This project was inspired by...
- This project was based on [this tutorial](https://www.example.com).
- Many thanks to...


## Contact
Created by [@flynerdpl](https://www.flynerd.pl/) - feel free to contact me!
-->
