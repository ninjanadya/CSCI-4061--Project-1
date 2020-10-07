## Information
* The purpose of this program is to count the number of occurrences of each word in a text file

* compile it by going into the project file and using the following command
$ make

*it is run with the following usage:
$ ./mapreduce num_of_mappers num_of_reducers filename
example:
% ./mapreduce 5 2 test/T1/F1.txt

* This program performs a map-reduce using a given number of mapper processes and reducer processes to perform a word count on the specified file. 
* It will output one file for each reducer, each file will be a collection of words and their counts, one on each line.

* No further assumptions were made other than the ones in the project 1 document.

# Contributions:
* Sean: wrote the needed functions in mapper.c and the map-related part of mapreduce.c
* Nadya: wrote the needed functions in reducer.c and the reduce-related part of mapreduce.c
* Both team members also helped debug code written by the other.

* test machine : CSE LAB_machine_name
* date : 10/05/20
* name : Nadya Postolaki , Sean Berg
* x500 : posto018 , berg2007
