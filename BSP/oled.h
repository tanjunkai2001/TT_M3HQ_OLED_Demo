#ifndef __OLED_H__
#define __OLED_H__

#include "bsp.h"

void OLED_WriteCmd(u8 command);
void OLED_WriteData(u8 data);
void OLED_WriteData2(u8 data);
void OLED_Init(void);
void OLED_ON(void);
void OLED_SetCursor(unsigned char x, unsigned char y); //������ʼ������
void OLED_Fill(unsigned char fill_Data);//ȫ�����
void OLED_CLS(void);//����
void OLED_Clear(void);		//ȫ���Ǻ�ɫ��.û�е���
void OLED_SetContrast(u8 con);

void OLED_DrawBMP(u8 x0, u8 y0, u8 x1, u8 y1,const u8 BMPx[]);
void Display_LOGO(void);

//8*16�ַ���ʾ����
void OLED_DisChar_F8X16(u8 x, u8 y, u8 ch);		
void OLED_CharInverse_F8X16(u8 x, u8 y, u8 ch);		//�ַ�����
void OLED_CharBlink_F8X16(u8 x, u8 y, u8 ch);		//�ַ���˸
void OLED_DisNumber_F8X16(u8 x, u8 y, u8 num);
void OLED_NumberInverse_F8X16(u8 x, u8 y, u8 num);	//��λ���ַ���
void OLED_NumberBlink_F8X16(u8 x, u8 y, u8 num);	//��λ������˸
void OLED_DisString_F8X16(u8 x, u8 y, u8 *str);
void OLED_DisBlack_F8X16(u8 x, u8 y);				//ָ��λ����ʾ�ַ��ڿ�
void OLED_DisWhite_F8X16(u8 x, u8 y);				//ָ��λ����ʾ�ַ��׿�
void OLED_ShowNumber_F8X16(u8 x, u8 y, u32 num, u8 n);

//6*8�ַ���ʾ����
void OLED_DisChar_F6X8(u8 x,u8 y,u8 ch);
void OLED_DisString_F6X8(u8 x,u8 y,u8 *str);
void OLED_DisNumber_F6X8(u8 x,u8 y,u8 num);
void OLED_ShowNumber_F6X8(u8 x, u8 y, u32 num, u8 n);

//16*32�ַ���ʾ����

void OLED_DisChar_F16X32(u8 x, u8 y, u8 ch);
void OLED_DisString_F16X32(u8 x, u8 y, u8 *str);
void OLED_DisNumber_F16X32(u8 x, u8 y, u8 num);

void OLED_Set_Pos(u8 x, u8 y); 			//������ʾר���������꺯��
void OLED_DisChinese(u8 x, u8 y, u8 CHN);


void Draw_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);

/******ʱ����ʾ���*****/
void OLED_DisTime(u8 hour, u8 min, u8 sec);
void OLED_DisDate(u8 mon, u8 day, u8 week);


#endif




