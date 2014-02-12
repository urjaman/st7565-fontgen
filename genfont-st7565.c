#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Here the name of the font XBM file.
#include "stfont.xbm"
// Here the name of the font array in that file - kolourpaint makes it like this.
#define ARR _bits
#define WIDTH _width
#define HEIGHT _height

static void print_header(int chars)
{
	printf("#include <stdint.h>\n#include <avr/pgmspace.h>\n\n");
	printf("const uint8_t PROGMEM st7565_font[%d][8] = {\n",chars);
}

static void output_char(char *data)
{
	const uint8_t yvlut[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
	uint8_t output[8] = {};
	// We've been given the data as if it was an 8x8 XBM.
	for (int y=0;y<8;y++) {
		for (int x=0;x<8;x++) {
			if (data[y]&(1<<(x))) output[x] |= yvlut[y];
		}
	}
	// It has been shuffled into ST7565 friendly format, now output a char...
	printf("\t{ 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X },\n",
		output[0], output[1], output[2], output[3], output[4], output[5], output[6], output[7] );
}

static void print_footer(void)
{
	printf("};\n\n");
}

int main(void) {
	if (WIDTH%8) {
		fprintf(stderr,"Width not multiple of 8\n");
		return 1;
	}
	if (HEIGHT%8) {
		fprintf(stderr,"Height not multiple of 8\n");
		return 1;
	}

	int cpl = WIDTH/8;
	int lines = HEIGHT/8;
	print_header(cpl*lines);
	char tmpdata[8];
	for (int y=0;y<lines;y++) {
		for (int x=0;x<cpl;x++) {
			int xyb=y*8*cpl+x;
			for (int i=0;i<8;i++) tmpdata[i] = ARR[xyb+(cpl*i)];
			output_char(tmpdata);
		}
	}
	print_footer();
	return 0;
}
