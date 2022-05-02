/* 
 * File:   LCD_Setup.h
 * Author: mikef
 *
 * Created on April 24, 2022, 11:38 AM
 */

#ifndef LCD_SETUP_H
#define	LCD_SETUP_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
    
void I2C1_Write1Byte(uint8_t * data);
void LCD_Setup(void);



#ifdef	__cplusplus
}
#endif

#endif	/* LCD_SETUP_H */

