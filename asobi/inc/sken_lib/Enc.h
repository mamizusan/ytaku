/*
 * Enc.h
 *
 *  Created on: 2021/07/17
 *      Author: hotaka
 */

#ifndef ENC_H_
#define ENC_H_

#include "sken_library/encoder.h"

struct Encoder_data{
	int count;
	double rot,deg,distance,volcity,rps;
};

class Enc {
public:
	Enc(void);
	void init(Pin pin_a,Pin pin_b,TimerNumber TIMER,double diameter,int ppr = 8192,int period = 1);
	void interrupt(Encoder_data* encoder_data);
	void reset();
private:
	Encoder encoder;
	int ppr_,diameter_,period_,limit;
	double PI = 3.1415926535;
	Pin pin[2];
};

#endif /* ENC_H_ */
