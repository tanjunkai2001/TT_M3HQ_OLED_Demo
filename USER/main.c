#include "main.h"

int main(void)
{
    uint8_t month = 9, day = 13, week = 5;
    uint8_t hour = 22, minute = 28, second = 11;

    delay_init();      //��ʱ������ʼ��
    LED_Init();         //LED��ʼ��
    KEY_Init();         //������ʼ��
    OLED_Init();        //OLED��ʼ��
    SW_Init();          //���뿪�س�ʼ��
    
    UART0_Init(115200);
    LOG("\r\nTT_M3HQ %s %s", __DATE__, __TIME__);
    
    Display_LOGO();
    OLED_DisTime(hour,minute,second);     //��ʾʱ��
    OLED_DisDate(month,day,week);       //��ʾ����
    
    while(1)
    {
        delay_ms(80);
        second++;
        if(second >= 60)
        {
            minute++;
            second = 0;
        }
        if(minute >= 60)
        {
            hour++;
            minute = 0;
        }
        OLED_DisTime(hour, minute, second);
        LOG("Now: %d-%d ����%d %d:%d:%d  %d \r\n", month, day, week, hour, minute, second, Get_SW());
        /*
        //��������LED��˸
        if(KEY_IN == GPIO_PIN_RESET)
        {
            PKout(4) = 1;   //����  PORTx_SET(GPIO_PORT_K, 4);
            PKout(5) = 1;
            PKout(6) = 1;
            PKout(7) = 1;
            delay_ms(50);
            LOG("\r\nTT_M3HQ %s %s", __DATE__, __TIME__);

            PORTx_CLR(GPIO_PORT_K, 4);  //Ϩ�� PKout(4)=0
            PORTx_CLR(GPIO_PORT_K, 5);
            PORTx_CLR(GPIO_PORT_K, 6);
            PORTx_CLR(GPIO_PORT_K, 7);
            delay_ms(50);
        }*/
    }
}
