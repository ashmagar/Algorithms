To Compile
$ make


To Run
$ ./main


Files
main.c
makefile
README.txt
I_Count.pdf


Instructions
Run programe, then you will be given choices.
Give choice, then give input size
Pattern showing sort process using * will be shown if input size is less or equal to 20
Press 5 then Enter to exit the program


Sample Output:

ashish@amagar1:~/pro1_algo$ make
gcc -Wall -g -c main.c
gcc -Wall -g main.o -o main
ashish@amagar1:~/pro1_algo$ ./main

 1.Selection Sort 
 2.Randomized Quick Sort 
 3.Counting Sort 
 4.Merge Sort 
 5.Exit

 
 Enter Choice : 1
 Enter input size: 5


 original array is
 8 4 4 8 9 

 ****
 ********
 ****
 ********
 *********

 ****
 ****
 ********
 ********
 *********
 sorted array is
 4 4 8 8 9 

 1.Selection Sort 
 2.Randomized Quick Sort 
 3.Counting Sort 
 4.Merge Sort 
 5.Exit

 
 Enter Choice : 5
ashish@amagar1:~/pro1_algo$ 
