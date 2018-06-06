#include "psxpblib.h"

#define BASE_ADDR 0x378
#define CONPORT 1
#define TAP 1
#define DELAY 4

char *read_block(int block_num)
{
	char *read_data;
	read_data = psx_memcard_read_block(BASE_ADDR,CONPORT,TAP,DELAY,block_num);
	return read_data;
}

int write_block(int block_num, char *data)
{
	return psx_memcard_write_block(BASE_ADDR,CONPORT,TAP,DELAY,block_num,data);
}

char *read_frame(int frame)
{
	char *read_data;
	read_data = psx_memcard_read_frame(BASE_ADDR,CONPORT,TAP,DELAY,frame);
	return read_data;
}

int write_frame(int frame, char *data)
{
	return psx_memcard_write_frame(BASE_ADDR,CONPORT,TAP,DELAY,frame,data);
}

int get_perm()
{
	return psx_obtain_io_permission(BASE_ADDR);
}
