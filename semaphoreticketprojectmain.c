/*

Jonathan Winter
04 - 09 - 2018
ITEC 2085
Project: Semaphores and Multithreaded Processing

SOURCES FOR THIS PROJECT:
https://gist.github.com/tausen/4261887
http://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/
http://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html
http://pubs.opengroup.org/onlinepubs/7908799/xsh/semaphore.h.html
https://beginnersbook.com/2014/01/c-passing-array-to-function-example/
http://www.csc.villanova.edu/~mdamian/threads/hellomany.txt

*/

// Libraries needed to run the program
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <windows.h>

// Create the semaphore
sem_t semaphore;
int tickets = 200;	// Total tickets
int test = 0;		// Incrementer

// Agent Function
void agent(char *tixp)
{
	int x = 0;
	for(x = 0; x < tickets; x++)
	{
		
		// Lock the data from other threads
	    sem_wait(&semaphore);
	    
	    // CRITICAL CODE:
	    
	    // If there is a ticket available
	    if (*tixp == 'A')
	    {
			// Sell the ticket
	       	*tixp = 'S';
	       	test++;
	       	printf("TICKET *%d* SOLD at Agent: *%u*\n", test, (int)pthread_self());
	    	// Simulate a customer transaction for 2 seconds
			Sleep(2000);
	       	
		}
		// Increment the array
	    tixp++;
		// Unlock the data from other threads
	    sem_post(&semaphore);
	    // Simulate a customer transaction for 1 second
	    Sleep(1000);
	}
}

// Main Function
int main(int argc, char *argv[]) 
{
	// Print out the Name, Date, Course, and Project Description
	printf("Jonathan Winter\n");
	printf("04 - 09 - 2018\n");
	printf("ITEC 2085\n");
	printf("4-Threaded Application: Ticket Salesmen Project\n\n");
    
    // Declare Variables
	char tix[tickets];	// Ticket Array
    void *tixp = tix;	// Pointer to ticket array
    int x = 0;			// Counter
    int y = 0;			// Counter
	    
    // Used to hold the Thread ID's
    int t0, t1, t2, t3;
    
    // Fill Array with Available Tickets
    // and Display a cool graphic
    printf("Ticket Number\t| Available or Sold\n");
    printf("________________|___________\n");
    for (y = 0; y < tickets; y++)
	{
		// Setting tickets to 'A' for available ticket
		tix[y] = 'A';
		printf("Ticket: %d%\t| %c \n", y, tix[y]);
	}
	printf("\n");
    
    // Initialize semaphore, only to be used with threads in this process, set value to 1
    sem_init(&semaphore, 0, 1);
    // Create an array of threads
	pthread_t threads[4];
	// Initialize the threads, call agent function, pass array
	t0 = pthread_create(&threads[0], NULL, (void*)agent, tix);
	t1 = pthread_create(&threads[1], NULL, (void*)agent, tix);
	t2 = pthread_create(&threads[2], NULL, (void*)agent, tix);
	t3 = pthread_create(&threads[3], NULL, (void*)agent, tix);
	// Join the threads and wait for them to finish
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);
	pthread_join(threads[3], NULL);
	// Let the user know all of the tickets have been sold
	printf("All tickets have been sold. Displaying ticket information:\n\n");
	// Print the array of tickets again
    printf("Ticket Number\t| Available or Sold\n");
    printf("____________________________\n");
    for (y = 0; y < tickets; y++)
	{
		// Displaying Sold Tickets 'S' for sold ticket
		printf("Ticket: %d%\t| %c \n", y, tix[y]);
	}
	printf("\n");
    	
	return 0;
}
