<b>MIPS CPU Simulator </b>
=======================================
This CPU Simulator was created from scratch for the coursework section of the second year module <b>Computer Architecture</b>, which is a part of Electronic and Information Engineering at Imperial College London.  The original specification for the project can be found [*here*](original-spec.md). 

Overview
-------------------------
This C++ program takes as input binaries compliant with the MIPS ISA and runs them as if they were running on a MIPS CPU. This program could potentially allow a developer without access to a MIPS CPU to test if their compiled code would run on one.

This program simulates the 5 Stage MIPS execution cycle. After using the *fstream* library to read the binary and store the instructions in virtualised instruction memory, instructions are <b>fetched</b> from this memory with via accessing STL Vector elements and <b>decoded</b> using shifts. The instruction is then <b>executed</b> by the program. Data memory is virtualised using an STL Vector, as are CPU Registers. This allows for <b>memory access</b> and register <b>write back</b>. The size and location of memory is defined by the memory map specified in original-spec.md.

A testbench written in Bash Script is also included with example binaries.
    
How to run the program
=======================

Prequisites
------------

- Make
- GCC/G++


Install
--------
<b>Clone the repository</b> by either downloading the zip file using the Git GUI or using the command line:
    
    git clone https://github.com/adidesh20/MIPS-CPU-Simulator.git

Then, from the top of the directory tree, run:
    
    make simulator

Running a Binary
--------------------
Assuming the presence of MIPS Binary `filename.bin`, from the top of the directory tree run:

    bin/mips_simulator filename.bin

    