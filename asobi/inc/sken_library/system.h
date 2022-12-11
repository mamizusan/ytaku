/*
 * system.h
 *
 *  Created on: 2019/09/03
 *      Author: TakumaNakao
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <sken_library/can.h>
#include <sken_library/io_name.h>
#include "stm32f4xx.h"

union ConvertIntFloat{
	int int_val;
	uint8_t uint8_val[4];
	float float_val;
};

class System
{
public:
	System(void);
	bool init(void);
	void timerInterruptCallback(void);
	unsigned int micros(void);
	unsigned int millis(void);
	void delayMillis(unsigned int delay_time_millis);
	void delayMicros(unsigned int delay_time_micros);
	bool addTimerInterruptFunc(void(*function_p)(void),int id,int period = 1);
	bool deleteTimerInterruptFunc(int id);
	bool changeTimerInterruptPeriod(int id,int period);
	bool startCanCommunicate(Pin tx_pin,Pin rx_pin,CanSelect can_select);
	bool canTransmit(CanSelect can_select,uint32_t stdid,uint8_t* data_p,int data_size,int dead_time = 10);
	bool addCanRceiveInterruptFunc(CanSelect can_select,void(*function_p)(CanRxMsgTypeDef),int id);
	bool deleteCanRceiveInterruptFunc(CanSelect can_select,int id);
private:
	static bool instance_create_flag_;
	uint8_t interrupt_func_array_flag_;
	int interrupt_func_array_period_[8];
	void (*interruptFuncArray[8])(void);
	void allClkEnable(void);
	void setSysClock(void);
	void basicTimerSet(void);
};

extern System sken_system;

#endif /* SYSTEM_H_ */
