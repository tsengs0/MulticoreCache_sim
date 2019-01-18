#ifndef SAVE_H
#define SAVE_H


#include <systemc.h>
#include <stdio.h>
#include <stdlib.h>

SC_MODULE(save)
{
public:
	//signal declaration
	sc_in<bool> enable;

	//constructor
	save( sc_module_name _name, char *save_pointer, int  *alu_pointer )
	:	sc_module( _name ), save_data( save_pointer ), alu_data( alu_pointer )
	{
		//process declaration
		SC_HAS_PROCESS( save );
		SC_THREAD( save_thread );
		sensitive << enable.pos();

	}
	//destructor
	~save(){}

	void save_thread();

private :
	char *save_data;
	int *alu_data;
	FILE *fout;



};
#endif //SAVE_H


