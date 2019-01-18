#ifndef THREAD_H
#define THREAD_H
#include <systemc.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "alu.h"
#include "save.h"
#include "bus_if.h"

class thread
	: public bus_if, public sc_module

	{
	 public:
		//signal declaration
		sc_in_clk	clk;

		//sc_signal is basic channel
		sc_signal<bool>	alu_enable;
		sc_signal<bool>	save_enable;
		sc_port<bus_if>	write_port;

		//module instances
		alu	*alu_module;
		save	*save_module;
		
		//constructor
		thread( 
			sc_module_name     _name,
			int	           addr
			
					
		 )
		 :	sc_module( _name    ),
			address  ( addr     )
			
		 {
		
			
			//creat instances
			alu_module  = new alu ( "alu" , alu_data, Block );
			save_module = new save( 
						"save", 
						save_data, alu_data  
					  ); 

			srand( time(NULL) );	alu_data[0] = alu_module -> memory_cache -> Cache_fetch( rand() % 256 );
			srand( time(NULL) );	alu_data[1] = alu_module -> memory_cache -> Cache_fetch( rand() % 256 );	

			//connect instances
			alu_module -> enable( alu_enable );
			save_module -> enable( save_enable );

			//process declaration
			SC_HAS_PROCESS( thread );
			SC_THREAD( thread_func );
			sensitive << clk.pos();

		 }

		//destructor
		~thread() 
		{
			if( alu_module ) 
			 { delete alu_module; alu_module = 0; }
			if( save_module )
			 { delete save_module; save_module = 0; }
		
		}

		//function declaration
		void thread_func();
		void write( unsigned addr, int data1, int data2 );
		int alu_data[2];

	  private:
			//int alu_data[2];
			int address;
			char save_data[11];
			unsigned short Block[4];

	};

#endif //THREAD_H
