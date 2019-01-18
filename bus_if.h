#ifndef BUS_IF_H
#define BUS_IF_H

#include <systemc.h>

class bus_if : public sc_interface
{
	//pure virtual function
public:
	virtual void write( unsigned addr, int dtat1, int data2 ) = 0;

};

#endif //BUS_IF_H
