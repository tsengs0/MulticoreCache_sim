#include "bus.h"

bus::bus( sc_module_name nm ) : sc_module(nm)
{
}

void bus::write( unsigned addr, int data1, int data2 )
{
	//addr0 write module0 ; 1 write module1 ; 2 write module2 : 3 write module3
	if( addr == 0 )
		write_port[0] -> write( addr, data1, data2 );
	else if( addr == 1 )
		write_port[1] -> write( addr, data1, data2 );
	else if( addr == 2 )
		write_port[2] -> write( addr, data1, data2 );
	else if( addr == 3 )
		write_port[3] -> write( addr, data1, data2 );
	else 
		printf( "There are only 4 cores were built.\r\n" );


}
