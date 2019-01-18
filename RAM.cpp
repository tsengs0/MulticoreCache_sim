#include "RAM.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

static int i;
static int msec;

void RAM::RAM_write( uint16_t addr, uint8_t data )
{
  FILE *fp;

  fp = fopen("RAM_256x8.dat", "wb+");

  Data[addr-6000] = data;
  //cout << "The Data of Block " << addr << " of RAM was written by " << "{ " << data << " }" << endl;
  printf("The Data of Block %d of RAM was written by { 0x%02X }\r\n\r\n",addr, data);
  
   fwrite( (uint8_t*) Data, sizeof( uint8_t ), 256, fp );

   fclose( fp );


///////////////////////////////////////////////
//Delay 5ms
msec = 5;
    while(msec--) {
        i = 100;
        while(i--);
    }
  
//////////////////////////////////////////////// 

}

uint8_t RAM::RAM_read( uint16_t addr )
{
  FILE *fp;

    if( ( fp = fopen("RAM_256x8.dat" , "rb" ) ) == NULL )
    {
        //cout << "Cannot read the values of Weight" << endl;
	printf("Cannot read the values of Weight.\r\n");        
	return ( false );
    }


  //cout << "The date of Block " << addr << " which was fetch is " << "{ " << Data[addr-6000] << " }" << endl;
  
  fread( (uint8_t*) Data, sizeof(uint8_t), 256, fp );

  printf("The Data of Block %d which was fetch is { 0x%02X }.\r\n\r\n", addr, Data[addr-6000]);

  fclose( fp );

///////////////////////////////////////////////
//Delay 3ms
msec = 3;
    while(msec--) {
        i = 100;
        while(i--);
    }
  
//////////////////////////////////////////////// 

  return Data[addr-6000];

}

RAM::RAM( uint8_t *data )
{

  FILE *fp;

  fp = fopen("RAM_256x8.dat", "wb+");
 
  Data    = data;

 
   fwrite( (uint8_t*) Data, sizeof( uint8_t ), 256, fp );

   fclose( fp );

	

}
