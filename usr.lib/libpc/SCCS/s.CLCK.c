h27474
s 00001/00000/00011
d D 1.2 81/03/07 15:53:27 mckusic 2 1
c merge in onyx changes
e
s 00011/00000/00000
d D 1.1 80/10/30 00:32:58 mckusick 1 0
c date and time created 80/10/30 00:32:58 by mckusick
e
u
U
t
T
I 1
/* Copyright (c) 1979 Regents of the University of California */

static char sccsid[] = "%Z%%M% %I% %G%";

I 2
long
E 2
CLCK()
{
	long	tim[4];

	times(tim);
	return (tim[0] * 50) / 3;
}
E 1
