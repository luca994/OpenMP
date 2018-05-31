# Open MP project

The purpose of this software is to compute real-time ball possession statistics of a soccer match. For doing that we have data originating from wireless sensors embedded in the shoes and in the ball used during the match.

## Prerequisites

You have to install the Open MP API for c++ in order to compile the code.
All the files to run the simulation of the program, except for the "full-game" with all the events of the match, are already in the repository in the folder "files".
The file with all the events of the match must be placed in the folder "files" without changing its name ("full-game"). It can be downloaded at https://mega.nz/#F!XQ0DzaqC!aOR5sxXPD6hJncWcW-BAsQ

## Getting Started

Steps to run the program:
```
make
./soccer_mpi_project k T
```
- k is the distance from the ball at which the ball possession is calculated.
- T is the time interval at which the file of events is parsed.

Use ```make clean``` to remove the built objects

## Built With

* [Open MP API](https://www.openmp.org/) - API used for parallel programming

## Authors

* **Luca Santini**
* **Riccardo Remigio**
