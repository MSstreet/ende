#include <stdio.h>

void main ()
{
	char * hello = "hello";
	int iter = 0;
	for (;iter<5;iter++)
		printf ("%c\n", hello[iter]);
	printf ("\n");
	
	for (iter = 0;iter<5;iter++)
		printf ("%X\n", hello[iter]);
	printf ("\n");

	printf ("hello world");
}
