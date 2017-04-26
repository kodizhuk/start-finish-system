#include "stdio.h"
#include "stdint.h"

void _convert_float(char *buf, double num, int width, uint8_t prec)
{
	char format[10];
	
	sprintf(format, "%%%i.%if", width, prec);
	sprintf(buf, format, num);
}
