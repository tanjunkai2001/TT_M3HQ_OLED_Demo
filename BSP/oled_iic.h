#ifndef __OLED_IIC_H__
#define __OLED_IIC_H__

#include "bsp.h" 

//SDA - PN2
//SCL - PN4

#define OLED_IIC_SDA_PORT       GPIO_PORT_N
#define OLED_IIC_SCL_PORT       GPIO_PORT_N

#define OLED_IIC_SDA_PIN    GPIO_PORT_2
#define OLED_IIC_SCL_PIN    GPIO_PORT_4

#define OLED_IIC_SCL_OUTPUT_FUN     GPIO_PN4_OUTPUT

#define OLED_IIC_SDA_INPUT_FUN     GPIO_PN2_INPUT
#define OLED_IIC_SDA_OUTPUT_FUN    GPIO_PN2_OUTPUT
//�����������ģʽ
#define OLED_SDA_IN()   gpio_func(&port, OLED_IIC_SDA_PORT, OLED_IIC_SDA_PIN, OLED_IIC_SDA_INPUT_FUN, GPIO_PIN_INPUT)   //����ģʽ
#define OLED_SDA_OUT()  gpio_func(&port, OLED_IIC_SDA_PORT, OLED_IIC_SDA_PIN, OLED_IIC_SDA_OUTPUT_FUN, GPIO_PIN_OUTPUT)

//λ����ʽ����IO
#define OLED_IIC_SCL    PNout(4) //SCL
#define OLED_IIC_SDA    PNout(2) //SDA	 
#define OLED_READ_SDA   PNin(2)  //����SDA 

//IIC���в�������
void OLED_IIC_Init(void);                //��ʼ��IIC��IO��				 
void OLED_IIC_Start(void);				//����IIC��ʼ�ź�
void OLED_IIC_Stop(void);	  			//����IICֹͣ�ź�
void OLED_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 OLED_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 OLED_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void OLED_IIC_Ack(void);					//IIC����ACK�ź�
void OLED_IIC_NAck(void);				//IIC������ACK�ź�

void OLED_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 OLED_IIC_Read_One_Byte(u8 daddr,u8 addr);	  

#endif




