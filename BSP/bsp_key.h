#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include "bsp.h"

#define KEY_PORT       GPIO_PORT_V
#define KEY_PIN        GPIO_PORT_3
#define KEY_FUN        GPIO_PV3_INPUT

//λ��������ʽ��ȡ���룬�������ַ�ʽ��һ��
//#define KEY_IN      READ_PIN(KEY_PORT, KEY_PIN)
#define KEY_IN      PVin(3)

void KEY_Init(void);
gpio_pinstate_t Get_Key(void);


#endif
