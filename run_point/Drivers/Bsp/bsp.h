/**
 * @file    bsp.h
 * @author  Deadline039
 * @brief   Bsp layer export interface.
 * @version 1.0
 * @date    2024-09-18
 */

#ifndef __BSP_H
#define __BSP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <CSP_Config.h>



#include "./core/bsp_core.h"
#include "./core/core_delay.h"
#include "./key/key.h"
#include "./led/led.h"
#include "./AK-Motor/ak_motor.h"
#include "./DJI-Motor/dji_bldc_motor.h"
#include "./VESC/vesc_motor.h"
#include "./CAN/can_list.h"
#include "pid.h"


void bsp_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BSP_H */