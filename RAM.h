#ifndef RAM_H
#define RAM_H

#include <iostream>
#include <systemc.h>
#define uint8_t unsigned char
#define uint16_t unsigned short



class RAM
{
private:
	uint8_t *Data;

public:
	void RAM_write( uint16_t addr, uint8_t data );
	uint8_t RAM_read( uint16_t addr );
	
	RAM( uint8_t *data );

	//~RAM();

};
#endif //RAM_H
