/**
 * @file keypad_countdown_timer.c
 * @author @Raghav3107
 * @brief 
 * @version 1.0.1
 * @date 03-10-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
/*---------------------------------------------------------------*/
/* standard C library */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* freeRTOS library */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* keypad header */
#include "keypad.h"

int rows[4] = {23, 22, 25, 21}; // Row I/O pins (top to bottom)
int cols[4] = {19, 18, 26, 17}; // Column I/O pins (left to right)

int values[16] = {1, 2, 3, 'A', // Values for each key in the 4x4
                  4, 5, 6, 'B',
                  7, 8, 9, 'C',
                  '*', 0, '#', 'D'};

/*---------------------------------------------------------------*/

/* function prototype */
int countdown(int t);

/*---------------------------------------------------------------*/
void app_main(void)
{
    printf("setting up keypad\n");

    keypad_setup(4, 4, rows, cols, values); // Setup dimensions, keypad arrays
    printf("keypad setup done. \n");

    while (1) // Main loop
    {
        print("Type number of seconds, "); // User prompt
        print("then press #.\r");

        int number = keypad_getNumber(); // Get number from keypad

        int result = countdown(number); // Start the countdown

        if (result == 0) // If counted down to 0
        {
            print("Countdown complete!\r"); // ...display success
        }
        else // If not
        {
            print("Countdown terminated"); // ...display terminated
            print(" at %d seconds.\r", result);
            while (keypad_read() != -1); // Wait for key release
        }
    }
}

/*---------------------------------------------------------------*/

int countdown(int t) // t = countdown time in s
{
    int key; // keypad reading variable

    do
    { // before starting countdown
        key = keypad_read();
    } while (key != -1); // Wait for key to be released

    while (1) // Keep counting down until 0
    {
        print("t = %d\r", t); // Display seconds
        if (keypad_read() != -1)
            break;
        if (t == 0)
            break;   // t == 0 exits loop
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // Delay 1 s
        t--;         // Subtract 1 from seconds
    }

    return t; // After loop, return the result
}
/*---------------------------------------------------------------*/