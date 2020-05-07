# Top Trumps
Generation of a deck for the Top Trumps card game as an optimization problem within the [GBEA benchmark](http://www.gm.fh-koeln.de/~naujoks/gbea/gamesbench_doc.html#toptrumps) (detailed information about the optimization problems can be found there).

Code by @TheHedgeify

## Build

Invoke either  
````
make all -f Makefile.in
````
or 
````
make all -f Makefile_win_gcc.in
````
depending on the platform to build the code.

## Run

Invoke either  
````
./TopTrumpsExec 1 2 3 88
````
or 
````
TopTrumpsExec.exe 1 2 3 88
````
depending on the platform to run the evaluate the middle of the domain for the given parameters (number of objectives = 1, function number = 2, instance number = 3, dimension = 88).

## Test

Invoke either  
````
./test_rw_top_trumps
````
or 
````
test_rw_top_trumps.exe
````
depending on the platform to run a test of the five Top Trumps objective functions.

Note that this does test the correctness of the evaluation, but rather checks that the code is being executed without problems.

