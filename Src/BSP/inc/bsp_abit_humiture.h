#ifndef __BSP_ABIT_HUMITURE_H
#define __BSP_ABIT_HUMITURE_H

#include "bsp_abit_delay.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define DH11_DATA_PIN       GPIO_Pin_6

typedef struct 
{
    uint8_t Humid_Int;
    uint8_t Humid_Dec;
    uint8_t Temp_Int;
    uint8_t Temp_Dec;
    uint8_t Check_CRC;
}Humiture_InitTypeDef;

// void bsp_abit_humiture_config();

uint8_t bsp_abit_dh11_read_data(Humiture_InitTypeDef *humiture);

static uint8_t bsp_abit_dh11_read_byte();

static void bsp_abit_dh11_pin_set_input();

static void bsp_abit_dh11_pin_set_output();

#endif //__BSP_ABIT_HUMITURE_H