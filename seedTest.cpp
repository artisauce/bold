#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Here's how seeds are going to be done. In the end, all we need is a sequence of random numbers determing where dadada happens.


int main ()
{
	// Let's take the standard seed, which is actually 0.
  	printf ("First number: %d\n", rand()%100);
  	printf ("Random number: %d\n", rand()%100);
	printf ("Random number: %d\n", rand()%100);
	printf ("Random number: %d\n", rand()%100);
	printf ("Random number: %d\n", rand()%100);
  	srand (1); // 1 reinitializes the whole thing. wew. Takes an UNSIGNED INT as the input.
  	printf ("Again the first number: %d\n", rand()%100);
	printf ("Random number: %d\n", rand()%100);
	printf ("Random number: %d\n", rand()%100);
	printf ("Random number: %d\n", rand()%100);
	printf ("Random number: %d\n", rand()%100);
	// Great. Now how do we use our own seeds?
	printf("----------------------\n");
	int seedStorage = rand();
	srand(seedStorage); // This is probably how it might actually look like, unfortately.
	printf ("First number: %d\n", rand()%100);
  	printf ("Random number: %d\n", rand()%100);
	printf ("Random number: %d\n", rand()%100);
	printf ("Random number: %d\n", rand()%100);
	printf ("Random number: %d\n", rand()%100);
  	srand (seedStorage);
  	printf ("Again the first number: %d\n", rand()%100);
	printf ("Random number: %d\n", rand()%100);
	printf ("Random number: %d\n", rand()%100);
	printf ("Random number: %d\n", rand()%100);
	printf ("Random number: %d\n", rand()%100);
	// Wow lad. Now what was seedstorage?
	printf(" ===== %d\n", seedStorage);
	// What this means is that we can use randomized seeds to generate randomized seeds. We store the seeds somewhere in case we need to regenerate.
	//

  return 0;
}