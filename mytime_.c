//#include "main.h"
//#include "can.h"
//#include "tim.h"
//#include "gpio.h"
////#include "fsmc.h"
////#include "MOTOR.h"
////#include "motor_can.h"
//#include "mytim.h"
//#include "math.h"
//#include "lcd.h"

//#define DLY_TIM_Handle (&htim14)                      // 微秒延时句柄
//int t1, t_1, t2, t_2, t_Accel, Accelt, t_text, textt; // 时间计算
//int TIM2_mode = 1, TIM6_mode = 1, TIM7_mode = 1;
//float zhigh;
//int serball = 1;
//int xnumb;
//int visball;
//float xxout1, xxout2, yyout1, yyout2;
//float soutx1, soutx2, souty1, souty2;
//int isFirstValue = 1; // 标志位，默认为第一次获�?
//int INSANE_LOOK[5];
//float elect1, elect2, elect3, elect4;
//float ball_time[2] = {0};

//float x1x;
//float y1x;
//float x2y;
//float y2y;
//float x1m, y1m;
//float high_change;
//float x1high, y1high;
//float anglex1, anglex2;
//float angley3, angley4;
//float anglem5, anglem6;
//float angleh1, angleh2;
//int angleadd[4] = {0};
//int ser_flag;
//int jugle_dis;             // y初次上电激光测距距�?
//int jugle_dis1;            // x初次上电激光测距距�?
//int first_laser_flag = 0;  // y激光测距初次上电标�?
//int first_laser_flag1 = 0; // x激光测距初次上电标�?
//u8 flag_stop = 0;
//u8 change_move = 0;
//u8 move_flag_2 = 0;

//u8 move_stop_flag = 0;

//int tim4_delay = 0; // 0-->2000 = 1s
//int delay_flag = 0; // 延时完成标志

//uint8_t is_delay_triggered = 0; // 标记是否触发了延�?

//int flafjh = 0;//FLAG
//float nowpos[4];
//float pos[4];

//int speed_conversion=0;
//int change_speed_flag=0;


//uint8_t lcd_refresh_flag = 0;

////void jugle_keep(void) 
////{
////  if (laser_distance != 0 && first_laser_flag == 0)
////  {
////    jugle_dis = laser_distance;
////    first_laser_flag = 1;
////  }
////  if (laser_distance1 != 0 && first_laser_flag1 == 0)
////  {
////    jugle_dis1 = laser_distance1;
////    first_laser_flag1 = 1;
////  }
////}

//void delay_us(uint16_t nus)
//{
//  __HAL_TIM_SET_COUNTER(DLY_TIM_Handle, 0);
//  __HAL_TIM_ENABLE(DLY_TIM_Handle);

//  while (__HAL_TIM_GET_COUNTER(DLY_TIM_Handle) < nus)
//  {
//  }

//  __HAL_TIM_DISABLE(DLY_TIM_Handle);
//}
//void delay_ms(uint16_t nms)
//{
//  uint32_t i;

//  for (i = 0; i < nms; i++)
//    delay_us(1000);
//}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) // sent
//{

//  if (htim->Instance == TIM4)//1ms
//  {
////    TIM4_int();
//  }

//  if (htim->Instance == TIM3)//1ms
//  {

//  } // htim->Instance == TIM3

//  if (htim->Instance == TIM2)
//  {

//    TIM2_int();
//  }
//}

//void TIM2_int(void)
//{
//}

//void TIM4_int(void)
//{

////  Buffer_Tick();
////  Time4_delay();

//        // 获取当前光电状�?
//  if (tim4_delay > 0)
//  {
//    tim4_delay--;
//    if (tim4_delay == 0)
//    {
//      delay_flag = 1; // 延时完成
//    }
//  }
//  static uint16_t lcd_cnt = 0;
//    lcd_cnt++;
//    if(lcd_cnt >= 100)
//    {
//        lcd_cnt = 0;
//        lcd_refresh_flag = 1;  // 置标志位
//    }
//}

