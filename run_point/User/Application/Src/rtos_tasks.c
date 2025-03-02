/**
 * @file    rtos_tasks.c
 * @author  Deadline039
 * @brief   RTOS tasks.
 * @version 1.0
 * @date    2024-01-31
 */

#include "includes.h"
#include "uart2_calbackl.h"
#include "remote_ctrl.h"
#include "dji_angle.h"

#include "shoot_machine.h"

#include "queue.h"
#include "semphr.h "

void motor_task(uint8_t key);
void msg_task(uint8_t msg_length, message_type_t msg_type, void *msg_data);
/*控制摩擦轮任务与实行任务的消息队列*/
QueueHandle_t Queue_From_Fir; // 单个变量消息队列句

static TaskHandle_t start_task_handle;
void start_task(void *pvParameters);

static TaskHandle_t task1_handle;
void task1(void *pvParameters);

static TaskHandle_t task2_handle;
void task2(void *pvParameters);

static TaskHandle_t task6_handle;

void task6(void *pvParameters);

QueueHandle_t message_queue;

/*****************************************************************************/

/**
 * @brief FreeRTOS start up.
 *
 */
void freertos_start(void) {
    xTaskCreate(start_task, "start_task", 512, NULL, 2, &start_task_handle);
    message_queue = xQueueCreate(2, sizeof(int));
    vTaskStartScheduler();
}

/**
 * @brief Start up task.
 *
 * @param pvParameters Start parameters.
 */
void start_task(void *pvParameters) {
    UNUSED(pvParameters);
    taskENTER_CRITICAL();

    xTaskCreate(task2, "task2", 256, NULL, 2, &task2_handle);

    xTaskCreate(task6, "task6", 256, NULL, 3, &task6_handle);

    xTaskCreate(task1, "task1", 256, NULL, 1, &task1_handle);

    vTaskDelete(start_task_handle);
    taskEXIT_CRITICAL();
}

/**
 * @brief Task1: 指定串口发送.
 *
 * @param pvParameters Start parameters.
 */
void task1(void *pvParameters) {
    UNUSED(pvParameters);

    while (1) {
        LED0_TOGGLE();
        LED1_TOGGLE();
    }
}

/**
 * @brief Task2: 指定串口接收
 *
 * @param pvParameters Start parameters.
 */
void task2(void *pvParameters) {
    UNUSED(pvParameters);
    message_add_polling_handle(&usart1_handle);
    message_register_recv_callback(MSG_REMOTE, remote_receive_callback);
    remote_register_key_callback(1, motor_task);
    remote_register_key_callback(2, motor_task);//使能按键1，2，为其指定回调函数。

    while (1) {

        message_polling_data();
        vTaskDelay(50);
    }
}

/**
  * @brief 接收目标角度，让电机工作。
  * 
  * @param pvParameters 
  */
void task6(void *pvParameters) {
    UNUSED(pvParameters);
    float set_angle = 0, angle_out = 0;
    float spd_out = 0;

    while (1) {
        xQueueReceive(message_queue, &set_angle, 10);
        angle_out = pid_calc(&pid_pos, set_angle, (float)m2006_1.rotor_degree);
        spd_out = pid_calc(&pid_spd, angle_out, (float)m2006_1.speed_rpm);
        dji_motor_set_current(can1_selected, DJI_MOTOR_GROUP1, spd_out, 0, 0,
                              0);
        vTaskDelay(5);
    }
}


/**
  * @brief 接收回调函数，判断键值，设置目标角度
  * 
  * @param key,按键 
  */
void motor_task(uint8_t key) {
    float set_angle;
    if (key == 1) {
        set_angle = 90;
        xQueueSend(message_queue, &set_angle, 10);
    } else if (key == 2) {
        set_angle = 180;
        xQueueSend(message_queue, &set_angle, 10);
    }

    return;
}
