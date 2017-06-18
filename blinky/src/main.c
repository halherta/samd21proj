#include <samd21.h>
void delayMs(int );

int main(void){
	REG_PORT_DIR0 |= (1 << 17);

	while(1){
		REG_PORT_OUT0 |= (1 << 17);
		delayMs(1);
		REG_PORT_OUT0 &= ~(1 << 17);
		delayMs(1);
	}
}

void delayMs(int n){
	int i;
	for(; n > 0; n--)
		for(i=0;i<199;i++)
			__asm__("nop");
}

