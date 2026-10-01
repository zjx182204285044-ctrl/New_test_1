// #include "lcd.h"
// #include "cfont.h"
// #include "mytim.h"
// extern float p;
// float pid_x_=0,pid_y_=0;
// int kind1=0;
// short pressure;
// extern int a;
// int value_AD;
// int VOLTAGE_AO;
// /*********************************************************************************
// *******************************STM32F407Ӧ�ÿ�����(�����)************************
// **********************************************************************************
// * �ļ�����: lcd.c                                                                *
// * �ļ�������LCD��ʾ��������                                                      *
// * �������ڣ�2016.10.08                                                           *
// * ��    ����V1.0                                                                 *
// * ��    �ߣ�Clever                                                               *
// * ˵    ����������֧����Ļ����ΪILI9341��SSD1963                                 *
// *           RA8875����ģ�����������RA8875��Ļ�����е�LCD�����ļ����滻�����̵�  *
//             LCD�ļ��У����±��뼴��                                              *
// **********************************************************************************
// *********************************************************************************/



// //��ʼ��LCD�Ļ�����ɫ�ͱ���ɫ
// u16 BRUSH_COLOR = BLACK;	//������ɫ
// u16 BACK_COLOR = WHITE; //����ɫ

// //LCD��������
// u16  lcd_id;          //LCD ID
// u8   dir_flag;        //�������������ƣ�0��������1������
// u16  lcd_width;       //LCD�Ŀ���
// u16  lcd_height;      //LCD�ĸ߶�
// u16	 write_gramcmd;		//дgramָ��
// u16  setxcmd;		      //����x����ָ��
// u16  setycmd;		      //����y����ָ��

// /****************************************************************************
// * ��    ��: void LCD_WriteReg(u16 LCD_Reg, u16 LCD_Value)
// * ��    �ܣ�LCDд�Ĵ���
// * ��ڲ�����LCD_Reg: �Ĵ�����ַ
// *           LCD_RegValue: Ҫд�������
// * ���ز�������
// * ˵    ����
// ****************************************************************************/
// void LCD_WriteReg(u16 LCD_Reg, u16 LCD_Value)
// {
//     LCD_CMD = LCD_Reg;		 //д��Ҫд�ļĴ������
//     LCD_DATA = LCD_Value;  //��Ĵ���д�������
// }

// /****************************************************************************
// * ��    ��: u16 LCD_ReadReg(u16 LCD_Reg)
// * ��    �ܣ�LCD���Ĵ���
// * ��ڲ�����LCD_Reg:�Ĵ�����ַ
// * ���ز����������üĴ���������ֵ
// * ˵    ����
// ****************************************************************************/
// u16 LCD_ReadReg(u16 LCD_Reg)
// {
//     LCD_CMD = LCD_Reg;		//д��Ҫ���ļĴ������
//     delay_us(4);
//     return LCD_DATA;		//���ض�����ֵ
// }

// //lcd��ʱ����
// void lcdm_delay(u8 i)
// {
//     while(i--);
// }

// //��ʼдGRAM
// void LCD_WriteGRAM(void)
// {
//     LCD_CMD = write_gramcmd;
// }

// //LCD������ʾ
// void LCD_DisplayOn(void)
// {
//     LCD_CMD = 0x29; //9341��1963����ʾ����һ��
// }

// //LCD�ر���ʾ
// void LCD_DisplayOff(void)
// {
//     LCD_CMD = 0x28; //9341��1963����ʾ����һ��
// }

// /****************************************************************************
// * ��    ��: void LCD_Open_Window(u16 X0,u16 Y0,u16 width,u16 height)
// * ��    �ܣ�������,�����û������굽�������Ͻ�(X0,Y0)
// * ��ڲ�����X0,Y0:������ʼ����(���Ͻ�)
//             width,height:���ڿ��Ⱥ͸߶�
// * ���ز�������
// * ˵    ���������С:width*height.?B
// ****************************************************************************/
// void LCD_Open_Window(u16 X0, u16 Y0, u16 width, u16 height)
// {
//     width = X0 + width - 1; //������½�����
//     height = Y0 + height - 1;

//     if(dir_flag == 0 && lcd_id == 0X1963) //1963��������
//     {
//         X0 = lcd_width - width - X0;
//         height = Y0 + height - 1;
//         LCD_CMD = setxcmd;
//         LCD_DATA = X0 >> 8;
//         LCD_DATA = X0 & 0XFF;
//         LCD_DATA = (X0 + width - 1) >> 8;
//         LCD_DATA = (X0 + width - 1) & 0XFF;
//         LCD_CMD = setycmd;
//         LCD_DATA = Y0 >> 8;
//         LCD_DATA = Y0 & 0XFF;
//         LCD_DATA = height >> 8;
//         LCD_DATA = height & 0XFF;
//     }
//     else
//     {
//         LCD_CMD = setxcmd;
//         LCD_DATA = X0 >> 8;
//         LCD_DATA = X0 & 0XFF;
//         LCD_DATA = width >> 8;
//         LCD_DATA = width & 0XFF;
//         LCD_CMD = setycmd;
//         LCD_DATA = Y0 >> 8;
//         LCD_DATA = Y0 & 0XFF;
//         LCD_DATA = height >> 8;
//         LCD_DATA = height & 0XFF;
//     }
// }

// /****************************************************************************
// * ��    ��: void Set_Scan_Direction(u8 direction)    ������#������
// * ��    �ܣ�����LCD��ɨ�跽��
// * ��ڲ�����direction��ɨ�跽��
// * ���ز�������
// * ˵    ����
// ****************************************************************************/
// void Set_Scan_Direction(u8 direction)
// {
//     u16 skhda = 0;
//     u16 diomf = 0;

//     //9341������1963����ʱ��Ҫת����
//     if( (dir_flag == 1 && lcd_id == 0X9341) || (dir_flag == 0 && lcd_id == 0X1963))
//     {
//         switch(direction)//����ת��
//         {
//             case 0:
//                 direction = 6;
//                 break;

//             case 1:
//                 direction = 7;
//                 break;

//             case 2:
//                 direction = 4;
//                 break;

//             case 3:
//                 direction = 5;
//                 break;

//             case 4:
//                 direction = 1;
//                 break;

//             case 5:
//                 direction = 0;
//                 break;

//             case 6:
//                 direction = 3;
//                 break;

//             case 7:
//                 direction = 2;
//                 break;
//         }
//     }

//     switch(direction)
//     {
//         case L2R_U2D:   //������,���ϵ���
//             skhda |= (0 << 7) | (0 << 6) | (0 << 5);
//             break;

//         case L2R_D2U:   //������,���µ���
//             skhda |= (1 << 7) | (0 << 6) | (0 << 5);
//             break;

//         case R2L_U2D:   //���ҵ���,���ϵ���
//             skhda |= (0 << 7) | (1 << 6) | (0 << 5);
//             break;

//         case R2L_D2U:   //���ҵ���,���µ���
//             skhda |= (1 << 7) | (1 << 6) | (0 << 5);
//             break;

//         case U2D_L2R:   //���ϵ���,������
//             skhda |= (0 << 7) | (0 << 6) | (1 << 5);
//             break;

//         case U2D_R2L:   //���ϵ���,���ҵ���
//             skhda |= (0 << 7) | (1 << 6) | (1 << 5);
//             break;

//         case D2U_L2R:   //���µ���,������
//             skhda |= (1 << 7) | (0 << 6) | (1 << 5);
//             break;

//         case D2U_R2L:   //���µ���,���ҵ���
//             skhda |= (1 << 7) | (1 << 6) | (1 << 5);
//             break;
//     }

//     diomf = 0X36;

//     if(lcd_id == 0X9341)
//         skhda |= 0X08;

//     LCD_WriteReg(diomf, skhda);
//     LCD_Open_Window(0, 0, lcd_width, lcd_height); //������ɨ�跽��󣬿���ʾ����Ϊȫ������
// }

// /****************************************************************************
// * ��    ��: void Set_Display_Mode(u8 mode)
// * ��    �ܣ�����LCD��ʾ����
// * ��ڲ�����mode: 0,����
//                   1,����
// * ���ز�������
// * ˵    ����?B
// ****************************************************************************/
// void Set_Display_Mode(u8 mode)
// {
//     if(mode == 0)		 //����
//     {
//         dir_flag = 0;

//         if(lcd_id == 0X9341)
//         {
//             write_gramcmd = 0X2C;
//             setxcmd = 0X2A;
//             setycmd = 0X2B;
//             lcd_width = 240;
//             lcd_height = 320;
//         }
//         else if(lcd_id == 0X1963)
//         {
//             write_gramcmd = 0X2C;	 //GRAM��ָ��
//             setxcmd = 0X2B;	     //дX����ָ��
//             setycmd = 0X2A;	     //дY����ָ��
//             lcd_width = 480;		 //���ÿ���480
//             lcd_height = 800;		 //���ø߶�800
//         }
//     }
//     else 				  //����
//     {
//         dir_flag = 1;

//         if(lcd_id == 0X9341)
//         {
//             write_gramcmd = 0X2C;
//             setxcmd = 0X2A;
//             setycmd = 0X2B;
//             lcd_width = 320;
//             lcd_height = 240;
//         }
//         else if(lcd_id == 0X1963)
//         {
//             write_gramcmd = 0X2C;	 //GRAM��ָ��
//             setxcmd = 0X2A;	      //дX����ָ��
//             setycmd = 0X2B;	      //дY����ָ��
//             lcd_width = 800;		  //���ÿ���800
//             lcd_height = 480;		  //���ø߶�480
//         }
//     }

//     Set_Scan_Direction(L2R_U2D);	//����ɨ�跽��   ������,���µ���
// }

// /****************************************************************************
// * ��    ��: void LCD_SetCursor(u16 Xaddr, u16 Yaddr)       ��#��%��#��
// * ��    �ܣ����ù��λ��
// * ��ڲ�����x��x����
//             y��y����
// * ���ز�������
// * ˵    ����
// ****************************************************************************/
// void LCD_SetCursor(u16 Xaddr, u16 Yaddr)
// {
//     if(lcd_id == 0X9341)
//     {
//         LCD_CMD = setxcmd;
//         LCD_DATA = (Xaddr >> 8);
//         LCD_DATA = (Xaddr & 0XFF);
//         LCD_CMD = setycmd;
//         LCD_DATA = (Yaddr >> 8);
//         LCD_DATA = (Yaddr & 0XFF);
//     }
//     else if(lcd_id == 0X1963)
//     {
//         if(dir_flag == 0)
//         {
//             Xaddr = lcd_width - 1 - Xaddr;
//             LCD_CMD = setxcmd;
//             LCD_DATA = 0;
//             LCD_DATA = 0;
//             LCD_DATA = Xaddr >> 8;
//             LCD_DATA = Xaddr & 0XFF;
//         }
//         else
//         {
//             LCD_CMD = setxcmd;
//             LCD_DATA = Xaddr >> 8;
//             LCD_DATA = Xaddr & 0XFF;
//             LCD_DATA = (lcd_width - 1) >> 8;
//             LCD_DATA = (lcd_width - 1) & 0XFF;
//         }

//         LCD_CMD = setycmd;
//         LCD_DATA = Yaddr >> 8;
//         LCD_DATA = Yaddr & 0XFF;
//         LCD_DATA = (lcd_height - 1) >> 8;
//         LCD_DATA = (lcd_height - 1) & 0XFF;

//     }
// }

// /****************************************************************************
// * ��    ��: u16 LCD_GetPoint(u16 x,u16 y)
// * ��    �ܣ���ȡĳ�����ɫֵ
// * ��ڲ�����x��x����
//             y��y����
// * ���ز������˵����ɫ
// * ˵    ����
// ****************************************************************************/
// u16 LCD_GetPoint(u16 x, u16 y)
// {
//     vu16 r = 0, g = 0, b = 0;

//     LCD_SetCursor(x, y);

//     LCD_CMD = 0X2E; //9341��1963��GRAMָ��һ��
//     r = LCD_DATA;

//     if(lcd_id == 0X1963)
//         return r;		   //1963ֱ�Ӷ���������16λ��ɫֵ

//     else	 //������������9341
//     {
//         lcdm_delay(2);
//         b = LCD_DATA;  //9341Ҫ��2��
//         g = r & 0XFF;		 //9341��һ�ζ�ȡ����RG��ֵ,R��ǰ,G�ں�,��ռ8λ
//         g <<= 8;
//         return (((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11)); //9341�蹫ʽת��
//     }
// }

// /****************************************************************************
// * ��    ��: void LCD_DrawPoint(u16 x,u16 y)
// * ��    �ܣ����㣨�ڸõ�д�뻭�ʵ���ɫ��
// * ��ڲ�����x��x����
//             y��y����
// * ���ز�������
// * ˵    ��?BRUSH_COLOR:�˵����ɫֵ
// ****************************************************************************/
// void LCD_DrawPoint(u16 x, u16 y)
// {
//     LCD_SetCursor(x, y);		   //���ù��λ��
//     LCD_WriteGRAM();	        //��ʼд��GRAM
//     LCD_DATA = BRUSH_COLOR;
// }

// /****************************************************************************
// * ��    ��: void LCD_Color_DrawPoint(u16 x,u16 y,u16 color)
// * ��    �ܣ������õ����괦����Ӧ��ɫ���ڸõ�д���Զ�����ɫ��
// * ��ڲ�����x��x����
//             y��y����
//             color �˵����ɫֵ
// * ���ز�������
// * ˵    ����color:д��˵����ɫֵ   GUI���øú���
// ****************************************************************************/
// void LCD_Color_DrawPoint(u16 x, u16 y, u16 color)
// {
//     LCD_DrawPoint(x, y);
//     LCD_CMD = write_gramcmd;
//     LCD_DATA = color;
// }

// /****************************************************************************
// * ��    ��: void Ssd1963_Set_BackLight(u8 BL_value)
// * ��    �ܣ�SSD1963 ���ñ���
// * ��ڲ�����BL_value���������ȴ�С  ȡֵ:0-255  ����255����
// * ���ز�������
// * ˵    ����
// ****************************************************************************/
// void Ssd1963_Set_BackLight(u8 BL_value)
// {
//     LCD_CMD = 0xBE;
//     LCD_DATA = 0x05;
//     LCD_DATA = BL_value;
//     LCD_DATA = 0x01;
//     LCD_DATA = 0xFF;
//     LCD_DATA = 0x00;
//     LCD_DATA = 0x00;
// }

// /****************************************************************************
// * ��    ��: void LCD_Clear(u16 color)
// * ��    �ܣ���������
// * ��ڲ�����color: Ҫ���������ɫ
// * ���ز�������
// * ˵    ����?B
// ****************************************************************************/
// void LCD_Clear(u16 color)
// {
//     u32 i = 0;
//     u32 pointnum = 0;

//     pointnum = lcd_width * lcd_height; 	 //�õ�LCD�ܵ���
//     LCD_SetCursor(0x00, 0x00);	      //���ù��λ��
//     LCD_WriteGRAM();     		 //��ʼд��GRAM

//     for(i = 0; i < pointnum; i++)
//     {
//         LCD_DATA = color;
//     }
// }




// u16 ILI9341_Read_id(void)
// {
//     u16 id;

//     LCD_CMD = 0xD3;	//9341��ID����
//     id = LCD_DATA;
//     id = LCD_DATA; 	//0x00
//     id = LCD_DATA; //0x93
//     id <<= 8;
//     id |= LCD_DATA; //0x41

//     return id;
// }

// u16 SSD1963_Read_id(void)
// {
//     u16 id;

//     LCD_CMD = (0xA1); //1963��ID����
//     id = LCD_DATA;
//     id = LCD_DATA;	//0x57
//     id <<= 8;
//     id |= LCD_DATA;	//0x61

//     return id;
// }

// //��ʼ��lcd
// void LCD_Init(void)
// {
//     delay_ms(50);
//     GPIO_InitTypeDef GPIO_Initure;
//     __HAL_RCC_GPIOF_CLK_ENABLE();			//����GPIOFʱ��
//     GPIO_Initure.Pin = GPIO_PIN_10;          	//PF10,�������
//     GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP; //�������
//     GPIO_Initure.Pull = GPIO_PULLUP;        //����
//     GPIO_Initure.Speed = GPIO_SPEED_HIGH;   //����
//     HAL_GPIO_Init(GPIOF, &GPIO_Initure);


//     lcd_id = ILI9341_Read_id(); //�ȶ�����������Ļ�ǲ���9341����

//     if(lcd_id != 0x9341)		//�������9341���������ǲ���1963����
//     {
//         lcd_id = SSD1963_Read_id();

//         if(lcd_id == 0x5761)
//             lcd_id = 0x1963; //SSD1963ʵ�ʶ�����ID��0x5761,Ϊ��ֱ�ۣ��������Ϊ1963
//     }

//     if(lcd_id == 0X9341) //������,����дʱ��Ϊ���
//     {
//         FSMC_Bank1E->BWTR[6] &= ~(0XF << 0); //��ַ����ʱ������
//         FSMC_Bank1E->BWTR[6] &= ~(0XF << 8); //���ݱ���ʱ������
//         FSMC_Bank1E->BWTR[6] |= 3 << 0;		 //��ַ����ʱ��Ϊ3��HCLK =18ns
//         FSMC_Bank1E->BWTR[6] |= 2 << 8;    	 //���ݱ���ʱ��Ϊ6ns*3��HCLK=18ns
//     }

//     if(lcd_id == 0X9341)	//9341��ʼ��
//     {
//         LCD_CMD = 0xCF;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0xC1;
//         LCD_DATA = 0X30;
//         LCD_CMD = 0xED;
//         LCD_DATA = 0x64;
//         LCD_DATA = 0x03;
//         LCD_DATA = 0X12;
//         LCD_DATA = 0X81;
//         LCD_CMD = 0xE8;
//         LCD_DATA = 0x85;
//         LCD_DATA = 0x10;
//         LCD_DATA = 0x7A;
//         LCD_CMD = 0xCB;
//         LCD_DATA = 0x39;
//         LCD_DATA = 0x2C;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x34;
//         LCD_DATA = 0x02;
//         LCD_CMD = 0xF7;
//         LCD_DATA = 0x20;
//         LCD_CMD = 0xEA;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x00;
//         LCD_CMD = 0xC0;
//         LCD_DATA = 0x1B;
//         LCD_CMD = 0xC1;
//         LCD_DATA = 0x01;
//         LCD_CMD = 0xC5;
//         LCD_DATA = 0x30;
//         LCD_DATA = 0x30;
//         LCD_CMD = 0xC7;
//         LCD_DATA = 0XB7;
//         LCD_CMD = 0x36;
//         LCD_DATA = 0x48;
//         LCD_CMD = 0x3A;
//         LCD_DATA = 0x55;
//         LCD_CMD = 0xB1;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x1A;
//         LCD_CMD = 0xB6;
//         LCD_DATA = 0x0A;
//         LCD_DATA = 0xA2;
//         LCD_CMD = 0xF2;
//         LCD_DATA = 0x00;
//         LCD_CMD = 0x26;
//         LCD_DATA = 0x01;
//         LCD_CMD = 0xE0;
//         LCD_DATA = 0x0F;
//         LCD_DATA = 0x2A;
//         LCD_DATA = 0x28;
//         LCD_DATA = 0x08;
//         LCD_DATA = 0x0E;
//         LCD_DATA = 0x08;
//         LCD_DATA = 0x54;
//         LCD_DATA = 0XA9;
//         LCD_DATA = 0x43;
//         LCD_DATA = 0x0A;
//         LCD_DATA = 0x0F;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x00;
//         LCD_CMD = 0XE1;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x15;
//         LCD_DATA = 0x17;
//         LCD_DATA = 0x07;
//         LCD_DATA = 0x11;
//         LCD_DATA = 0x06;
//         LCD_DATA = 0x2B;
//         LCD_DATA = 0x56;
//         LCD_DATA = 0x3C;
//         LCD_DATA = 0x05;
//         LCD_DATA = 0x10;
//         LCD_DATA = 0x0F;
//         LCD_DATA = 0x3F;
//         LCD_DATA = 0x3F;
//         LCD_DATA = 0x0F;
//         LCD_CMD = 0x2B;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x01;
//         LCD_DATA = 0x3f;
//         LCD_CMD = 0x2A;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0xef;
//         LCD_CMD = 0x11;
//         delay_ms(120);
//         LCD_CMD = 0x29;

//         LCD_BACK = 1;	 //��������
//     }
//     else if(lcd_id == 0X1963)
//     {
//         LCD_CMD = 0xE2;
//         LCD_DATA = 0x1D;
//         LCD_DATA = 0x02;
//         LCD_DATA = 0x04;
//         delay_us(100);

//         LCD_CMD = 0xE0;
//         LCD_DATA = 0x01;
//         delay_ms(10);

//         LCD_CMD = 0xE0;
//         LCD_DATA = 0x03;
//         delay_ms(12);

//         LCD_CMD = 0x01;		//����λ
//         delay_ms(10);

//         LCD_CMD = 0xE6;
//         LCD_DATA = 0x2F;
//         LCD_DATA = 0xFF;
//         LCD_DATA = 0xFF;

//         LCD_CMD = 0xB0;
//         LCD_DATA = 0x20;
//         LCD_DATA = 0x00;

//         LCD_DATA = (800 - 1) >> 8; //LCDˮƽ��������
//         LCD_DATA = 800 - 1;
//         LCD_DATA = (480 - 1) >> 8; //LCD��ֱ��������
//         LCD_DATA = 480 - 1;
//         LCD_DATA = 0x00;		 //RGB����

//         LCD_CMD = 0xB4;
//         LCD_DATA = (800 + 46 + 210 - 1) >> 8;
//         LCD_DATA = 800 + 46 + 210 - 1;
//         LCD_DATA = 46 >> 8;
//         LCD_DATA = 46;
//         LCD_DATA = 0;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x00;

//         LCD_CMD = 0xB6;
//         LCD_DATA = (480 + 23 + 22 - 1) >> 8;
//         LCD_DATA = 480 + 23 + 22 - 1;
//         LCD_DATA = 23 >> 8;
//         LCD_DATA = 23;
//         LCD_DATA = 21;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x00;

//         LCD_CMD = 0xF0;
//         LCD_DATA = 0x03;	//SSD1963��MCU�Ľӿ�Ϊ16bit

//         LCD_CMD = 0x29;	//������ʾ
//         LCD_CMD = 0xD0;	//�����Զ���ƽ��DBC
//         LCD_DATA = 0x00;

//         LCD_CMD = 0xBE;	 //PWM���
//         LCD_DATA = 0x05;	//PWMƵ��
//         LCD_DATA = 0xFE;	//PWMռ�ձ�
//         LCD_DATA = 0x01;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x00;
//         LCD_DATA = 0x00;

//         LCD_CMD = 0xB8;
//         LCD_DATA = 0x03;
//         LCD_DATA = 0x01;
//         LCD_CMD = 0xBA;
//         LCD_DATA = 0X01;	//����LCD����

//         Ssd1963_Set_BackLight(255);//��������
//     }

//     Set_Display_Mode(0);		 //��ʼ��Ϊ����
//     LCD_Clear(WHITE);        //������ɫ
// }

// /****************************************************************************
// * ��    ��: void LCD_Fill_onecolor(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)  ��*��@��#��
// * ��    �ܣ���ָ����������䵥����ɫ
// * ��ڲ�����(sx,sy),(ex,ey):�����ζԽ�����
//             color:Ҫ������ɫ
// * ���ز�������
// * ˵    ���������СΪ:(ex-sx+1)*(ey-sy+1)  ?B
// ****************************************************************************/
// void LCD_Fill_onecolor(u16 sx, u16 sy, u16 ex, u16 ey, u16 color)
// {
//     u16 i, j;
//     u16 nlen = 0;

//     nlen = ex - sx + 1;

//     for(i = sy; i <= ey; i++)
//     {
//         LCD_SetCursor(sx, i);      				 //���ù��λ��
//         LCD_WriteGRAM();     			  //��ʼд��GRAM

//         for(j = 0; j < nlen; j++)
//             LCD_DATA = color;	//���ù��λ��
//     }
// }

// /****************************************************************************
// * ��    ��: void LCD_Draw_Picture(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
// * ��    �ܣ���ָ�������ڻ���ͼƬ
// * ��ڲ�����(sx,sy),(ex,ey):�����ζԽ�����
//             color:Ҫ����ͼƬ������ɫ����
// * ���ز�������
// * ˵    ���������СΪ:(ex-sx+1)*(ey-sy+1)  ?B
// ****************************************************************************/
// void LCD_Draw_Picture(u16 sx, u16 sy, u16 ex, u16 ey, u16 *color)
// {
//     u16 height, width;
//     u16 i, j;
//     width = ex - sx + 1; 			 //�õ�ͼƬ�Ŀ���
//     height = ey - sy + 1;			 //�õ�ͼƬ�ĸ߶�

//     for(i = 0; i < height; i++)
//     {
//         LCD_SetCursor(sx, sy + i); //���ù��λ��
//         LCD_WriteGRAM();        //��ʼд��GRAM

//         for(j = 0; j < width; j++)
//             LCD_DATA = color[i * height + j]; //д����ɫֵ
//     }
// }

// /****************************************************************************
// * ��    ��: void LCD_DisplayChar(u16 x,u16 y,u8 num,u8 size)
// * ��    �ܣ���ָ��λ����ʾһ���ַ�
// * ��ڲ�����x,y:��ʼ����
//             word:Ҫ��ʾ���ַ�:abcdefg1234567890...
//             size:�����С 12/16/24
// * ���ز�������
// * ˵    ��������ģȡģ����Ϊ�ȴ����ң��ٴ��ϵ���  ��λ��ǰ  ?B
// ****************************************************************************/
// void LCD_DisplayChar(u16 x, u16 y, u8 word, u8 size)
// {
//     u32  bytenum, bytedata, a, b;
//     u16 ymid = y;

//     if(size == 12) bytenum = 12;    // �жϸ����������ֿ�������ռ���ֽ���
//     else if(size == 16) bytenum = 16;
//     else if(size == 24) bytenum = 36;
//     else if(size == 48) bytenum = 144;
//     else if(size == 64) bytenum = 256; //���ֻ֧�ֵ�64��
//     else return;

//     word = word - ' '; //�õ�ƫ�ƺ��ֵ ��Ϊ�ո�֮ǰ���ַ�û��font.h�е���������

//     for(b = 0; b < bytenum; b++)
//     {
//         if(size == 12)bytedata = char_1206[word][b]; 	 	 //����1206����
//         else if(size == 16)bytedata = char_1608[word][b];	//����1608����
//         else if(size == 24)bytedata = char_2412[word][b];	//����2412����
//         else if(size == 48)bytedata = char_4824[word][b];	//����4824����
//         else if(size == 64)bytedata = char_6432[word][b];	//����6432����
//         else return;								                  //û�е��ַ����飬û�ַ��ֿ�

//         for(a = 0; a < 8; a++)
//         {
//             if(bytedata & 0x80)LCD_Color_DrawPoint(x, y, BRUSH_COLOR);
//             else LCD_Color_DrawPoint(x, y, BACK_COLOR);

//             bytedata <<= 1;
//             y++;

//             if(y >= lcd_height)return;		//�������˳�����

//             if((y - ymid) == size)
//             {
//                 y = ymid;
//                 x++;

//                 if(x >= lcd_width)return;	 //�������˳�����

//                 break;
//             }
//         }
//     }
// }
// /****************************************************************************
// * ��    ��: void LCD_DisplayString(u16 x,u16 y,u8 size,u8 *p)
// * ��    �ܣ���ʾ�ַ���
// * ��ڲ�����x,y:�������
// *           size:�����С
// *           *p:�ַ�����ʼ��ַ
// * ���ز�������
// * ˵    ����  ?B
// ****************************************************************************/
// void LCD_DisplayString(u16 x, u16 y, u8 size, u8 *p)
// {
//     while((*p >= ' ') && (*p <= '~')) //ֻ��ʾ�� ������~��֮����ַ�
//     {
//         LCD_DisplayChar(x, y, *p, size);
//         x += size / 2;

//         if(x >= lcd_width) break;

//         p++;
//     }
// }

// /****************************************************************************
// * ��    ��: void LCD_DisplayString(u16 x,u16 y,u8 size,u8 *p)
// * ��    �ܣ���ʾ�Զ����ַ���
// * ��ڲ�����x,y:�������
// *           width,height:�����С
// *           size:�����С
// *           *p:�ַ�����ʼ��ַ
// *           brushcolor���Զ��廭����ɫ
// *           backcolor�� �Զ��屳����ɫ
// * ���ز�������
// * ˵    ����  ?B
// ****************************************************************************/
// void LCD_DisplayString_color(u16 x, u16 y, u8 size, u8 *p, u16 brushcolor, u16 backcolor)
// {
//     u16 bh_color, bk_color;

//     bh_color = BRUSH_COLOR; //�ݴ滭����ɫ
//     bk_color = BACK_COLOR; //�ݴ汳����ɫ

//     BRUSH_COLOR = brushcolor;
//     BACK_COLOR = backcolor;

//     LCD_DisplayString(x, y, size, p);

//     BRUSH_COLOR = bh_color; //���ı�ϵͳ��ɫ
//     BACK_COLOR = bk_color;
// }

// //a^n����������ֵ:a^n�η�
// u32 Counter_Power(u8 a, u8 n)
// {
//     u32 mid = 1;

//     while(n--)mid *= a;

//     return mid;
// }

// /****************************************************************************
// * ��    ��: void LCD_DisplayNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
// * ��    �ܣ���ָ��λ����ʾһ������
// * ��ڲ�����x,y:�������
//             value:��ֵ;
//             len:����(������ʾ��λ��)
//             size:�����С
//             mode: 0����λΪ0����ʾ
//                   1����λΪ0����len���Ȳ���ʾ����0
// * ���ز�������
// * ˵    ����  ?B
// ****************************************************************************/
// void LCD_DisplayNum(u16 x, u16 y, u32 value, u8 len, u8 size, u8 mode)
// {
//     u8 t, numtemp;
//     u8 value_num;     //��ֵ�ܹ���λ��
//     u32 value_mid;

//     value_mid = value; //����λ��ʱ��Ӱ��Ҫ��ʾ����ֵ��С

//     for (value_num = 0; value_mid > 0; value_num++)
//     {
//         value_mid /= 10;
//     } //ִ����for����֪��Ҫ��ʾ����ֵΪ��λ��

//     if(value_num > len) //��ֵλ����������λ��������ʾ���򲻹� ��ʾ����
//     {
//         LCD_DisplayString(x, y, size, "ERR");
//         return; //�˳�����
//     }
//     else
//     {
//         for(t = 0; t < len; t++)
//         {
//             if( t < (len - value_num))
//             {
//                 if(mode)LCD_DisplayChar(x + (size / 2)*t, y, '0', size);
//                 else LCD_DisplayChar(x + (size / 2)*t, y, ' ', size);
//             }
//             else
//             {
//                 numtemp = (value / Counter_Power(10, len - t - 1)) % 10; //ȡ����λ��ֵ
//                 LCD_DisplayChar(x + (size / 2)*t, y, numtemp + '0', size);
//             }
//         }
//     }
// }
// /****************************************************************************
// * ��    ��: void LCD_Num(u16 x,u16 y,u32 num,u8 len,u8 size)
// * ��    �ܣ���ָ��λ����ʾһ������
// * ��ڲ�����x,y:�������
//             num:��ֵ;
//             len:����(������ʾ��λ��)
//             size:�����С
//                   1����λΪ0����len���Ȳ���ʾ����0
// * ���ز�������
// * ˵    ��:����Ϊ��ɫΪ����������Ϊ��ɫΪ����?B
// ****************************************************************************/
// void LCD_Num(u16 x, u16 y, int num, u8 len, u8 size)
// {
//     if(num >= 0)
//     {
//         LCD_DisplayNum_color(x, y, num, len, size, 1, BLACK, GBLUE);
//     }
//     else
//     {
//         LCD_DisplayNum_color(x, y, -num, len, size, 1, BLACK, MAGENTA);
//     }
// }
// /****************************************************************************
// * ��    ��: void LCD_DisplayNum_color(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
// * ��    �ܣ���ָ��λ����ʾһ���Զ�����ɫ������  ��#��*��&��
// * ��ڲ�����x,y:�������
//             num:��ֵ;
//             len:����(��Ҫ��ʾ��λ��)
//             size:�����С
//             mode: 0����λΪ0����ʾ
//                   1����λΪ0��ʾ0
//             brushcolor���Զ��廭����ɫ
//             backcolor�� �Զ��屳����ɫ
// * ���ز�������
// * ˵    ����  ?B
// ****************************************************************************/
// void LCD_DisplayNum_color(u16 x, u16 y, u32 num, u8 len, u8 size, u8 mode, u16 brushcolor, u16 backcolor)
// {
//     u16 bh_color, bk_color;

//     bh_color = BRUSH_COLOR; //�ݴ滭����ɫ
//     bk_color = BACK_COLOR; //�ݴ汳����ɫ

//     BRUSH_COLOR = brushcolor;
//     BACK_COLOR = backcolor;

//     LCD_DisplayNum(x, y, num, len, size, mode);

//     BRUSH_COLOR = bh_color; //���ı�ϵͳ��ɫ
//     BACK_COLOR = bk_color;
// }
// /****************************************************************************
// * ��    ��: void LCD_Draw_Line(u16 x1, u16 y1, u16 x2, u16 y2)
// * ��    �ܣ�����
// * ��ڲ�����x1,y1:�������
//             x2,y2:�յ�����
// * ���ز�������
// * ˵    ��������������Ļ��ߣ�ˮƽ�ߡ���ֱ����б��(���ߡ��������뻭Բ�ο����ϴ���)  ?B
// ************************2****************************************************/
// void LCD_Draw_Line(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
// {
//     u16 i;
//     int xm1 = 0, ym2 = 0, model_x, model_y, model,  mcx, mcy, mRow, mCol;

//     model_x = x2 - x1;              //����ֱ�ߵ�ģ ������������
//     model_y = y2 - y1;
//     mRow = x1;
//     mCol = y1;

//     if(model_x > 0)mcx = 1;
//     else if(model_x == 0)mcx = 0;  //��ֱ��
//     else
//     {
//         mcx = -1;
//         model_x = -model_x;
//     }

//     if(model_y > 0)mcy = 1;
//     else if(model_y == 0)mcy = 0;  //ˮƽ��
//     else
//     {
//         mcy = -1;
//         model_y = -model_y;
//     }

//     if( model_x > model_y)model = model_x;
//     else model = model_y;

//     for(i = 0; i <= model + 1; i++ ) //�������
//     {
//         LCD_Color_DrawPoint(mRow, mCol, color);
//         xm1 += model_x ;
//         ym2 += model_y ;

//         if(xm1 > model)
//         {
//             xm1 -= model;
//             mRow += mcx;
//         }

//         if(ym2 > model)
//         {
//             ym2 -= model;
//             mCol += mcy;
//         }
//     }
// }
// /****************************************************************************
// * ��    ��: void LCD_Draw_Rectangle(u16 x1, u16 y1, u16 x2, u16 y2)
// * ��    �ܣ�������
// * ��ڲ�����(x1,y1),(x2,y2):���εĶԽ�����
// * ���ز�������
// * ˵    ����  ?B
// ****************************************************************************/
// void LCD_Draw_Rectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
// {
//     LCD_Draw_Line(x1, y1, x2, y1, color);
//     LCD_Draw_Line(x1, y1, x1, y2, color);
//     LCD_Draw_Line(x1, y2, x2, y2, color);
//     LCD_Draw_Line(x2, y1, x2, y2, color);
// }
// /****************************************************************************
// * ��    ��: void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
// * ��    �ܣ���ָ��λ�û�һ��ָ����С��Բ
// * ��ڲ�����(x,y):���ĵ�
//             r    :�뾶
// * ���ز�������
// * ˵    ����  ?B
// ****************************************************************************/
// void LCD_Draw_Circle(u16 x0, u16 y0, u8 r, u16 color)
// {
//     int a, b;
//     int di;
//     a = 0;
//     b = r;
//     di = 3 - (r << 1);       //�ж��¸���λ�õı�־

//     while(a <= b)
//     {
//         LCD_Color_DrawPoint(x0 + a, y0 - b, color);
//         LCD_Color_DrawPoint(x0 + b, y0 - a, color);
//         LCD_Color_DrawPoint(x0 + b, y0 + a, color);
//         LCD_Color_DrawPoint(x0 + a, y0 + b, color);
//         LCD_Color_DrawPoint(x0 - a, y0 + b, color);
//         LCD_Color_DrawPoint(x0 - b, y0 + a, color);
//         LCD_Color_DrawPoint(x0 - a, y0 - b, color);
//         LCD_Color_DrawPoint(x0 - b, y0 - a, color);
//         a++;

//         if(di < 0)di += 4 * a + 6;	 //ʹ��Bresenham�㷨��Բ
//         else
//         {
//             di += 10 + 4 * (a - b);
//             b--;
//         }
//     }
// }
// void LCD_SHOWER(void)
// {  
	
// 	//ʹ���������ʱ����Ҫ��ʾ�ַ���!!!!!!!!!!! 
//         //   LCD_Num(0,0,delay_flag,3,16);//���1guangdian_flag
//         //   LCD_Num(40,0,move_stop_flag,3,16);//���2guangdian_flag2
//         //   LCD_Num(90,0,tim4_delay,5,16);
//         //   LCD_Num(140,0,is_delay_triggered,5,16);
//         //   LCD_Num(170,40,flafjh,1,24);
//     //    LCD_Num(10,20,flag_2,3,24);//������stcAngle.Angle[2] (Go1Motor[4].Pos - GOset[4].GO_setpos)
//     //    LCD_Num(20,40,(laser_distance )/10,4,16);//y������
//     //    LCD_Num(20,80,(laser_distance1 )/10,4,16);//x������
// 	  // LCD_Num(60,0,stcAngle.Angle[2],5,24);//�ƾ���	
//       // LCD_Num(70,30, stcAngle.Angle[2],5,24);//����������
//  //      LCD_Num(80,60,zuobiao_pan_date_x,5,24);//����������
//     //   LCD_Num(90,90,zuobiao_pan_date_y,5,24);//����������
    
//     //   LCD_Num(120,180,laser_distance ,4,24);//go��ʼ����־
// //     LCD_Num(120,220,zuobiao_date_z ,5,16);//������
// //    LCD_Num(130,240,zuobiao_date_x,5,16);//������
//     //  LCD_Num(140,260,Go1Motor[1].Pos,3,24);//������
//     //  LCD_Num(150,280,Go1Motor[2].Pos,3,24);//������
//     //   LCD_Num(160,220,Go1Motor[3].Pos,3,24);//����
//     //  LCD_Num(170,320,Go1Motor[4].Pos,3,24);//����

// }
