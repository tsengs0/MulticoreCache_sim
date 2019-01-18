#include <iostream>
#include <systemc.h>
//#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

static int i;
static int msec;


void Cache_Direct_mapped::Cache_write( uint8_t addr, uint8_t data )
{

  Block[ addr % 4 ] &= ~( 0x3F << 8  );//Resetting the 6-bit of Tag of Block
  Block[ addr % 4 ] &= ~( 0x1  << 14 );//Resetting the Valid bit of Block
  Block[ addr % 4 ] = ( ( uint16_t ) ( data ) ) | ( ( uint16_t ) ( addr >> 2 ) ) << 8 | ( ( uint16_t ) ( 0x1 ) ) << 14; 
  
  //cout << "The Data of Block #" << addr % 4 << " of Cache was written by " << "{ " << data << " }" << endl;
  printf("The Data of Block 0x%02X of Cache was written by 0x%02X\r\n", addr % 4, data);
  
///////////////////////////////////////////////
//Delay 2ms
msec = 2;
    while(msec--) {
        i = 100;
        while(i--);
    }
  
//////////////////////////////////////////////// 
  
  
}

uint8_t Cache_Direct_mapped::Cache_fetch( uint8_t addr )
{
 

    //If Valid bit is '1' and the demanded Tag is exist in Cache memory 
    if( 
	(( (uint8_t) ( addr >> 2  ) ) == ((uint8_t) (( Block[addr % 4] & (0x3F00)) >> 8) )) 
        &&
        ( Block[addr % 4] & 0x4000 ) != 0 

    ) 
    { 
        //cout << "The Data of Block #" << addr % 4 << " of Cache was Hitted " << "{ " << data << " }" << endl;
	printf("The Data of Bloc 0x%02X of Cache was Hitted 0x%02X\r\n", addr % 4, (uint8_t) Block[addr % 4]);
	
	hit_cnt_core += 1;	
	access_cnt_core += 1;
///////////////////////////////////////////////
//Delay 1ms
msec = 1;
    while(msec--) {
        i = 100;
        while(i--);
    }
  
//////////////////////////////////////////////// 
	
	return (uint8_t) ( Block[addr % 4] & 0x00FF ); 
    }


    //If Valid bit is not '1' or the demanded Tag is not exist in Cache memory 
   else  if( 
	(( (uint8_t) ( addr >> 2  ) ) != ((uint8_t) (( Block[addr % 4] & (0x3F00)) >> 8) ) )
        ||
        ( Block[addr % 4] & 0x4000 ) == 0 

    )
    { 
	//cout << "The Data of Block #" << addr % 4 << " of Cache was missed hit " << endl;
	printf("==========================================================================================================================================\r\n");
	printf("The Data of Block 0x%02X of Cache was missed hit\r\n\r\n", addr % 4);
	FILE *fp;
        uint8_t *buffer;
 	buffer = (uint8_t*) malloc( 256 * sizeof(uint8_t) );
	if( ( fp = fopen( "RAM_256x8.dat", "rb" ) ) == NULL )
	 {
		//cout << "Cannot read the values of Weight" << endl;
		printf("Cannot read the values of Weight\r\n");
		return ( false );
	 }


	fread( (uint8_t*) buffer, sizeof(uint8_t), 256 * sizeof(uint8_t), fp );
	//Block[addr % 4] = 0x0000;
	//Block[addr % 4] = ((uint16_t) (0x1 << 14)) | ((uint16_t) (addr >> 2)) | ((uint16_t) (buffer[addr % 4]));
        
	printf("Miss penalty !\r\n");
	Cache_write( addr, buffer[addr] );
	//cout << "Hit miss" << endl;
	printf("========================================================================================================================================\r\n\r\n");
        fclose(fp);
	access_cnt_core += 1;
	return buffer[addr];//Meaning miss hit 
    }

 
  
	
   
}

Cache_Direct_mapped::Cache_Direct_mapped( uint16_t *block )
{
	Block = block;
	hit_cnt_core = 0;
	access_cnt_core = 0;


}


