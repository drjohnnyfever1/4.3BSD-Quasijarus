h34489
s 00015/00000/00000
d D 1.1 86/07/20 11:14:44 sam 1 0
c date and time created 86/07/20 11:14:44 by sam
e
u
U
t
T
I 1
/*	%M%	%I%	%E%	*/

#include "../tahoealign/align.h"
stf(infop)	process_info *infop;
/*
/*	Store accumulator (float) in destination.
/*
/*************************************************/
{

	write_back (infop, acc_high, operand(infop,0) );
	if (acc_high < 0) negative_1; else negative_0;
	if ( (acc_high & 0xff800000) == 0 ) zero_1; else zero_0;
	carry_1; overflow_0;
}
E 1
