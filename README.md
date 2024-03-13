# UTK-LBM-Electrolyzer-Project

The University of Tennessee, Knoxville's Electrochemical Energy Storage and Conversion Lab's effort to model the two phase flow of a PEM Hydrogen Electrolyzer system

This is code for solving the Cahn-Hilliard Navier-Stokes coupled multiphase LBM equations. It is best suited to simulate high density and viscosity ratios inside a finite domain with realistic 2D boundary conditions. Utilizes the Lattice-Boltzmann method in both Python and C++.

The code is based on the works of by T. Lee, et al., 2005 1, 2 and 3.

## C++ Model
Written by Will Buziak

Dependencies:
 - make
 - g++

Compile with make

```
make
```

Model developed by Frida Roenning & Anirban Roy 

## Python

Model written & developed by Frida Ronning & Anirban Roy 

The code is written and tested in Python 3.10.11 and uses the following packages:

   - numpy, https://numpy.org/
   - matplotlib, https://matplotlib.org/
   - numba, https://numba.pydata.org/
   - cv2, https://opencv.org/
   - python built-in packages (viz. datetime, copy, os, sys)

The code can be installed by cloning the repository and installing the required packages using pip:
```
git clone <repo-url-here>
python -m pip install -r ./requirements.txt
```

Usage:

To run the code, simply run the main.py file:
```
python CH_main.py
```
The output files are saved in the ./output/ folder. The output files are saved in the following format:

    Phi@time*.png: The phase field images of the simulation
    Pressure@time*.png: The hydrodynamic pressure field images of the simulation
    Total_Pressure@time*.png: The total thermodynamic pressure field images of the simulation
    vel@time*.png: The velocity field images of the simulation
    Density@time*.dat: The phase field data of the simulation
    Pressure@time*.dat: The hydrodynamic pressure field data of the simulation
    Velocity@time*.dat: The velocity field data of the simulation

To change the simulation parameters, edit the CH_base.py file. This file contains the base definitions of the lattice constants, physical constants, and the flow parameters. The CH_base.py file is imported by the main.py and the other CH_*.py files to run the simulation.

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
