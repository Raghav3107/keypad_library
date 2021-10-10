/**
 * @file keypad.h
 * @author @Raghav3107
 * @brief 
 * @version 1.0.1
 * @date 03-10-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#define KEY_NOT_PRESSED       -1     

/*---------------------------------------------------------------*/
/**
 * @brief Set up the row and column dimensions, pins, and key values.
 * 
 * @param rowCount Number of keypad rows.
 * @param columnCount Number of keypad columns.
 * @param rowPinCons Array that stores the row connections (from top to bottom).
 * @param columnPinCons Array that stores the column connections (from left to right).
 * @param buttonValues Array that stores the values that should be returned for each key.
 */
void keypad_setup(int rowCount, int columnCount,
                  int *rowPinCons, int *columnPinCons,
                  int *buttonValues);


/*---------------------------------------------------------------*/

/**
 * @brief  Returns the first key pressed, or -1 if no key is pressed.
 * 
 * @return The value of the key that was pressed.  The value for each key 
 * is set up in the array that gets passed to keypad_setup's *buttonValues argument.  
 */
int keypad_read(void);

/*---------------------------------------------------------------*/
/**
 * @brief Get a number from the keypad.  The number will be retured as soon as
 * a non-numeric key is pressed and released.
 * 
 * @return The number that was entered. 
 */
int keypad_getNumber(void);

/*---------------------------------------------------------------*/

/**
 * @brief Get the key that terminated number received by keypad_getNumber.    
 * 
 * @return Key that terminated getNumber. 
 */
int keypad_getNumberEndKey(void); // getNumber function


/*---------------------------------------------------------------*/

/**
 * @brief If more than one key might be pressed and held at one time, use this 
 * keyapd_readFrom function to get the 2nd, 3rd, etc key.
 * 
 * @param button Pass the value last returned by either keypad_read or
 * keypad_readFrom.  This function will start searching from one past that key in
 * the scan order. 
 * 
 * @return The next key detected in the scan order, or -1 if no additional keys
 * are pressed 
 */
int keypad_readFrom(int button);

/*---------------------------------------------------------------*/

#endif /* _KEYPAD_H_ */