h44414
s 00010/00005/00028
d D 5.4 88/06/27 18:25:47 bostic 4 3
c install approved copyright notice
e
s 00010/00008/00023
d D 5.3 88/05/25 14:24:03 bostic 3 2
c written by Robert Elz; add Berkeley specific header
e
s 00001/00001/00030
d D 5.2 86/03/09 19:36:30 donn 2 1
c added LIBC_SCCS condition for sccs ids
e
s 00031/00000/00000
d D 5.1 85/08/05 21:43:08 kre 1 0
c date and time created 85/08/05 21:43:08 by kre
e
u
U
t
T
I 1
/*
 * Copyright (c) 1985 Regents of the University of California.
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
E 3
 */

D 3
/*
 * Sys5 compat routine
 */

E 3
D 2
#ifndef lint
E 2
I 2
#if defined(LIBC_SCCS) && !defined(lint)
E 2
D 3
static char sccsid[] = "%W% (Berkeley) %E%";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */
E 3

strspn(s, set)
	register char *s, *set;
{
	register n = 0;
	register char *p;
	register c;

	while (c = *s++) {
		for (p = set; *p; p++)
			if (c == *p)
				break;
		if (!*p)
			return (n);
		n++;
	}
	return (n);
}
E 1
