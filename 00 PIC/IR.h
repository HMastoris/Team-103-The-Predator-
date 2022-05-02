/*
 *  File: IR.h
 *  Authors: Mike, Johnny, Haylee, KJ
 *     EGR 314 Team 103
 *     Spring 2022
 * 
 *      Title: The Predator: 
 *      Wearable IOT GPS Enabled Range Finder
 */

#ifndef IR_H
#define	IR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/mcc.h"

    
    adc_result_t dist_1;
    char Distance[64];
    
    adc_result_t Dist_Read(adcc_channel_t channel);
            


#ifdef	__cplusplus
}
#endif

#endif	/* IR_H */

