//Jose Manuel Lopez Alcala
//CS 261
//Assignment 2
#include "cirListDeque.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

   struct cirListDeque *d1 = createCirListDeque();
   printf("%d\n", isEmptyCirListDeque(d1));//should be empty (1 should print)
   addBackCirListDeque(d1, 21);// added 21 to the end of the deque
   printf("%d\n", isEmptyCirListDeque(d1));//shoul'nt be empty (print 0)
   printCirListDeque(d1);//should only print 21
   addFrontCirListDeque(d1, 5);
   addFrontCirListDeque(d1, 6);
   addFrontCirListDeque(d1, 7);
   addFrontCirListDeque(d1, 8);
   addFrontCirListDeque(d1, 9);
   printCirListDeque(d1);//shoudl now print 9,8,7,6,5,21
   addBackCirListDeque(d1,22);//should now have 22 at the end 
   printCirListDeque(d1);//same print as last + 22 at end

   printf("At front of deque: %f\n",frontCirListDeque(d1));// should print 9
   printf("At end of deque: %f\n", backCirListDeque(d1));// shoudl print 22
   removeFrontCirListDeque(d1);
   printCirListDeque(d1);//9 should no longer be in the deque
   removeBackCirListDeque(d1);
   printCirListDeque(d1);//22 shoud no longer be in the deque
   freeCirListDeque(d1);

   printf("%s\n", "End of program");


	return 0;
}


