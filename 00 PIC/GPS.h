/*
 *  File: GPS.h
 *  Authors: Mike, Johnny, Haylee, KJ
 *     EGR 314 Team 103
 *     Spring 2022
 * 
 *      Title: The Predator: 
 *      Wearable IOT GPS Enabled Range Finder
 */

#ifndef GPS_H
#define	GPS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "mcc_generated_files/mcc.h"
#include "stdlib.h"
#include <string.h> 

/* Macros for enabling and disabling peripherals and external hardware*/
#define U1_EN()         (U1CON0 = 0xB0)
#define U1_DIS()        (U1CON0 = 0x80)
#define U3_EN()         (U3CON0 = 0xB0)
#define U3_DIS()        (U3CON0 = 0x80)
#define GPS_Start()     do { LATAbits.LATA2 = 1; } while(0)
#define GPS_Stop()      do { LATAbits.LATA2 = 0; } while(0)
    
/* Volatile variables for use inside interrupt routines */
volatile int Sw_f =0;          // Button interrupt flag
volatile int GPS_f =0;         // UART interrupt flag

 //     PMTK command for GPS to output only GPGLL NMEA data 
char   * GLL = "$PMTK314,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n";    
char    GPS_data[50];  // Array for raw GPS data
char * lat;      // Array for parsed longitude
char * lon;      // Array for parsed longitude
char str[100];

void SW_1_ISR(void);
void GPS_flag(void);
void GPS_Read(void);
void U3_ER(void);


#ifdef	__cplusplus
}
#endif

#endif	/* GPS_H */

