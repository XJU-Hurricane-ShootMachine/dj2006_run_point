/**
 * @file    keyboard.h
 * @author  Deadline039
 * @brief   16键矩阵键盘驱动
 * @version 0.2
 * @date    2023-11-05
 * @note    由于键盘的IO较多, 宏定义较麻烦, 所以这里就不定义IO口了
 */
#ifndef __KEY_BOARD_H
#define __KEY_BOARD_H

#include <CSP_Config.h>

#define KEYBOARD_GPIO_PORT GPIOB
#define KEYBOARD_GPIO_ENABLE()                                                 \
    do {                                                                       \
        __HAL_RCC_AFIO_CLK_ENABLE();                                           \
        __HAL_AFIO_REMAP_SWJ_NOJTAG();                                         \
        __HAL_RCC_GPIOB_CLK_ENABLE();                                          \
    } while (0)

/* 所有按键的IO口 */
#define ALL_KEYS_IO                                                            \
    GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 |           \
        GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9
/* 列的IO, 1,3,4,5 */
#define COL_KEY_IO GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5
/* 行的IO, 6,7,8,9 */
#define ROW_KEY_IO GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9

void keyboard_init(void);
uint8_t keyboard_scan(void);

#endif /* __KEY_BOARD_H */