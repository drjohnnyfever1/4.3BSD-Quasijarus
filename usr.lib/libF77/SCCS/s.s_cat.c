h48589
s 00005/00001/00024
d D 5.1 85/06/07 22:31:06 kre 2 1
c Add copyright
e
s 00025/00000/00000
d D 1.1 83/01/21 11:18:48 dlw 1 0
c date and time created 83/01/21 11:18:48 by dlw
e
u
U
t
T
I 1
/*
D 2
 *	"%W%"
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W%	%G%
E 2
 */

s_cat(lp, rpp, rnp, np, ll)
char *lp, *rpp[];
long int rnp[], *np, ll;
{
int i, n, nc;
char *rp;

n = *np;
for(i = 0 ; i < n ; ++i)
	{
	nc = ll;
	if(rnp[i] < nc)
		nc = rnp[i];
	ll -= nc;
	rp = rpp[i];
	while(--nc >= 0)
		*lp++ = *rp++;
	}
while(--ll >= 0)
	*lp++ = ' ';
}
E 1
