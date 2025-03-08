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

    size_t buffer_size = (size_t)atoi(argv[1]);

    if (buffer_size == 0) 
    {
        fprintf(stderr, "Buffer size must be greater than 0.\n");
        return EXIT_FAILURE;
    }
    
    /* Initialize the circular buffer. */
    CircularBuffer* cb = cb_init(buffer_size);

    if (!cb) 
    {
        fprintf(stderr, "Failed to initialize circular buffer.\n");
        return EXIT_FAILURE;
    }
    
    printf("Heart Rate Monitor started. Circular buffer size: %zu\n", buffer_size);
    printf("Press Ctrl+C to exit.\n\n");
    
    /* Generate a new heart rate every second. */
    while (1) 
    {
        int heart_rate = generate_random_heart_rate();
        cb_add(cb, heart_rate);  // Overwrites oldest reading if the buffer is full.
        
        double ema = compute_ema(cb, EMA_ALPHA);
        printf("New Heart Rate: %d bpm | EMA: %.2f bpm | Stored Readings: %zu\n",
               heart_rate, ema, cb_size(cb));
        
        // Sleep for 1 second.
        #ifdef _WIN32
        Sleep(1000); // Sleep in milliseconds on Windows.
        #else
        sleep(1);    // Sleep in seconds on Unix-based systems.
        #endif
    }
    
    /* Cleanup (this point is actually unreachable). */
    cb_free(cb);

    return EXIT_SUCCESS;
}

/* Generates a random heart rate between 44 and 185 bpm. */
int32_t generate_random_heart_rate() 
{
    srand(time(NULL)); /* Seed the random number generator */

    return (rand() % (MAX_HEART_RATE - MIN_HEART_RATE + 1)) + MIN_HEART_RATE;
}
