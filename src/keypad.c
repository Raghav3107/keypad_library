/**
 * @file keypad.c
 * @author @Raghav3107
 * @brief 
 * - set the row as output and column as input.
 * - at reading time 
 *    - first set the whole row pin to low (0).
 *    - Now one by one set the row pins high (1) and check every pins coloumns.
 *    - It will give the pressed key.
 * @check the simple_keypad.ino program for better understanding of logic.
 * check working principle of keypad.
 * @link https://youtu.be/84M-aOPBca8 
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

/* esp-idf library */
#include "driver/gpio.h"
#include "esp_err.h"

/* keypad header */
#include "keypad.h"

/* --------------------------------------------------------*/

static int rows;      /**< no of rows */
static int cols;      /**< no of cols */
static int *rowIo;    /**< row input/output */
static int *colIo;    /**< column input/output */
static int *btnVals;  /**< value of key pressed */
static int lastKey;   /**< last key pressed */

/* --------------------------------------------------------*/

void keypad_setup(int rowCount, int columnCount, int *rowPinCons, int *columnPinCons, int *buttonValues)
{
  esp_err_t err = ESP_OK;
  rows = rowCount;
  cols = columnCount;
  rowIo = rowPinCons;
  colIo = columnPinCons;
  btnVals = buttonValues;

  /**< set row as output */
  for (int row = 0; row < rows; row++)
  {
    err = gpio_set_direction(rowIo[row], GPIO_MODE_OUTPUT);
    if (err != ESP_OK)
    {
      printf("ERROR: failed to set the row pin %d as input. error %s", rowIo[row], esp_err_to_name(err));
    }
  }

  /**< set column as input */
  for (int col = 0; col < cols; col++)
  {
    err = gpio_set_direction(colIo[col], GPIO_MODE_INPUT);
    if (err != ESP_OK)
    {
      printf("ERROR: failed to set the column pin %d as input. error %s", colIo[col], esp_err_to_name(err));
    }
  }
  return;
}

/* --------------------------------------------------------*/

int keypad_getNumber()                        // getNumber function
{
  int key = KEY_NOT_PRESSED;                               // Key & number variables
  int number = 0;                             // Start with zero                                 
  lastKey = KEY_NOT_PRESSED;
  
  while(1)                                    // Get number loop
  {
    key = keypad_read();                      // Get pressed key (or KEY_NOT_PRESSED for none)
    
    if( (key >= 0) && (key <= 9) )            // If a digit key was pressed
    {
      number = number * 10 + key;             // Make next digit in number
                                              // Display the key that was pressed
    }      
    else if(key > 9)                          // If # pressed
    {
                                              // Advance to next line
      lastKey = key;
    }
    
    while(key != KEY_NOT_PRESSED)                          // Wait for key to be released
    {                                         // before taking another digit
      key = keypad_read();
    }   
    if(lastKey > 9) 
    {
      break;                                  // Break if non-digit
    }
  }
  return number;                              // Return number value
}  

/* --------------------------------------------------------*/

int keypad_getNumberEndKey(void)                 // getNumber function
{
  return lastKey;
}  

/* --------------------------------------------------------*/

int keypad_read(void)
{
  return keypad_readFrom(KEY_NOT_PRESSED);
}

/* --------------------------------------------------------*/

int keypad_readFrom(int button)
{
  esp_err_t err = ESP_OK;
  int state = 0, n = 0;
  int row, col, rowStart, colStart;
  int elements = rows * cols;

  if (button != KEY_NOT_PRESSED)
  {
    for (n = 0; n < elements; n++)
    {
      if (btnVals[n] == button)
      {
        n++;
        break;
      }
    }

    rowStart = n / cols;
    colStart = n % cols;
    button = KEY_NOT_PRESSED;
  }
  else
  {
    rowStart = 0;
    colStart = 0;
  }

  if (n == elements)
  {
    return KEY_NOT_PRESSED;
  }

  for (row = 0; row < rows; row++)
  {
    err = gpio_set_level(rowIo[row], 0);
    if (err != ESP_OK)
    {
      printf("ERROR: failed to set the pin %d low.\n", rowIo[row]);
    }
  }
  for (row = rowStart; row < rows; row++)
  {
    for (col = colStart; col < cols; col++)
    {
      err = gpio_set_level(rowIo[row], 1);
      if (err != ESP_OK)
      {
        printf("ERROR: failed to set the pin %d low.\n", colIo[col]);
      }
      state = gpio_get_level(colIo[col]);

      err = gpio_set_level(rowIo[row], 0);
      if (err != ESP_OK)
      {
        printf("ERROR: failed to set the pin %d low.\n", colIo[col]);
      }

      if (state)
      {
        button = (row * cols) + col;
        // DEBUG PURPOSE
        // printf("button Pressed: %d\n", button);
        // printf("button %c state %d row %d col %d\n",
        //        btnVals[(row * cols) + col], state, row, col);
        break;
      }
      else
      {
        //printf("button not Pressed:\n");
      }

      colStart = 0;
    }

    if (state)
    {
      break;
    }
  }
  if (button == KEY_NOT_PRESSED)
  {
    return button;
  }
  else
  {
    return btnVals[button];
  }
}

/* --------------------------------------------------------*/