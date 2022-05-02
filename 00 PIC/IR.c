/*
 * File:   IR.c
 * Author: mikef
 *
 * Created on April 24, 2022, 12:29 PM
 */


#include <xc.h>
#include "IR.h"

//adc_result_t dist_1;


adc_result_t  Dist_Read(adcc_channel_t channel)
{
       dist_1 = ADCC_GetSingleConversion(channel);
//        while (dist_1 <= 0x2df)
//        {
            for (int i=0; i<=3; i++)
            {
                LED_Toggle();
                __delay_ms(200);
                
            }
            return dist_1;
}
