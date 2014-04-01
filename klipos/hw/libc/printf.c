/*
 The MIT License (MIT)
 
 Copyright (c) 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "../include/libs-default.h"

#include <stdarg.h>

void defaultPrintfInterface(uint8_t c)
{
    c = 0;
}

static PrintfInterfaceCallback printfInterfaceCallback = &defaultPrintfInterface;

void xputc(uint8_t c)
{
    printfInterfaceCallback(c);
}

void xputs (const char* str)
{
	while (*str)
	{
		xputc(*str++);
	}
}

void setPrintfInterface(PrintfInterfaceCallback callback)
{
    printfInterfaceCallback = callback;
}

#ifdef FIRMWARE_USE_FLOAT_IN_PRINTF

unsigned int binToDecimalAscii(int bin,char *result)
{
	int i=0;
	char bCount, bPrinted;
	unsigned int lTmp,lDigit;
    
	bPrinted = 0;
	if(bin < 0)
	{
		bin = -bin;
		result[i++]='-';
	}
    
	lDigit = 1000000000L;
	for(bCount = 0; bCount < 9; bCount++)
	{
		lTmp = (char)(bin/lDigit);
		if(lTmp)
		{
			result[i++]=(char)(lTmp)+'0';
			bPrinted = 1;
		}
		else if(bPrinted)
		{
			result[i++]=(char)lTmp+'0';
		}
		bin -= ((long)lTmp)*lDigit;
		lDigit = lDigit/10;
	}
    
	lTmp = (char)(bin/lDigit);
    
	result[i++]=(char)lTmp+'0';
    
	return i;
}

void printFloat(double value)
{
    char string[48];
    int len;
    
    int first = (int)value;
    double t = (value - (double)first) * 100000.0;
    if (t<0)
        t= -t;
    
    len = binToDecimalAscii(first, string);
    string[len] = 0;
    
    xputs(string);
    xputc('.');
    
    
    len = binToDecimalAscii((int)t, string);
    string[len] = 0;

    xputs(string);
}
#endif

void printf (
	const char*	str,	// Pointer to the format string
	...					// Optional arguments
)
{
	va_list arp;
	unsigned int r, i, w, f;
	unsigned long val;
	char s[24], c, d;

#ifdef FIRMWARE_USE_FLOAT_IN_PRINTF
        double fval;
#endif

	va_start(arp, str);

	while ((c = *str++) != 0) {
		if (c != '%') {
			xputc(c); continue;
		}
		c = *str++;
		f = 0;
		if (c == '0') {				// Flag: '0' padded
			f = 1; c = *str++;
		}
		w = 0;
		while (c >= '0' && c <= '9') {	// Minimum width
			w = w * 10 + c - '0';
			c = *str++;
		}
		if (c == 'l' || c == 'L') {	// Prefix: Size is long int
			f |= 2; c = *str++;
		}
		if (!c) break;
		d = c;
		if (d >= 'a') d -= 0x20;
		switch (d) {				// Type is...
		case 'S' :					// String
			xputs(va_arg(arp, char*)); continue;
		case 'C' :					// Character
			xputc((char)va_arg(arp, int)); continue;
		case 'B' :					// Binary
			r = 2; break;
		case 'O' :					// Octal
			r = 8; break;
		case 'D' :					// Signed decimal
		case 'U' :					// Unsigned decimal
			r = 10; break;
		case 'X' :					// Hexdecimal
			r = 16; break;
#ifdef FIRMWARE_USE_FLOAT_IN_PRINTF
                case 'F':
                        fval = (double)va_arg(arp, double);
                        printFloat(fval);
                        continue;
#endif
		default:					// Unknown
			xputc(c); continue;
		}

		// Get an argument and put it in numeral
		if (f & 2) {
			val = va_arg(arp, long);
		} else {
			if (d == 'D') {
				val = (long)va_arg(arp, int);
			} else {
				val =va_arg(arp, unsigned int);
			}
		}
		if (d == 'D' && (val & 0x80000000)) {
			val = 0 - val;
			f |= 4;
		}
		i = 0;
		do {
			d = (char)(val % r); val /= r;
			if (d > 9) {
				d += 7;
				if (c == 'x') d += 0x20;
			}
			s[i++] = d + '0';
		} while (val && i < sizeof(s));
		if (f & 4) s[i++] = '-';
		while (i < w--) xputc((f & 1) ? '0' : ' ');
		do xputc(s[--i]); while(i);
	}

	va_end(arp);
}
