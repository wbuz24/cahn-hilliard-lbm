# UTK-LBM-Electrolyzer-Project

The University of Tennessee, Knoxville's Electrochemical Energy Storage and Conversion Lab's effort to model the two phase flow of a PEM Hydrogen Electrolyzer system

This is code for solving the Cahn-Hilliard Navier-Stokes coupled multiphase LBM equations. It is best suited to simulate high density and viscosity ratios inside a finite domain with realistic 2D boundary conditions. Utilizes the Lattice-Boltzmann method in both Python and C++.

The code is based on the works of by T. Lee, et al., 2005 1, 2 and 3.

## C++ Model

Written by Undergraduate students Will Buziak & Price LeNoir

Dependencies:
 - make
 - g++

Compile with make

```
make
```

Run from the command line

```
./bin/cahn-hilliard Number-Of-Lattice-Units Input-File
```

An input file can be optionally specified, if so it will read in a csv file that will then apply to the domain.

Translated from [Python Model](https://github.com/wbuz24/UTK-LBM-Electrolyzer-Project) developed by Frida Roenning & Anirban Roy 

## Advisors

Dr. Matthew Mench

Dr. Douglas Aaron

## Post-Doctoral

Dr. Yu-kai Weng

## Graduate Students

Anirban Roy

Frida Ronning 

## Undergraduate Students

Will Buziak

Price LeNoir
