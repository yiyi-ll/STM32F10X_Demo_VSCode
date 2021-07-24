#include "bsp_abit_humiture.h"

// void bsp_abit_humiture_config()
// {
//     GPIO_InitTypeDef GPIO_InitStruct;

//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

//     GPIO_InitStruct.GPIO_Pin = DH11_DATA_PIN;
//     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

//     GPIO_Init(GPIOE, &GPIO_InitStruct);

//     GPIO_SetBits(GPIOE, DH11_DATA_PIN);
// }

uint8_t bsp_abit_dh11_read_data(Humiture_InitTypeDef *humiture)
{
    uint8_t val[5] = {0x00, };
    uint8_t i = 0;

    bsp_abit_dh11_pin_set_output();
    GPIO_ResetBits(GPIOE, DH11_DATA_PIN);
    bsp_abit_delay_ms(20);
    GPIO_SetBits(GPIOE, DH11_DATA_PIN);
    bsp_abit_delay_us(30);

    bsp_abit_dh11_pin_set_input();

    if(GPIO_ReadInputDataBit(GPIOE, DH11_DATA_PIN) == 0)
    {
        while(GPIO_ReadInputDataBit(GPIOE, DH11_DATA_PIN) == 0);

        while(GPIO_ReadInputDataBit(GPIOE, DH11_DATA_PIN) == 1);

        for(i = 0; i < 5; i++)
        {
            val[i] = bsp_abit_dh11_read_byte();
        }

        bsp_abit_dh11_pin_set_output();
        GPIO_SetBits(GPIOE, DH11_DATA_PIN);

        if(val[0] + val[1] + val[2] + val[3] == val[4])
        {
            humiture->Humid_Int = val[0];
            humiture->Humid_Dec = val[1];
            humiture->Temp_Int = val[2];
            humiture->Temp_Dec = val[3];

            return 0;
        }
        else
            return 1;
    }

    else
        return 1;
}

static uint8_t bsp_abit_dh11_read_byte()
{
    uint8_t i = 0;
    uint8_t byte = 0;

    for(i = 0; i < 8; i++)
    {
        byte <<= 1;
        while(GPIO_ReadInputDataBit(GPIOE, DH11_DATA_PIN) == 0);

        bsp_abit_delay_us(40);

        if(GPIO_ReadInputDataBit(GPIOE, DH11_DATA_PIN) == 1)
        {
            while(GPIO_ReadInputDataBit(GPIOE, DH11_DATA_PIN) == 1);
            byte |= 1;
        }
    }
    return byte;
}

static void bsp_abit_dh11_pin_set_input()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Pin = DH11_DATA_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
}

static void bsp_abit_dh11_pin_set_output()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Pin = DH11_DATA_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStruct);
}