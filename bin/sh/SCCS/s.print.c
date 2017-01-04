h26757
s 00003/00001/00098
d D 4.2 83/08/11 20:20:03 sam 2 1
c standardize sccs keyword lines
e
s 00099/00000/00000
d D 4.1 82/05/07 19:38:44 mckusick 1 0
c date and time created 82/05/07 19:38:44 by mckusick
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% %G%";
#endif
E 2

#
/*
 * UNIX shell
 *
 * S. R. Bourne
 * Bell Telephone Laboratories
 *
 */

#include	"defs.h"

CHAR		numbuf[6];


/* printing and io conversion */

newline()
{	prc(NL);
}

blank()
{	prc(SP);
}

prp()
{
	IF (flags&prompt)==0 ANDF cmdadr
	THEN	prs(cmdadr); prs(colon);
	FI
}

VOID	prs(as)
	STRING		as;
{
	REG STRING	s;

	IF s=as
	THEN	write(output,s,length(s)-1);
	FI
}

VOID	prc(c)
	CHAR		c;
{
	IF c
	THEN	write(output,&c,1);
	FI
}

prt(t)
	L_INT		t;
{
	REG INT	hr, min, sec;

	t += 30; t /= 60;
	sec=t%60; t /= 60;
	min=t%60;
	IF hr=t/60
	THEN	prn(hr); prc('h');
	FI
	prn(min); prc('m');
	prn(sec); prc('s');
}

prn(n)
	INT		n;
{
	itos(n); prs(numbuf);
}

itos(n)
{
	REG char *abuf; REG POS a, i; INT pr, d;
	abuf=numbuf; pr=FALSE; a=n;
	FOR i=10000; i!=1; i/=10
	DO	IF (pr |= (d=a/i)) THEN *abuf++=d+'0' FI
		a %= i;
	OD
	*abuf++=a+'0';
	*abuf++=0;
}

stoi(icp)
STRING	icp;
{
	REG CHAR	*cp = icp;
	REG INT		r = 0;
	REG CHAR	c;

	WHILE (c = *cp, digit(c)) ANDF c ANDF r>=0
	DO r = r*10 + c - '0'; cp++ OD
	IF r<0 ORF cp==icp
	THEN	failed(icp,badnum);
	ELSE	return(r);
	FI
}

E 1
