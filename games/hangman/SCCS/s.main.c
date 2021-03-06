h41291
s 00012/00007/00044
d D 5.2 88/06/18 14:44:38 bostic 2 1
c install approved copyright notice
e
s 00051/00000/00000
d D 5.1 87/12/22 13:08:08 bostic 1 0
c date and time created 87/12/22 13:08:08 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1987 Regents of the University of California.
E 2
I 2
 * Copyright (c) 1983 Regents of the University of California.
E 2
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
D 2
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 2
 */

#ifndef lint
char copyright[] =
D 2
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 2
I 2
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 2
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

# include	"hangman.h"

/*
 * This game written by Ken Arnold.
 */
main()
{
	initscr();
	signal(SIGINT, die);
	setup();
	for (;;) {
		Wordnum++;
		playgame();
		Average = (Average * (Wordnum - 1) + Errors) / Wordnum;
	}
	/* NOTREACHED */
}

/*
 * die:
 *	Die properly.
 */
die()
{
	mvcur(0, COLS - 1, LINES - 1, 0);
	endwin();
	putchar('\n');
	exit(0);
}
E 1
