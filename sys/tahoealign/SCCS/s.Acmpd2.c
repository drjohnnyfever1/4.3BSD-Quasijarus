h56892
s 00024/00000/00000
d D 1.1 86/07/20 11:14:04 sam 1 0
c date and time created 86/07/20 11:14:04 by sam
e
u
U
t
T
I 1
/*	%M%	%I%	%E%	*/

#include "../tahoealign/align.h"
cmpd2(infop)	process_info *infop;
/*
/*	Compare operand 1 with operand 2 (double). 
/*
/****************************************************/
{
	register double	*Register_12;	/* Has to be first reg ! */
	register double	*Register_11;
	register long	Register_10;

	Register_12 = (double *) &operand(infop,0)->data;
	Register_11 = (double *) &operand(infop,1)->data;
	if ( reserved( *(long *)Register_12 ) ||
	     reserved( *(long *)Register_11 ) )
			exception(infop, ILL_OPRND);
	Register_10=psl;
	Set_psl(r10);	/* restore the user psl */
	asm ("	cmpd2	(r12),(r11)");
	asm ("	movpsl	r10");
	New_cc (Register_10);
}
E 1
