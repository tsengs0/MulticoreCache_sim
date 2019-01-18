#ifndef ALU_H
#define ALU_H

#include <systemc.h>
#include "cache.h"

//#define unsigned short uint16_t

//unsigned short Block_1[4];

SC_MODULE(alu)
{
public:
	//signal declaration
	sc_in<bool> enable;
	Cache_Direct_mapped *memory_cache;

	//constructor
	alu( sc_module_name _name, int *alu_pointer, uint16_t *Block )
	:sc_module( _name ),
	 alu_data( alu_pointer )
	{
		//process declaration
		SC_HAS_PROCESS( alu );
		SC_THREAD( alu_thread );
		sensitive << enable.pos();
		memory_cache = new  Cache_Direct_mapped(Block);
		
	}
	
	//destructor
	~alu(){}

	void alu_thread();

private:
	int *alu_data;
	//Cache_Direct_mapped *memory_cache;

};
#endif	//ALU_H
