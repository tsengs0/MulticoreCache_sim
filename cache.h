#ifndef CACHE_H
#define CACHE_H
#include <systemc.h>
#include <iostream>
#define uint8_t unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int


class Cache_Direct_mapped
{
private:
/**
Address :

     [ 7:2 ]                         [ 1:0 ]
--------------------------------------------------------
|      			|				|
|       Tag	     	|  	   Index                |
|  		  	|				|
--------------------------------------------------------

Block :

  [15]   [14]   [ 13:8 ]          [ 7:0 ]
---------------------------------------------------------
|     |        |       |                                |
| NC  |  Valid |   Tag |   DATA ( 1-Byte per word )     |
|     |        |       |                                |
----------------------------------------------------------
**/

	uint8_t   *Address;
	uint16_t  *Block;
	
        

public:
	void Cache_write( uint8_t addr, uint8_t data );
	uint8_t Cache_fetch( uint8_t addr );
	
	Cache_Direct_mapped( uint16_t *block );
	int hit_cnt_core;
	int access_cnt_core;
	

	//~Cache_Direct_mapped();

};
#endif //CACHE_H
