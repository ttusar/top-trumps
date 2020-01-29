# Top Trumps
Generation of a deck for the Top Trumps card game as an optimization problem

Code by @TheHedgeify

## Build

In the `src` folder run either  
````
make all -f Makefile.in
````
or 
````
make all -f Makefile_win_gcc.in
````
depending on the platform.

## Build

In the `src` folder run either  
````
./TopTrumpsExec number_of_objectives, function, instance, dimension
````
or 
````
TopTrumpsExec.exe number_of_objectives, function, instance, dimension
````
depending on the platform to run the evaluator for the given parameters.

## Test

In the `src` folder run either  
````
./test_rw_top_trumps
````
or 
````
test_rw_top_trumps.exe
````
depending on the platform to run a test evaluation of the five Top Trumps objective functions.
