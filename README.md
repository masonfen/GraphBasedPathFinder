# GraphBasedPathFinder
Computes shortest paths between actors using movie connections

This program solves the "Six Degrees of Kevin Bacon" where it determines the shortest connection path between two actors based on 
co appearences in a movie. This program then uses BFS (Breadth-first-search) and finds the shortest path between any 2 given actors


Main.cpp:entry point of program for i/o handling
SixDeg.h: header file containning declarations for SixDegfreesGraph class and helper functions
SixDeg.cpp: implemenation of the sixdegreesgraph class and its methods
Makefile: compiles all of the code to create an executable


instructions:

run make in the Sixdegrees directory

type ./sixdegrees <input_file> <output_file> --> make sure they are both txt files

Ex.

Seshadhri John_Wayne
Ingrid_Bergman Ingrid_Bergman


should return:

Not present
Ingrid_Bergman
