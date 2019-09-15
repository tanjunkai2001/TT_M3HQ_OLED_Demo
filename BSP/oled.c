#include "oled.h"
#include "oled_iic.h"

#include "oled_font.h"

void OLED_WriteCmd(u8 command)
{
    OLED_IIC_Start();
    OLED_IIC_Send_Byte(0x78);//OLED��ַ
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(0x00);//�Ĵ�����ַ
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(command);
    OLED_IIC_Wait_Ack();
    OLED_IIC_Stop();
}

void OLED_WriteData(u8 data)
{
    OLED_IIC_Start();
    OLED_IIC_Send_Byte(0x78);//OLED��ַ
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(0x40);//�Ĵ�����ַ
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(data);
    OLED_IIC_Wait_Ack();
    OLED_IIC_Stop();
}
void OLED_WriteData2(u8 data)
{
    OLED_IIC_Start();
    OLED_IIC_Send_Byte(0x78);//OLED��ַ
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(0x40);//�Ĵ�����ַ
    OLED_IIC_Wait_Ack();
    OLED_IIC_Send_Byte(~data);
    OLED_IIC_Wait_Ack();
    OLED_IIC_Stop();
}
//���öԱȶ�
void OLED_SetContrast(u8 con)
{
    OLED_WriteCmd(0x81);	 //�Աȶ�����
    OLED_WriteCmd(con); 	 //1~255;Ĭ��0X7F (��������,Խ��Խ��)
}



void OLED_Clear(void)		//ȫ���Ǻ�ɫ��.û�е���
{
    u8 i, n;
    for(i = 0; i < 8; i++)
    {
        OLED_WriteCmd (0xb0 + i); //����ҳ��ַ��0~7��
        OLED_WriteCmd (0x00);     //������ʾλ�á��е͵�ַ
        OLED_WriteCmd (0x10);     //������ʾλ�á��иߵ�ַ
        for(n = 0; n < 128; n++)	//ÿ��128����
            OLED_WriteData(0);		//Ϩ�����ص�
    }
}
void OLED_Init(void)
{
	OLED_IIC_Init();

//    delay_ms(100); 

    OLED_WriteCmd(0xAE); //�ر���ʾ
    OLED_WriteCmd(0xD5); //����ʱ�ӷ�Ƶ����,��Ƶ��
    OLED_WriteCmd(0x80);  //[3:0],��Ƶ����;[7:4],��Ƶ��
    OLED_WriteCmd(0xA8); //��������·��
    OLED_WriteCmd(0X3F); //Ĭ��0X3F(1/64)
    OLED_WriteCmd(0xD3); //������ʾƫ��
    OLED_WriteCmd(0X00); //Ĭ��Ϊ0
    OLED_WriteCmd(0x40); //������ʾ��ʼ�� [5:0],����.
    OLED_WriteCmd(0x8D); //��ɱ�����
    OLED_WriteCmd(0x14); //bit2������/�ر�
    OLED_WriteCmd(0x20); //�����ڴ��ַģʽ
    OLED_WriteCmd(0x02); //[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
    OLED_WriteCmd(0xA1); //0xa0���ҷ��� 0xa1����
    OLED_WriteCmd(0xC8); //0xc0���·��� 0xc8����
    OLED_WriteCmd(0xDA); //����COMӲ����������
    OLED_WriteCmd(0x12); //[5:4]����
    OLED_WriteCmd(0x81); //�Աȶ�����
    OLED_WriteCmd(0x7f); //1~255;Ĭ��0X7F (��������,Խ��Խ��)
    OLED_WriteCmd(0xD9); //����Ԥ�������
    OLED_WriteCmd(0xf1); //[3:0],PHASE 1;[7:4],PHASE 2;
    OLED_WriteCmd(0xDB); //����VCOMH ��ѹ����
    OLED_WriteCmd(0x30); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
    OLED_WriteCmd(0xA4); //ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
    OLED_WriteCmd(0xA6); //������ʾ��ʽ;bit0:1-0xa7������ʾ;0xa6������ʾ
    OLED_WriteCmd(0xAF); //������ʾ

    OLED_Clear();
    OLED_SetCursor(0, 0);
}

void OLED_ON(void)
{
    OLED_WriteCmd(0X8D);  //���õ�ɱ�
    OLED_WriteCmd(0X14);  //������ɱ�
    OLED_WriteCmd(0XAF);  //OLED����
}


/**
 * @brief  OLED_SetCursor�����ù��
 * @param  x,���xλ��
   *                   y�����yλ��
 * @retval ��
 */
void OLED_SetCursor(unsigned char x, unsigned char y) //������ʼ������
{
    OLED_WriteCmd(0xb0 + (y >> 3));
//    OLED_WriteCmd(0xb0 + y);
    OLED_WriteCmd(((x & 0xf0) >> 4) | 0x10);
    OLED_WriteCmd((x & 0x0f) | 0x01);
}

/**
 * @brief  OLED_Fill�����������Ļ
 * @param  fill_Data:Ҫ��������
   * @retval ��
 */
void OLED_Fill(unsigned char fill_Data)//ȫ�����
{
    unsigned char m, n;
    for(m = 0; m < 8; m++)
    {
        OLED_WriteCmd(0xb0 + m);     //page0-page1
        OLED_WriteCmd(0x00);     //low column start address
        OLED_WriteCmd(0x10);     //high column start address
        for(n = 0; n < 128; n++)
        {
            OLED_WriteData(fill_Data);
        }
    }
}

void OLED_CLS(void)//����
{
    OLED_Fill(0x00);
}

#if 1		//16*32���֣�����������ʾ
//��ʾ�ַ�,16*32����,x��0-127��y��0-63
void OLED_DisChar_F16X32(u8 x, u8 y, u8 ch)
{
    u8 c, i;
	if(ch == ':')
		c = 10;
	else
		c = ch - '0';		//��ַƫ��
    //һ����ʾ�ķ�֮һ
	OLED_SetCursor(x, y);		//��1/4
    for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i]);			
	OLED_SetCursor(x, y+8);
	for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i+16]);	//��2/4
		OLED_SetCursor(x, y+16);
	for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i+32]);	//2/4
	OLED_SetCursor(x, y+24);
	for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i+48]);	//��2/4
/*	
	//��̬Ч��
	OLED_SetCursor(x, y+16);
	for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i+32]);	//2/4
	OLED_SetCursor(x, y+24);
	for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i+48]);	//��2/4
	delay_ms(105);
	
	OLED_SetCursor(x, y);		//��1/4
    for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i]);			
	OLED_SetCursor(x, y+8);
	for(i = 0; i < 16; i++)		
        OLED_WriteData(F16X32[c][i+16]);	//��2/4
	*/
}
/*��ʾ�ַ���,16X32����*/
void OLED_DisString_F16X32(u8 x, u8 y, u8 *str)
{
    while (*str != '\0')
    {
        OLED_DisChar_F16X32(x, y, *str++);
        x += 16;
    }
}
/*��ʾ��λ���֣�8X16���壬x��0-14��y��0-3*/
void OLED_DisNumber_F16X32(u8 x, u8 y, u8 num)
{
    //�����ַ�������ʾ
    OLED_DisChar_F16X32(x, y, num / 10 + 0x30);
    OLED_DisChar_F16X32(x + 16, y, num % 10 + 0x30);
}

#endif



#if 1		//8x16����,����������ʾ,x��0-15��y��0-3

//��ʾ�ַ�,8*16����,x��0-15��y��0-3
void OLED_DisChar_F8X16(u8 x, u8 y, u8 ch)
{
    u8 c, i;
    c = ch - ' ';
    OLED_SetCursor(x * 8, y * 16);
    for(i = 0; i < 8; i++)					//��ʾ�ϰ벿��8*8
        OLED_WriteData(F8X16[c][i]);		//ÿһ�е�ǰ8��
    OLED_SetCursor(x * 8, y * 16 + 8);			//��ʾ�°벿��8*8
    for(i = 0; i < 8; i++)
        OLED_WriteData(F8X16[c][i + 8]);	//ÿһ�еĺ�8��
}
//��ʾ8*16�ַ�����,x��0-15��y��0-3
void OLED_CharInverse_F8X16(u8 x, u8 y, u8 ch)
{
    u8 c, i;
    c = ch - ' ';
    OLED_SetCursor(x * 8, y * 16);
    for(i = 0; i < 8; i++)
        OLED_WriteData2(F8X16[c][i]);
    OLED_SetCursor(x * 8, y * 16 + 8);
    for(i = 0; i < 8; i++)
        OLED_WriteData2(F8X16[c][i + 8]);
}
//��ʾ8x16�ַ���˸
void OLED_CharBlink_F8X16(u8 x, u8 y, u8 ch)
{
    OLED_CharInverse_F8X16(x, y, ch);
    delay_ms(400);
    OLED_DisChar_F8X16(x, y, ch);
    delay_ms(400);
}
//��ʾ��λ���֣�8X16���壬x��0-14��y��0-3
void OLED_DisNumber_F8X16(u8 x, u8 y, u8 num)
{
    //�����ַ�������ʾ
    OLED_DisChar_F8X16(x, y, num / 10 + 0x30);
    OLED_DisChar_F8X16(x + 1, y, num % 10 + 0x30);

}
void OLED_ShowNumber_F8X16(u8 x, u8 y, u32 num, u8 n)
{
	u8 i;
	for( i = 0; i < n; i++)
	{
		OLED_DisChar_F8X16(x + n-1, y, num % 10 + 0x30);
		num = num / 10;
		x--;
	}
}


//��ʾ��λ���ַ���,8*16����,x��0-14��y��0-3
void OLED_NumberInverse_F8X16(u8 x, u8 y, u8 num)
{
    OLED_CharInverse_F8X16(x, y, num / 10 + 0x30);
    OLED_CharInverse_F8X16(x + 1, y, num % 10 + 0x30);
}
//��ʾ��λ������˸:�����ͷ��Խ���
void OLED_NumberBlink_F8X16(u8 x, u8 y, u8 num)
{
    OLED_NumberInverse_F8X16(x, y, num);
    delay_ms(100);
    OLED_DisNumber_F8X16(x, y, num);
    delay_ms(100);
}
//��ʾ�ַ���,8X16���壬x��0-15��y��0-3
void OLED_DisString_F8X16(u8 x, u8 y, u8 *str)
{
    while (*str != '\0')
    {
        OLED_DisChar_F8X16(x, y, *str++);
        x++;
    }
}
//ָ��λ����ʾ8*16�ڿ��ַ�
void OLED_DisBlack_F8X16(u8 x, u8 y)		//ָ��λ����ʾ�ַ��ڿ�
{
    u8 i;
    OLED_SetCursor(x * 8, y * 16);
    for(i = 0; i < 8; i++)
        OLED_WriteData(0);			//Ϩ�����ص�
    OLED_SetCursor(x * 8, y * 16 + 8);
    for(i = 0; i < 8; i++)
        OLED_WriteData(0);
}
//ָ��λ����ʾ8*16�׿��ַ�
void OLED_DisWhite_F8X16(u8 x, u8 y)		//ָ��λ����ʾ�ַ��׿�
{
    u8 i;
    OLED_SetCursor(x * 8, y * 16);
    for(i = 0; i < 8; i++)
        OLED_WriteData2(0);			//�������ص�
    OLED_SetCursor(x * 8, y * 16 + 8);
    for(i = 0; i < 8; i++)
        OLED_WriteData2(0);
}
#endif


#if 0		//8x16����,����������ʾ,x��0-127��y��0-63

/*��ʾ�ַ�,8X16����,x��0-127��y��0-63*/
void OLED_DisChar_F8X16(u8 x, u8 y, u8 ch)
{
    u8 c, i;
    c = ch - ' ';		//��ַƫ��
    OLED_SetCursor(x, y);
    for(i = 0; i < 8; i++)		//��ʾ�ϰ벿��8*8
        OLED_WriteData(F8X16[c][i]);			//ÿһ�е�ǰ8��
    OLED_SetCursor(x, y + 8);		//��ʾ�°벿��8*8
    for(i = 0; i < 8; i++)
        OLED_WriteData(F8X16[c][i + 8]);		//ÿһ�еĺ�8��
}
void OLED_DisString_F8X16(u8 x, u8 y, u8 *str)
{
    while (*str != '\0')
    {
        OLED_DisChar_F8X16(x, y, *str++);
        x += 8;
    }
}
/*��ʾ��λ���֣�8X16���壬x��0-14��y��0-3*/
void OLED_DisNumber_F8X16(u8 x, u8 y, u8 num)
{
    //�����ַ�������ʾ
    OLED_DisChar_F8X16(x, y, num / 10 + 0x30);
    OLED_DisChar_F8X16(x + 8, y, num % 10 + 0x30);
}

#endif



void OLED_Set_Pos(u8 x, u8 y)	 //������ʾ��������ʾ����
{
    OLED_WriteCmd(0xb0 + y);
    OLED_WriteCmd(((x & 0xf0) >> 4) | 0x10);
    OLED_WriteCmd((x & 0x0f) | 0x01);
}
void OLED_DisChinese(u8 x, u8 y, u8 Num)
{
	u8 i;
    OLED_SetCursor(x, y);
    for(i = 0; i < 16; i++)
        OLED_WriteData(CHN[Num][i]);	
	
    OLED_SetCursor(x, y + 8);
    for(i = 0; i < 16; i++)
        OLED_WriteData(CHN[Num][i + 16]);
}

#if 1		//6x8����,��������,x��0-20��y��0-7

/*��ʾ�ַ���6X8���壬x��0-20��y��0-7*/
void OLED_DisChar_F6X8(u8 x, u8 y, u8 ch)
{
    u8 c = 0, i = 0;
    c = ch - ' ';
    OLED_SetCursor(x * 6, y * 8);
    for(i = 0; i < 6; i++)
        OLED_WriteData(F6X8[c][i]);
}
/*��ʾ�ַ�����6X8����,���Ȳ��ܳ���21���ַ�*/
void OLED_DisString_F6X8(u8 x, u8 y, u8 *str)
{
    while (*str != '\0')
    {
        OLED_DisChar_F6X8(x, y, *str++);
        x++;
    }
}
/*��ʾ��λ����,6X8����,x��0-19��y:0-7*/
void OLED_DisNumber_F6X8(u8 x, u8 y, u8 num)
{
    //�����ַ�������ʾ
    OLED_DisChar_F6X8(x, y, num / 10 + 0x30);
    OLED_DisChar_F6X8(x + 1, y, num % 10 + 0x30);

}
void OLED_ShowNumber_F6X8(u8 x, u8 y, u32 num, u8 n)
{
	u8 i;
	for( i = 0; i < n; i++)
	{
		OLED_DisChar_F6X8(x + n-1, y, num % 10 + 0x30);
		num = num / 10;
		x--;
	}
}
#endif

#if 0		//6x8����,����������ʾ,x��0-127��y��0-63

/*��ʾ�ַ���6X8���壬x��0-127��y��0-36*/
void OLED_DisChar_F6X8(u8 x, u8 y, u8 ch)
{
    u8 c = 0, i = 0;
    c = ch - ' ';
    OLED_SetCursor(x, y);
    for(i = 0; i < 6; i++)
        OLED_WriteData(F6X8[c][i]);
}
/*��ʾ�ַ�����6X8����,���Ȳ��ܳ���21���ַ�*/
void OLED_DisString_F6X8(u8 x, u8 y, u8 *str)
{
    while (*str != '\0')
    {
        OLED_DisChar_F6X8(x, y, *str++);
        x += 6;
    }
}
/*��ʾ��λ����,6X8����,x��0-19��y:0-7*/
void OLED_DisNumber_F6X8(u8 x, u8 y, u8 num)
{
    //�����ַ�������ʾ
    OLED_DisChar_F6X8(x, y, num / 10 + 0x30);
    OLED_DisChar_F6X8(x + 6, y, num % 10 + 0x30);
}

#endif


void Display_LOGO(void)
{
    u8 n;

    OLED_DrawBMP(0, 0, 128, 8, TOSHIBA);    //��֥LOGOȫ����ʾ

    OLED_DisString_F8X16(0, 3, "Starting...");  
    for( n = 5; n > 0; n--)
    {
        OLED_DisNumber_F8X16(12, 3, n);     //��������ʱ
        delay_ms(800);
    }
    OLED_Clear();//����
	OLED_DrawBMP(0, 0, 128, 8, TT_M3HQ);    //TT_M3HQȫ����ʾ
    delay_ms(200);
    OLED_Clear();//����
	OLED_DrawBMP(0, 0, 128, 8, THUNDER);    //�пƴ���LOGOȫ����ʾ
    delay_ms(200);
    OLED_Clear();//����
	OLED_DrawBMP(0, 0, 128, 8, MBB);        //���������LOGOȫ����ʾ
    delay_ms(800);
    OLED_Clear();//����
	OLED_DrawBMP(0, 0, 128, 2, BAR);	    //��1/4���ֻ�״̬����ʾ	
}

//��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��8
void OLED_DrawBMP(u8 x0, u8 y0, u8 x1, u8 y1,const u8 BMPx[])
{
    u16 j = 0;
    u8 x, y;

    if(y1 % 8 == 0) y = y1 / 8;
    else y = y1 / 8 + 1;
    for(y = y0; y < y1; y++)
    {
        OLED_Set_Pos(x0, y);
        for(x = x0; x < x1; x++)
        {
            OLED_WriteData(BMPx[j++]);
        }
    }
}

void OLED_DisTime(u8 hour, u8 min, u8 sec)
{
	OLED_DisNumber_F16X32(0, 32, hour);
	OLED_DisChar_F16X32(32, 32, ':');  //:
	OLED_DisNumber_F16X32(48, 32, min);
	OLED_DisChar_F16X32(80, 32, ':');  //:
	OLED_DisNumber_F16X32(96, 32, sec);	
}


void OLED_DisDate(u8 mon, u8 day, u8 week)
{
	u8 date_tmp[10];
	sprintf((char *)date_tmp, "%d/%d", mon, day);
	OLED_DisString_F8X16(0, 1, "     ");

	OLED_DisString_F8X16(0, 1, date_tmp);
	OLED_DisChinese(96 + 16, 16, week);	//����"��"

}
