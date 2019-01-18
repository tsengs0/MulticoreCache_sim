#include "thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int cnt0, cnt1, cnt2, cnt3;


void thread::thread_func()
{
	while(1)
	{
		
		//srand( time(NULL) );	
		  alu_data[0] = alu_module -> memory_cache -> Cache_fetch( rand() % 256 );
		//srand( time(NULL) );	
		  alu_data[1] = alu_module -> memory_cache -> Cache_fetch( rand() % 256 ); 
		//process handle
		wait();
		
		//module1 initiate data is (0, 0)
		if( alu_data[0] == 0 )	wait(2);//waiting for module0

		//enalble save_module
		strcpy( save_data, thread::name() );
		save_enable.write(true);
		wait();
		save_enable.write(false);

		//enable alu_module
		alu_enable.write(true);
		wait();
		alu_enable.write(false);

		//address 0 => module0 ; 1 => module1 ; 2 => module2 ; 3 => module3
		if( address == 0 )
		{
		  write_port -> write( cnt0++, alu_data[0], alu_data[1] );
		  printf( "Transfering the sum of data from Core_0 to Core_%d\r\n", cnt0 );
		  printf("data[0] = %d, data[1] = %d\r\n\r\n", alu_data[0], alu_data[1]);
		  cnt0 = cnt0 % 4;
		}
		else if( address == 1 )
		{
		  write_port -> write( cnt1++, alu_data[0], alu_data[1] );
	          printf( "Transfering the sum of data from Core_1 to Core_%d\r\n", cnt1 );
	          printf("data[0] = %d, data[1] = %d\r\n\r\n", alu_data[0], alu_data[1]);
		  cnt1 = cnt1 % 4;
		}
		else if( address == 2 )
		{ 
	          write_port -> write( cnt2++, alu_data[0], alu_data[1] );
		  printf( "Transfering the sum of data from Core_2 to Core_%d\r\n", cnt2 );
		  printf("data[0] = %d, data[1] = %d\r\n\r\n", alu_data[0], alu_data[1]);
		  cnt2 = cnt2 % 4;
		}
		else if( address == 3 )
		{
		  write_port -> write( cnt3++, alu_data[0], alu_data[1] );
		  printf( "Transfering the sum of data from Core_3 to Core_%d\r\n", cnt3 );
		  printf("data[0] = %d, data[1] = %d\r\n\r\n", alu_data[0], alu_data[1]);
		  cnt3 = cnt3 % 4;
		}
		else
		  printf( "There are only 4 core were built.\r\n" );

		//waiting for another module
		wait(2);
		
		
	//	printf(" %d %\r\n", ((int)((alu_module -> memory_cache -> hit_cnt_core)*100)) / ((int)((alu_module -> memory_cache -> access_cnt_core)*100)) );
		
		
		

	}


}


void thread::write( unsigned addr, int data1, int data2 )
{
	//writing data to buffer
	alu_data[0] = data1;
	alu_data[1] = data2;

}
