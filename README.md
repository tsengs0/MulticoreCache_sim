This is a simple exercise of using SystemC when I was in undergraduate school.

I implemented a multicore simulator which contains: <br />
	* Four indentical cores. it is for performing simple arithmetic unit (ALU) <br />
	* Main memory (RAM). The size is 256x8 bits (tentative) <br />
	* L1 data cache. Each core owns one L1 cache memory <br />
	* System bus. It is for interconnecting whole elements, i.e., cores and main memory

I managed to evaluate the hit and miss ratio of L1 cache of each core. Specifically every core will randomly chose two data from the RAM and do the addition operation. Then transfer the calculation reslut to another core via RAM.

  
