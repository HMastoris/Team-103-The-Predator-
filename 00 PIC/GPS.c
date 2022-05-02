/*
 * File:   GPS.c
 * Author: mikef
 *
 * Created on April 24, 2022, 12:20 PM
 */

#include <xc.h>
#include "GPS.h"

void SW_1_ISR(void){
 
   for(int i=0; i<=3; i++)
    {
        LED_2_Toggle();     // Visible sign that interrupt worked
        __delay_ms(200);
    }
    
    Sw_f = 1;               // Flag to enter if statement 1
    //SW_1_SetHigh();
    IOCBFbits.IOCBF2 = 0;   // Clear IOC flag
}

void GPS_flag(void){
    UART3_Receive_ISR();    
    GPS_f = true;   
    // Flag to enter if statement 2
}

void GPS_Read(void){
    UART3_Receive_ISR();
    while (UART3_Read() != 0x24); // Wait here for a '$' character at the start of NMEA GPS data line (ASCII 0x24)
    //while(!UART3_DataReady);// Wait for new line to come in over UART
    for (int i=0; i<=50; i++){   //Read GPGLL data from GPS
        GPS_data[i] = UART3_Read();
    }
    __delay_ms(1);
    U3_DIS();               // Disable UART3 to prevent further interrupts
    /*       token = strtok(str, delimiters):  function reads char array and returns a token from the first address in str 
     *  to the last character bfore  a delimiter is reached. Data is removed from str and stored in token, therefore the 
     *  start address of every subsequent call of strtok() after the first begins at the first null address in str */
  
    lon = strtok(GPS_data, ",.\0");         // Start token "GPGLL"
    LED_Toggle();
    lon = strtok(NULL," ,.\0");       // Next token Longitude (deg,deg,min,min)
    LED_Toggle();
    lat = strtok(NULL," ,.\0");               // Next token, decimal: not needed
    LED_Toggle();
    lat = strtok(NULL," ,.\0");               // Next token, 'N': not needed
    LED_Toggle();
    lat = strtok(NULL," ,.\0");        // Last needed token, Latitude (deg,deg,deg,min,min)
    LED_Toggle();
    sprintf(str, "GPS: %sN %sW , ", lon, lat);  // Copy longitude and latitude to one string
    LED_Toggle();
    U1_EN();
    printf(str);                               // Print Latitude and longitude string
}

