/*

*/

#include "userCode.h"

void Init(void){
	
	LED_Init();
	KEY_Init();
  
	CAN1_QuickInit();
	CAN2_QuickInit();
	
	
	DR16_receiverInit();


}


void setup(void){
  
  
}


void loop(void){
	// put your main code here, to run repeatedly:
	
	LED_RED_TOGGLE();
	delay_ms(100);

}




