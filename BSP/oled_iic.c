#include "oled_iic.h"
#include "bsp.h"
//SDA - PA12
//SCL - PA11
gpio_t port;

//��ʼ��IIC
void OLED_IIC_Init(void)
{
    port.p_pn_instance = TSB_PN;        //PNʱ��ʹ��
    
    gpio_init(&port, OLED_IIC_SDA_PORT);  
    gpio_init(&port, OLED_IIC_SCL_PORT);  

    gpio_func(&port, OLED_IIC_SDA_PORT, OLED_IIC_SDA_PIN, OLED_IIC_SDA_OUTPUT_FUN, GPIO_PIN_OUTPUT);   
    gpio_func(&port, OLED_IIC_SCL_PORT, OLED_IIC_SCL_PIN, OLED_IIC_SCL_OUTPUT_FUN, GPIO_PIN_OUTPUT);  

    OLED_IIC_SCL = 1;
    OLED_IIC_SDA = 1;
}
//����IIC��ʼ�ź�
void OLED_IIC_Start(void)
{
    OLED_SDA_OUT();     //sda�����
    OLED_IIC_SDA = 1;
    OLED_IIC_SCL = 1;
    delay_us(4);
    OLED_IIC_SDA = 0; //START:when CLK is high,DATA change form high to low
    delay_us(4);
    OLED_IIC_SCL = 0; //ǯסI2C���ߣ�׼�����ͻ��������
}
//����IICֹͣ�ź�
void OLED_IIC_Stop(void)
{
    OLED_SDA_OUT();//sda�����
    OLED_IIC_SCL = 0;
    OLED_IIC_SDA = 0; //STOP:when CLK is high DATA change form low to high
    delay_us(4);
    OLED_IIC_SCL = 1;
    OLED_IIC_SDA = 1; //����I2C���߽����ź�
    delay_us(4);
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 OLED_IIC_Wait_Ack(void)
{
    u8 ucErrTime = 0;
    OLED_SDA_IN();      //SDA����Ϊ����
    OLED_IIC_SDA = 1;
    delay_us(1);
    OLED_IIC_SCL = 1;
    delay_us(1);
    while(OLED_READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime > 250)
        {
            OLED_IIC_Stop();
            return 1;
        }
    }
    OLED_IIC_SCL = 0; //ʱ�����0
    return 0;
}
//����ACKӦ��
void OLED_IIC_Ack(void)
{
    OLED_IIC_SCL = 0;
    OLED_SDA_OUT();
    OLED_IIC_SDA = 0;
    delay_us(2);
    OLED_IIC_SCL = 1;
    delay_us(2);
    OLED_IIC_SCL = 0;
}
//������ACKӦ��
void OLED_IIC_NAck(void)
{
    OLED_IIC_SCL = 0;
    OLED_SDA_OUT();
    OLED_IIC_SDA = 1;
    delay_us(2);
    OLED_IIC_SCL = 1;
    delay_us(2);
    OLED_IIC_SCL = 0;
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void OLED_IIC_Send_Byte(u8 txd)
{
    u8 t;
    OLED_SDA_OUT();
    OLED_IIC_SCL = 0; //����ʱ�ӿ�ʼ���ݴ���
    for(t = 0; t < 8; t++)
    {
        OLED_IIC_SDA = (txd & 0x80) >> 7;
        txd <<= 1;
        delay_us(2);  
        OLED_IIC_SCL = 1;
        delay_us(2);
        OLED_IIC_SCL = 0;
        delay_us(2);
    }
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
u8 OLED_IIC_Read_Byte(unsigned char ack)
{
    unsigned char i, receive = 0;
    OLED_SDA_IN();//SDA����Ϊ����
    for(i = 0; i < 8; i++)
    {
        OLED_IIC_SCL = 0;
        delay_us(2);
        OLED_IIC_SCL = 1;
        receive <<= 1;
        if(OLED_READ_SDA)receive++;
        delay_us(1);
    }
    if(!ack)
        OLED_IIC_NAck();//����nACK
    else
        OLED_IIC_Ack(); //����ACK
    return receive;
}




