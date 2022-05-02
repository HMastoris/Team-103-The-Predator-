/*
 *  File: main.c
 *  Authors: Mike, Johnny, Haylee, KJ
 *     EGR 314 Team 103
 *     Spring 2022
 * 
 *      Title: The Predator: 
 *      Wearable IOT GPS Enabled Range Finder
 */
   
#include "mcc_generated_files/mcc.h"
#include "GPS.h"
#include "IR.h"
#include "LCD_Setup.h"

#define U1_EN()         (U1CON0 = 0xB0)
#define U1_DIS()        (U1CON0 = 0x80)
#define U3_EN()         (U3CON0 = 0xB0)
#define U3_DIS()        (U3CON0 = 0x80)
#define GPS_Start()     do { LATAbits.LATA2 = 1; } while(0)
#define GPS_Stop()      do { LATAbits.LATA2 = 0; } while(0)

void SW_1_ISR(void){
 
   for(int i=0; i<=3; i++)
    {
        LED_2_Toggle();     // Visible sign that interrupt worked
        __delay_ms(200);
    }
    
    Sw_f = 1;               // Flag to enter if statement 1 in main loop
    IOCBFbits.IOCBF2 = 0;   // Clear IOC flag
}
    //------------------------------------------------------------------------------------------------------------------------------//
void main(void){

    SYSTEM_Initialize();    // See following comment

    //UART interrupts interfere with IOC, UART disabled to prevent interrupt  
    U1_DIS();   
    U3_DIS();

    INTERRUPT_GlobalInterruptEnable();
    UART3_SetRxInterruptHandler(GPS_flag);
    IOCBF2_SetInterruptHandler(SW_1_ISR);

    I2C1_Write1Byte(0x01);      // Turn off LCD

    LED_SetHigh();
    LED_2_SetHigh();
    LED_3_SetHigh();
    Sw_f = 0;
    GPS_f = 0;

    //Enable GPS, allow GPS startup time, write GPGLL PMTK command to GPS: GPS only outputs GPGLL
    GPS_Start();
    __delay_ms(10);
    U3_EN(); 
    for (int i=0; i<=60; i++){
            UART3_Write(GLL[i]);
    }
    U3_DIS();

    //------------------------------------------------------------------------------------------------------------------------------//
    
        while (1){


                if (Sw_f == 1){                  // If statement 1

                        dist_1 = Dist_Read(IR1);    //

                        sprintf(Distance, "Distance: %u\r", dist_1);

                        LCD_Setup();                // Print mock data to LCD
                        Sw_f = 0;                   // Reset flag
                        U3_EN(); 

                }
                if (GPS_f == 1 )            // If statement # 2: Read UART3, Parse, Write to UART1
                {                
                        GPS_Read();                // Read GPS data and send it to ESP32
                        printf(Distance);          // Send Distance to ESP32
                        U1_DIS();
                        GPS_f = 0;
                }

    }   // while(1)
}   //void main
