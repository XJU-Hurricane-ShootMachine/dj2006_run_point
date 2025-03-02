/**
 * @file    bsp.c
 * @author  Deadline039
 * @brief   Bsp layer initialize.
 * @version 1.0
 * @date    2024-09-18
 */

#include <bsp.h>

/**
 * @brief Bsp layer initiallize.
 *
 */
void bsp_init(void) {
    HAL_Init();
    system_clock_config();
    delay_init(180);
    usart1_init(115200);
    usart2_init(115200);

    led_init();
    key_init();

    can1_init(1000, 350);
    can_list_add_can(can1_selected, 1, 4);
    dji_motor_init(&m2006_1, DJI_M2006, CAN_Motor1_ID, can1_selected);
    pid_init(&pid_pos, 8192, 8192, 30, 8000, POSITION_PID, 6.0f, 0.001f, 0.0f);
    pid_init(&pid_spd, 16384, 5000, 30, 8000, POSITION_PID, 8.0f, 0.001f, 0.2f);
}

#ifdef USE_FULL_ASSERT

#include <stdio.h>

/**
 * @brief HAL assert failed.
 *
 * @param file File name.
 * @param line Line.
 */
void assert_failed(uint8_t *file, uint32_t line) {
    fprintf(stderr, "HAL assert failed. In file: %s, line: %u\r\n", file, line);
}

#endif /* USE_FULL_ASSERT */