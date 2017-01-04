h46690
s 00011/00006/00054
d D 5.2 88/06/18 14:44:36 bostic 2 1
c install approved copyright notice
e
s 00060/00000/00000
d D 5.1 87/12/22 13:07:46 bostic 1 0
c date and time created 87/12/22 13:07:46 by bostic
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
 *
 *	%W% (Berkeley) %G%
 */

# include	<curses.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<ctype.h>
# include	<signal.h>

# define	MINLEN	6
# define	MAXERRS	7
# define	DICT	"/usr/dict/words"

# define	MESGY	12
# define	MESGX	0
# define	PROMPTY	11
# define	PROMPTX	0
# define	KNOWNY	10
# define	KNOWNX	1
# define	NUMBERY	4
# define	NUMBERX	(COLS - 1 - 26)
# define	AVGY	5
# define	AVGX	(COLS - 1 - 26)
# define	GUESSY	2
# define	GUESSX	(COLS - 1 - 26)


typedef struct {
	short	y, x;
	char	ch;
} ERR_POS;

extern bool	Guessed[];

extern char	Word[], Known[], *Noose_pict[];

extern int	Errors, Wordnum;

extern double	Average;

extern ERR_POS	Err_pos[];

extern FILE	*Dict;

extern off_t	Dict_size;

int	die();

off_t	abs();
E 1
