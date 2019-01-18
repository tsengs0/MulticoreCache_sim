#ifndef BUS_H
#define BUS_H

#include "bus_if.h"

class bus : public bus_if, public sc_module
{
public:
	//port declaration
	//<bud_if, 0> one or more targets
	sc_port<bus_if, 0>	write_port;

	//bus_if function
	void write( unsigned addr, int data1, int data2 );

	//constructor
	bus( sc_module_name );

};
#endif //BUS_H
