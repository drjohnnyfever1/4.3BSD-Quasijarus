h62516
s 00010/00005/00045
d D 5.3 88/06/30 17:22:05 bostic 5 4
c install approved copyright notice
e
s 00010/00004/00040
d D 5.2 88/06/08 13:57:47 bostic 4 3
c written by Ken Arnold; add Berkeley specific header
e
s 00010/00001/00034
d D 5.1 85/06/07 11:42:26 dist 3 2
c Add copyright
e
s 00001/00001/00034
d D 1.2 85/05/01 17:34:43 bloom 2 1
c fix sccs id
e
s 00035/00000/00000
d D 1.1 81/01/26 17:03:14 arnold 1 0
c date and time created 81/01/26 17:03:14 by arnold
e
u
U
t
T
I 1
/*
I 3
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 5
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

/*
E 3
 * routines dealing with entering and exiting standout mode
 *
D 2
 * %G% (Berkeley) %W%
E 2
I 2
D 3
 * %W% (Berkeley) %G%
E 3
E 2
 */

# include	"curses.ext"

/*
 * enter standout mode
 */
char *
wstandout(win)
reg WINDOW	*win;
{
	if (!SO && !UC)
		return FALSE;

	win->_flags |= _STANDOUT;
	return (SO ? SO : UC);
}

/*
 * exit standout mode
 */
char *
wstandend(win)
reg WINDOW	*win;
{
	if (!SO && !UC)
		return FALSE;

	win->_flags &= ~_STANDOUT;
	return (SE ? SE : UC);
}
E 1
