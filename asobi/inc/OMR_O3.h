/*
 * OMR_O3.h
 *
 *  Created on: 2022/11/27
 *      Author: Owner
 */

#ifndef OMR_O3_H_
#define OMR_O3_H_

//double* Vo[3];
#include "sken_library/include.h"
#include "sken_lib/lib_include.h"

struct Enc_Pins{
	Pin omuni_a_pin;
	Pin omuni_b_pin;
	TimerNumber omuni_timer;
};

struct Motor_Pins{
	Pin motor_pinA,motor_pinB,motor_pinp;
	TimerNumber timer_num;
	TimerChannel CH;
};

struct Gein_point{
	int p_gain,i_gain,d_gain,time = 20;
};


class O3{
	Enc encoder[3];
	Encoder_data Data[3];
	Pid PID[3];
	Motor mtrA,mtrB,mtrC;
	double omuni_vol_01,omuni_vol_02,omuni_vol_03;
    double V[3];
    double Vx[3];
    double Vy[3];
    double Vomega[3];
    double VX,VY,VO;
    double X,Y,circledig;
    double sita = 0,R,r;
    double O;
    double CF,dis1;
    double PID_OUT[3];
    double Xtarget,Ytarget,Otarget;
    double Xresult,Yresult,Oresult;
	//void encode_interrupt();
    Pin pin;
public:
	O3();
	void interrupt_prot(double* X,double* Y,double* O);
	void vol(Enc_Pins A,Enc_Pins B,Enc_Pins C,Gein_point AG,Gein_point BG,Gein_point CG);
	void Command(int target_x,int target_y,int target_o);
	void init(double bodyR,double wheelR);
	void read(void);
	//Pin Aomuni_a_pin,Pin Aomuni_b_pin,TimerNumber Aomuni_timer
};



#endif /* OMR_O3_H_ */
