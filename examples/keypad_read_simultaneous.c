/**
 * @file keypad_example.c
 * @author @Raghav3107
 * @brief Reads the multi key press.
 * @version 1.0.1
 * @date 03-10-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
/* standard C library */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* freeRTOS library */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* keypad header */
#include "keypad.h"
/*---------------------------------------------------------------*/
int rows[4] = {23, 22, 25, 21}; // Row I/O pins (top to bottom)
int cols[4] = {19, 18, 26, 17}; // Column I/O pins (left to right)

int values[16] = { 1,    2,  3,   'A', // Values for each key in the 4x4
                   4,    5,  6,   'B',
                   7,    8,  9,   'C',
                  '*',   0, '#',  'D' };

/*---------------------------------------------------------------*/
void app_main(void)
{
    printf("setting up keypad\n");

    keypad_setup(4, 4, rows, cols, values); // Setup dimensions, keypad arrays

    printf("keypad setup done. \n");

    // Main loop
    while (1) 
    {
        int key = keypad_read(); // Get pressed key (or KEY_NOT_PRESSED for none)
        if(key == KEY_NOT_PRESSED) //If key = -1, key not pressed
        {
            //printf("KEY NOT PRESSED"");
        }
        else if ((key >= 0) && (key <= 9)) // Display key value
        {
            printf("%d: key = %d\n",__LINE__, key); // If key = 0 - 9, dispaly as decimal
        }
        else 
        {
            printf("%d: key = %c\n",__LINE__, key); // Otherwise, display as character
        }

        while (key != KEY_NOT_PRESSED) // Loop getting more pressed keys
        {
            key = keypad_readFrom(key);   // Use readFrom previous key

            if(key == KEY_NOT_PRESSED)
            {
                //printf("KEY NOT PRESSED"");
            }
            else if ((key >= 0) && (key <= 9)) // Process the same way as read
            {
                printf("%d: key = %d\n",__LINE__, key);
            }
            else
            {
                printf("%d: key = %c\n",__LINE__, key);
            }
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

/*---------------------------------------------------------------*/