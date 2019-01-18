#include "alu.h"

void alu::alu_thread()
{
	while(1)
	{
		//process handle
		wait();
		

		printf("Sum = %d\r\n", (unsigned short) (alu_data[0] + alu_data[1]));

	
		
	}


}
