# Enc
Encoderクラスを継承したクラス  
実際的な値をこのクラスで得ることができる

# struct Encoder_data
演算したカウンタの値を格納するための構造体

[要素内容]  
カウンタの値  
回転数[回転]  
角度[deg]  
移動距離[mm]    
速度[mm/s]  
毎秒回転数[rps]  

[要素一覧]
``` c++
struct Encoder_data{
	int count;
	double rot,deg,distance,volcity,rps;
};
```
# class Enc
## void Enc::init(Pin pin_a,Pin pin_b,TimerNumber TIMER,double r,int ppr = 8192,int period = 1);
エンコーダのピン、タイマー、回転体半径、分解能、制御周期を設定する.  
使⽤することができるタイマーは1,2,3,4,5,8のチャンネル1とチャンネル2である．  
エンコーダのカウントに使⽤するタイマーはチャンネル3とチャンネル4も含めてPWM出⼒に使⽤することはできない．

[パラメータ]  
チャンネル1のピン番号  
チャンネル2のピン番号  
タイマー番号  
回転体半径[mm]  
分解能 （デフォルト：8192）  
制御周期[ms]（デフォルト：1[ms]）  

[戻り値]  
なし

[サンプルコード]  
タイマー2をエンコーダモード、回転体半径を50[mm]に設定.（分解能、制御周期はデフォルト値）  
``` c++
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "sken_library/include.h"
#include "sken_lib/lib_include.h"

Enc encoder;

int main(void){
	sken_sysytem.init();
	
	encoder.init(A0,A1,TIMER2,50);
	
	while(true){
	
	}
}
```

## void interrupt(Encoder_data* encoder_data);
エンコーダでの測定結果をEncoder_data構造体に返す関数.タイマー割り込みで使用する.  

[パラメータ]  
Encoder_data構造体のアドレス

[戻り値]  
なし

[サンプルコード]  
エンコーダでの測定を行う
``` c++
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "sken_library/include.h"
#include "sken_lib/lib_include.h"

Enc encoder;
Encoder_data encoder_data;

void encoder_interrupt(){
	encoder.interrupt(&encoder_data);
}

int main(void){
	sken_sysytem.init();
	
	encoder.init(A0,A1,TIMER2,50);
	sken_sysytem.addTimerInterruptFunc(encoder_interrupt,0,1);
	
	while(true){
	
	}
}
```

## void Enc::reset();
カウンタの値をリセットする

[パラメータ]  
なし  

[戻り値]  
なし

[サンプルコード]
カウンタの値が10000を超えたときにリセットする
``` c++
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "sken_library/include.h"
#include "sken_lib/lib_include.h"

Enc encoder;
Encoder_data encoder_data;

void encoder_interrupt(){
	encoder.interrupt(&encoder_data);
}

int main(void){
	sken_sysytem.init();
	
	encoder.init(A0,A1,TIMER2,50);
	sken_sysytem.addTimerInterruptFunc(encoder_interrupt,0,1);
	
	while(true){
		if(encodor_data.count == 10000){
			encoder.reset();
		}
	}
}
```

