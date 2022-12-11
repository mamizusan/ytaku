/**
  ******************************************************************************

  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "math.h"
#include "sken_library/include.h"
#include "sken_lib/lib_include.h"
#include "OMR_O3.h"
#include "sken_mdd.h"

	O3 red;
	double target[3];


	Encoder_data Data_prot[3];
	Enc encoder;
	Enc_Pins pins[3];


	Gein_point G[3];


	SkenMdd mdd;

	void encode_interrupt()
	{
	red.interrupt_prot(&target[0],&target[1],&target[2]);
	red.read();
	}

	const float mode[4] = {0,0,0,0};//全部０で切るって感じ．
	const float encoder_config[4] = {8192,8192,8192,8192};//ここはエンコーダーそれぞれの分解能らしい
	const float diameter[4] = {76.0,680.0,0,0};//移しただけ．タイヤ直径と旋回半径

	const float M1_gain_config[4] = {5.0,10.0,0.1,20};//こいつらはｋｐとかの値だな，最後のは分からん
	const float M2_gain_config[4] = {5.0,10.0,0.1,20};
	const float M3_gain_config[4] = {5.0,10.0,0.1,20};

	float robot_volcity[4] = {0,0,0,0};

int main(void)
	{
	sken_system.init();

	mdd.tcp(MOTOR_COMMAND_MODE_SELECT,mode,10,2000);//PWMモードを切るらしい．
	mdd.tcp(ENCODER_RESOLUTION_CONFIG,encoder_config,10,2000);//エンコーダーの分解能の設定
	mdd.tcp(ROBOT_DIAMETER_CONFIG,diameter,10,2000);//色んな半径の設定
	mdd.tcp(M1_PID_GAIN_CONFIG,M1_gain_config,10,2000);//pidのkpのせっていだなー
	mdd.tcp(M2_PID_GAIN_CONFIG,M2_gain_config,10,2000);
	mdd.tcp(M3_PID_GAIN_CONFIG,M3_gain_config,10,2000);

	//encoder.init(B4,B5,TIMER3,50);
	red.vol(pins[0],pins[1],pins[2],G[0],G[1],G[2]);//encoder pin timerB4,B5,TIMER3,A0,A1,TIMER2,A8,A9,TIMER1
	red.init(30,30);//robottohannkei taiyahannkei
	sken_system.addTimerInterruptFunc(encode_interrupt,0,1);
	while(true)
	{
		robot_volcity[0] = target[0];
		robot_volcity[1] = target[1];
	    robot_volcity[2] = target[2];

	    mdd.udp(OMNI3_MODE,robot_volcity);

	   if(robot_volcity[0]==0 && robot_volcity[1]==0 && robot_volcity[2]==0){
	    	mdd.udp(PID_RESET_COMMAND,mode);
	      }
	}

    }


