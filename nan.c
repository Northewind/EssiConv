#include <string.h>


/** Little endian representation of double NaN */
static unsigned char nan_bytes[] =
	{0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x7F};


double nan()
{
	double ans;
	memcpy(&ans, nan_bytes, sizeof nan_bytes);
	return ans;
}

