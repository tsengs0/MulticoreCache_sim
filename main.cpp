#include <systemc.h>
#include "thread.h"
#include "bus.h"
#include "RAM.h"
#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define RAM_test
//#define Cache_test
#define core_test


int cnt0 = 0, cnt1 = 1, cnt2 = 2, cnt3 = 3;
int hit_cnt_core0 = 0, hit_cnt_core1 = 0, hit_cnt_core2 = 0, hit_cnt_core3 = 0;
int access_cnt_core0 = 0, access_cnt_core1 = 0, access_cnt_core2 = 0, access_cnt_core3 = 0;

int sc_main( int argc, char *argv[] )
{
	//signal declaration
	sc_clock	clk("clk", 1, SC_NS, 0.5);

	//module declaration
	thread	module0("thread0", 0);//, 1, 1);
	thread	module1("thread1", 1);//, 0, 0);
	thread  module2("thread2", 2);//, 0, 0);
	thread  module3("thread3", 3);//, 0, 0);
	bus	bus0("bus0");

	int i;
	uint8_t *data;
	uint8_t *address;
	
	data    = (uint8_t*) malloc( 256 * sizeof(uint8_t) ); 
	srand( time(NULL) );
	for( i = 0 ; i < 256 ; i++ )	data[i] = rand() % 256;	

	RAM Main_Memory(data);

#ifdef RAM_test
	for( i = 0 ; i < 256 ; i++ )
	Main_Memory.RAM_read( i + 6000 );

        Main_Memory.RAM_write( 6255, 0x35 );
	Main_Memory.RAM_write( 6011, 0x35 );

	Main_Memory.RAM_read( 6255 );
	Main_Memory.RAM_read( 6011 );
#endif
	



#ifdef Cache_test
	uint16_t *block;
	block = ( uint16_t* ) malloc( 4 * sizeof(uint16_t) );
	Cache_Direct_mapped cache_memory( block );

	cache_memory.Cache_fetch( 0xFC );
	cache_memory.Cache_fetch( 0x05 );
	cache_memory.Cache_fetch( 0x0A );
	cache_memory.Cache_fetch( 0x0F );


	cache_memory.Cache_fetch( 0xFC );
	cache_memory.Cache_fetch( 0x05 );
	cache_memory.Cache_fetch( 0x0A );
	cache_memory.Cache_fetch( 0x0F );


	cache_memory.Cache_fetch( 0xAC );
	

#endif



#ifdef core_test

	//signal connection
	module0.clk(clk);
	module1.clk(clk);
        module2.clk(clk);
	module3.clk(clk);

	module0.write_port(bus0);
	module1.write_port(bus0);
	module2.write_port(bus0);
	module3.write_port(bus0);

	bus0.write_port(module0);	//write_port[0]
	bus0.write_port(module1);	//write_port[1]
	bus0.write_port(module2);	//write_port[2]
	bus0.write_port(module3);	//write_port[3]

	//run simulation
	sc_start(100, SC_NS);
printf("---------------------------------------------------------------------------------------------------------------------------------\r\n");
printf("The cache fetch time of Core0 is %d\r\n" , module0.alu_module->memory_cache->access_cnt_core);
printf("The hit time of Core0 is %d\r\n\r\n",  module0.alu_module->memory_cache->hit_cnt_core);

printf("The cache fetch time of Core1 is %d\r\n" , module1.alu_module->memory_cache->access_cnt_core);
printf("The hit time of Core1 is %d\r\n\r\n",  module1.alu_module->memory_cache->hit_cnt_core);

printf("The cache fetch time of Core2 is %d\r\n" , module2.alu_module->memory_cache->access_cnt_core);
printf("The hit time of Core2 is %d\r\n\r\n",  module2.alu_module->memory_cache->hit_cnt_core);

printf("The cache fetch time of Core3 is %d\r\n" , module3.alu_module->memory_cache->access_cnt_core);
printf("The hit time of Core3 is %d\r\n\r\n",  module3.alu_module->memory_cache->hit_cnt_core);
printf("---------------------------------------------------------------------------------------------------------------------------------\r\n");
#endif
	return 0;


}
