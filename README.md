# HopHopEngine

Welcome to the demo repository for Hop Engine

## Contributors
* Azita
* Caleb
* Jake
* Indigo
* Glen

## Instructions
This repository contains a compiled static library, libHopEngine.a, which is located in engine/build/lib. It is not possible to compile this library on the VIU lab machines at this time, but the compiled library reflects the source code contained in engine/src. We hope to have a better solution for building the engine soon.

To view the four demos, please navigate to the example directory. There is a Makefile in each demo directory which will compile the demo code into an executable file (something.bin). This executable file can then be run from the terminal on lab machines.

example/maze is a recreation of the maze demo from our presentation, since Glen mistakenly deleted the source code. As the Makefile for this demo currently uses the single-file miniaudio library, it takes a few extra seconds to compile this demo. 

The source code for Hop Engine is located in engine/src/ and is divided amoung multiple sub-directories which corrospond to components of the engine. 
