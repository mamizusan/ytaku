/*
 * Enc.cpp
 *
 *  Created on: 2021/07/17
 *      Author: hotaka
 */

#include "Enc.h"

Enc::Enc(void)
	: ppr_(0),diameter_(0),period_(0),limit(0)
{}

void Enc::init(Pin pin_a,Pin pin_b,TimerNumber TIMER,double diameter,int ppr,int period){
	encoder.init(pin_a,pin_b,TIMER);
	diameter_ = diameter;
	ppr_ = ppr;
	period_ = period;
}

void Enc::interrupt(Encoder_data* encoder_data){
	if(encoder.read() >= 20000||encoder.read() <= -20000){
		if(encoder.read() >= 20000){limit++;}else{limit--;}
		encoder.reset();
	}
	encoder_data->count = encoder.read()+limit*20000;
	encoder_data->rot = (encoder_data->count)/(double)ppr_;
	encoder_data->deg = ((encoder_data->count)/(double)ppr_)*360.0;
	encoder_data->distance = encoder_data->deg*(PI*diameter_/360.0);

	static double before_distance,before_count;
	encoder_data->volcity = (encoder_data->distance-before_distance)/(period_*0.001);
	before_distance = encoder_data->distance;
	encoder_data->rps = (double)((encoder_data->count)-before_count)/(double)ppr_/(period_*0.001);
	before_count = encoder_data->count;
}

void Enc::reset(){
	encoder.reset();
	limit = 0;
}
