/*
 * OMR_O3.cpp
 *
 *  Created on: 2022/11/27
 *      Author: Owner
 */
#include "OMR_O3.h"
/*Enc encoder[3];
Encoder_data Data[3];*/
#include "math.h"
#define PI 3.14159265359
	O3::O3(){}

	//encoder0,1,2でオムニ1,2,3.Dataも同じ．

    /*void O3::encode_interrupt(){
    encoder[0].interrupt(&Data[0]);
    encoder[1].interrupt(&Data[1]);
    encoder[2].interrupt(&Data[2]);
    }*/

	/*main関数の割り込みで実体を持たせる関数，構造体Dataはmain関数から触れないため，
	引数にmainで用意した構造体を送り込み，その構造体にDataの中身を代入し値を得るつもり．*/
	 void O3::interrupt_prot(double* X,double* Y,double* O)
	 {
	 encoder[0].interrupt(&Data[0]);
	 encoder[1].interrupt(&Data[1]);
	 encoder[2].interrupt(&Data[2]);
	 /**omuni_01_data = Data[0];
	 *omuni_02_data = Data[1];
	 *omuni_03_data = Data[2];*/
	 PID_OUT[0] = PID[0].control(Xtarget,1)/0.001;
	 PID_OUT[1] = PID[1].control(Ytarget,1)/0.001;
	 PID_OUT[2] = PID[2].control(Otarget,1)*dis1;
	 *X = PID_OUT[0];
	 *Y = PID_OUT[1];
	 *O = PID_OUT[2];

	 }

	 void O3::init(double bodyR,double wheelR){
	 r = wheelR;
	 R = bodyR;
	 CF = (2.0*PI)*R;
	 dis1 = CF/360.0;
	 }

	 void O3::Command(int target_x,int target_y,int target_o){
	 Xresult = target_x;
	 Yresult = target_y;
	 Oresult = target_o;
	 }



    //encoderの初期設定の為，引数が必要．
	void O3::vol(Enc_Pins A,Enc_Pins B,Enc_Pins C,Gein_point AG,Gein_point BG,Gein_point CG){

	encoder[0].init(A.omuni_a_pin,A.omuni_b_pin,A.omuni_timer,r);
	encoder[1].init(B.omuni_a_pin,B.omuni_b_pin,B.omuni_timer,r);
	encoder[2].init(C.omuni_a_pin,C.omuni_b_pin,C.omuni_timer,r);
	PID[0].setGain(AG.p_gain,AG.i_gain,AG.d_gain,AG.time);
	PID[1].setGain(BG.p_gain,BG.i_gain,BG.d_gain,BG.time);
	PID[2].setGain(CG.p_gain,CG.i_gain,CG.d_gain,CG.time);
	//sken_system.addTimerInterruptFunc(encode_interrupt,0,1);
}

	void O3::read(void){
	Vy[0] = Data[0].volcity * sin(sita+PI);
	Vy[1] = Data[1].volcity * sin(sita+(5.0/3.0)*PI);
	Vy[2] = Data[2].volcity * sin(sita+(1.0/3.0)*PI);
	Vx[0] = Data[0].volcity * cos(sita+PI);
	Vx[1] = Data[1].volcity * cos(sita+(5.0/3.0)*PI);
	Vx[2] = Data[2].volcity * sin(sita+(1.0/3.0)*PI);
	Vomega[0] = Data[0].volcity/R;
	Vomega[1] = Data[1].volcity/R;
	Vomega[2] = Data[2].volcity/R;

	VX = (Vx[0]+Vx[1]+Vx[2])/3.0;
	VY = (Vy[0]+Vy[1]+Vy[2])/3.0;
	VO = (Vomega[0]+Vomega[1]+Vomega[2])/3.0;
	circledig = VO/dis1;//*


	Xtarget = Xresult;
	Ytarget = Yresult;
	Otarget = Oresult;

	Xtarget = Xtarget - (VX*0.001);//*
	Ytarget = Ytarget - (VY*0.001);//* targetを入れる
	Otarget = Otarget - circledig;
	sita = sita + circledig;

	}

	/*void O3::write(Motor_Pins mA,Motor_Pins mB,Motor_Pins mC){
	mtrA.init(mA.motor_pinA,mA.motor_pinp,mA.motor_pinB,mA.timer_num,mA.CH);
	mtrB.init(mB.motor_pinA,mB.motor_pinp,mB.motor_pinB,mB.timer_num,mB.CH);
	mtrC.init(mC.motor_pinA,mC.motor_pinp,mC.motor_pinB,mC.timer_num,mC.CH);
	mtrA.write(PID_OUT[0]);
	mtrB.write(PID_OUT[1]);
	mtrC.write(PID_OUT[2]);
	}これは他基盤でやった方がいいはず．*/
