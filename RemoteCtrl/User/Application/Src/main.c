/**
 * @file    main.c
 * @author  Deadline039
 * @brief   Main function files.
 * @version 1.0
 * @date    2024-07-29
 */

#include "includes.h"


/**
 * @brief 遥控器下标数组下标
 */
enum {
    ARRAY_KEY = 0x00U,
    ARRAY_LEFT_X,
    ARRAY_LEFT_Y,
    ARRAY_RIGHT_X,
    ARRAY_RIGHT_Y,
};


/**
 * @brief The program entrance.
 *
 * @return Exit code.
 */
int main(void) {
    bsp_init();
    uint8_t remote_data[5] = {0};
    message_register_send_handle(MSG_REMOTE, &usart1_handle);
    while (1)
    {
        LED0_ON();
        remote_data[0] = keyboard_scan();
        //uart_printf(&usart1_handle,"%d\n",remote_data);
        message_send_data(MSG_REMOTE, MSG_DATA_UINT8, remote_data,
                          MSG_GET_DATA_ARRAY_LENGTH(remote_data));
        delay_ms(50);
    }
    
}