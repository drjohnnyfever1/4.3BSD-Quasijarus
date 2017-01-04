h58581
s 00010/00005/00046
d D 5.5 88/06/30 17:21:37 bostic 8 7
c install approved copyright notice
e
s 00010/00004/00041
d D 5.4 88/06/08 13:57:10 bostic 7 6
c written by Ken Arnold; add Berkeley specific header
e
s 00002/00002/00043
d D 5.3 86/04/16 18:20:53 mckusick 6 5
c turn on cbreak, not raw in getch() if none of noecho, raw, or
c cbreak are already set (from sun!gorodish!guy)
e
s 00002/00001/00043
d D 5.2 85/11/04 15:30:21 bloom 5 4
c echo where typed not top of screen
e
s 00010/00001/00034
d D 5.1 85/06/07 11:32:21 dist 4 3
c Add copyright
e
s 00001/00001/00034
d D 1.3 85/05/01 17:11:27 bloom 3 2
c fix sccs id
e
s 00001/00001/00034
d D 1.2 81/05/11 17:34:28 arnold 2 1
c fix an off-by-one error
e
s 00035/00000/00000
d D 1.1 81/01/26 17:02:54 arnold 1 0
c date and time created 81/01/26 17:02:54 by arnold
e
u
U
t
T
I 4
/*
D 7
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 8
E 7
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7

E 4
I 1
# include	"curses.ext"

/*
 *	This routine reads in a character from the window.
 *
D 3
 * %G% (Berkeley) %W%
E 3
I 3
D 4
 * %W% (Berkeley) %G%
E 4
E 3
 */
wgetch(win)
reg WINDOW	*win; {

	reg bool	weset = FALSE;
	reg char	inp;

	if (!win->_scroll && (win->_flags&_FULLWIN)
D 2
	    && win->_curx == win->_maxx && win->_cury == win->_maxy)
E 2
I 2
	    && win->_curx == win->_maxx - 1 && win->_cury == win->_maxy - 1)
E 2
		return ERR;
# ifdef DEBUG
	fprintf(outf, "WGETCH: _echoit = %c, _rawmode = %c\n", _echoit ? 'T' : 'F', _rawmode ? 'T' : 'F');
# endif
	if (_echoit && !_rawmode) {
D 6
		raw();
E 6
I 6
		cbreak();
E 6
		weset++;
	}
	inp = getchar();
# ifdef DEBUG
	fprintf(outf,"WGETCH got '%s'\n",unctrl(inp));
# endif
	if (_echoit) {
D 5
		mvwaddch(curscr, win->_cury, win->_curx, inp);
E 5
I 5
		mvwaddch(curscr, win->_cury + win->_begy,
			win->_curx + win->_begx, inp);
E 5
		waddch(win, inp);
	}
	if (weset)
D 6
		noraw();
E 6
I 6
		nocbreak();
E 6
	return inp;
}
E 1
