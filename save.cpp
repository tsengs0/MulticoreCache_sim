#include "save.h"


void save::save_thread()
{
	while(1)
	{
		//process handle
		wait();
		
		//print simulateion time when writing file
		sc_time_stamp().print();
		printf("open file summation.txt to write !\r\n");
		

		fout = fopen("summation.txt", "a");

		if( fout == NULL )
		{
			printf("open file error !");
			//cout << "open file error !" << endl;
			exit(1);
		}

	//write data
	fprintf(fout, " %s %d %c", save_data, alu_data[0], "\n");
	fprintf(fout, " %s %d %c", save_data, alu_data[1], "\n");

	fclose(fout);

	}

}
