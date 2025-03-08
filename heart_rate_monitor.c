#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

#include "circular_buffer.h"

#define EMA_ALPHA 0.3  /* Smoothing factor for EMA */

#define MIN_HEART_RATE 44
#define MAX_HEART_RATE 185

static int32_t generate_random_heart_rate(void); 

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

}

/* Generates a random heart rate between 44 and 185 bpm. */
int32_t generate_random_heart_rate() 
{
    srand(time(NULL)); /* Seed the random number generator */
    
    return (rand() % (MAX_HEART_RATE - MIN_HEART_RATE + 1)) + MIN_HEART_RATE;
}
