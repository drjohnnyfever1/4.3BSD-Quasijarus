h40482
s 00011/00021/00101
d D 1.2 88/03/28 13:46:44 bostic 2 1
c add Berkeley specific header
e
s 00122/00000/00000
d D 1.1 87/05/10 11:28:03 minshall 1 0
c date and time created 87/05/10 11:28:03 by minshall
e
u
U
t
T
I 1
/*
D 2
 *	Copyright (c) 1984, 1985, 1986 by the Regents of the
 *	University of California and by Gregory Glenn Minshall.
E 2
I 2
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 2
 *
D 2
 *	Permission to use, copy, modify, and distribute these
 *	programs and their documentation for any purpose and
 *	without fee is hereby granted, provided that this
 *	copyright and permission appear on all copies and
 *	supporting documentation, the name of the Regents of
 *	the University of California not be used in advertising
 *	or publicity pertaining to distribution of the programs
 *	without specific prior permission, and notice be given in
 *	supporting documentation that copying and distribution is
 *	by permission of the Regents of the University of California
 *	and by Gregory Glenn Minshall.  Neither the Regents of the
 *	University of California nor Gregory Glenn Minshall make
 *	representations about the suitability of this software
 *	for any purpose.  It is provided "as is" without
 *	express or implied warranty.
E 2
I 2
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 2
 */

D 2
#ifndef	lint
static	char	sccsid[] = "@(#)asctab.c	3.1  10/29/86";
#endif	/* ndef lint */

E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

/*
 * ascii to ebcdic translation tables
 */

#include "ascebc.h"

unsigned char ascebc[NASCEBC][NASCII]	= {

/*
 * printer translation
 */

/* 000 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 010 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 020 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 030 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 040 */   0x40,  0x5A,  0x7F,  0x7B,  0x5B,  0x6C,  0x50,  0x74,
/* 050 */   0x4D,  0x5D,  0x5C,  0x4E,  0x6B,  0x60,  0x4B,  0x61,
/* 060 */   0xF0,  0xF1,  0xF2,  0xF3,  0xF4,  0xF5,  0xF6,  0xF7,
/* 070 */   0xF8,  0xF9,  0x7A,  0x5E,  0x4C,  0x7E,  0x6E,  0x6F,
/* 100 */   0x7C,  0xC1,  0xC2,  0xC3,  0xC4,  0xC5,  0xC6,  0xC7,
/* 110 */   0xC8,  0xC9,  0xD1,  0xD2,  0xD3,  0xD4,  0xD5,  0xD6,
/* 120 */   0xD7,  0xD8,  0xD9,  0xE2,  0xE3,  0xE4,  0xE5,  0xE6,
/* 130 */   0xE7,  0xE8,  0xE9,  0xAD,  0xE0,  0xBD,  0x71,  0x6D,
/* 140 */   0x79,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,  0x87,
/* 150 */   0x88,  0x89,  0x91,  0x92,  0x93,  0x94,  0x95,  0x96,
/* 160 */   0x97,  0x98,  0x99,  0xA2,  0xA3,  0xA4,  0xA5,  0xA6,
/* 170 */   0xA7,  0xA8,  0xA9,  0xC0,  0x4F,  0xD0,  0xA1,  0x00,

/*
 * input translation
 */

/* 000 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 010 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 020 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 030 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 040 */   0x40,  0x5A,  0x7F,  0x7B,  0x5B,  0x6C,  0x50,  0x7D,
/* 050 */   0x4D,  0x5D,  0x5C,  0x4E,  0x6B,  0x60,  0x4B,  0x61,
/* 060 */   0xF0,  0xF1,  0xF2,  0xF3,  0xF4,  0xF5,  0xF6,  0xF7,
/* 070 */   0xF8,  0xF9,  0x7A,  0x5E,  0x4C,  0x7E,  0x6E,  0x6F,
/* 100 */   0x7C,  0xC1,  0xC2,  0xC3,  0xC4,  0xC5,  0xC6,  0xC7,
/* 110 */   0xC8,  0xC9,  0xD1,  0xD2,  0xD3,  0xD4,  0xD5,  0xD6,
/* 120 */   0xD7,  0xD8,  0xD9,  0xE2,  0xE3,  0xE4,  0xE5,  0xE6,
/* 130 */   0xE7,  0xE8,  0xE9,  0xAD,  0xE0,  0xBD,  0x5F,  0x6D,
/* 140 */   0x79,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,  0x87,
/* 150 */   0x88,  0x89,  0x91,  0x92,  0x93,  0x94,  0x95,  0x96,
/* 160 */   0x97,  0x98,  0x99,  0xA2,  0xA3,  0xA4,  0xA5,  0xA6,
/* 170 */   0xA7,  0xA8,  0xA9,  0xC0,  0x4F,  0xD0,  0xA1,  0x00,

/*
 * special translation - for IBM 6670 laser printer.
 * Used by iroff and ipr.  The control characters 030-037 have been mapped
 * into printable (though non-ascii) characters.  Bell 007 and backspace 010
 * translate to the corresponding ebcdic characters, and ^N 016 and ^O 017
 * map to ebcdic SBS (subscript) and SPS (superscript).
 */

/* 000 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x2F,
/* 010 */   0x16,  0x00,  0x00,  0x00,  0x00,  0x00,  0x38,  0x09,
/* 020 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 030 */   0x8D,  0x9D,  0x9E,  0x8B,  0x4A,  0x9B,  0x8C,  0xAE,
/* 040 */   0x40,  0x5A,  0x7F,  0x7B,  0x5B,  0x6C,  0x50,  0x7D,
/* 050 */   0x4D,  0x5D,  0x5C,  0x4E,  0x6B,  0x60,  0x4B,  0x61,
/* 060 */   0xF0,  0xF1,  0xF2,  0xF3,  0xF4,  0xF5,  0xF6,  0xF7,
/* 070 */   0xF8,  0xF9,  0x7A,  0x5E,  0x4C,  0x7E,  0x6E,  0x6F,
/* 100 */   0x7C,  0xC1,  0xC2,  0xC3,  0xC4,  0xC5,  0xC6,  0xC7,
/* 110 */   0xC8,  0xC9,  0xD1,  0xD2,  0xD3,  0xD4,  0xD5,  0xD6,
/* 120 */   0xD7,  0xD8,  0xD9,  0xE2,  0xE3,  0xE4,  0xE5,  0xE6,
/* 130 */   0xE7,  0xE8,  0xE9,  0xAD,  0xE0,  0xBD,  0x5F,  0x6D,
/* 140 */   0x79,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,  0x87,
/* 150 */   0x88,  0x89,  0x91,  0x92,  0x93,  0x94,  0x95,  0x96,
/* 160 */   0x97,  0x98,  0x99,  0xA2,  0xA3,  0xA4,  0xA5,  0xA6,
/* 170 */   0xA7,  0xA8,  0xA9,  0xC0,  0x4F,  0xD0,  0xA1,  0x00,

/*
 * text translation - all graphics retained.
 */

/* 000 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 010 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 020 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 030 */   0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
/* 040 */   0x40,  0x5A,  0x7F,  0x7B,  0x5B,  0x6C,  0x50,  0x7D,
/* 050 */   0x4D,  0x5D,  0x5C,  0x4E,  0x6B,  0x60,  0x4B,  0x61,
/* 060 */   0xF0,  0xF1,  0xF2,  0xF3,  0xF4,  0xF5,  0xF6,  0xF7,
/* 070 */   0xF8,  0xF9,  0x7A,  0x5E,  0x4C,  0x7E,  0x6E,  0x6F,
/* 100 */   0x7C,  0xC1,  0xC2,  0xC3,  0xC4,  0xC5,  0xC6,  0xC7,
/* 110 */   0xC8,  0xC9,  0xD1,  0xD2,  0xD3,  0xD4,  0xD5,  0xD6,
/* 120 */   0xD7,  0xD8,  0xD9,  0xE2,  0xE3,  0xE4,  0xE5,  0xE6,
/* 130 */   0xE7,  0xE8,  0xE9,  0xAD,  0xE0,  0xBD,  0x71,  0x6D,
/* 140 */   0x79,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,  0x87,
/* 150 */   0x88,  0x89,  0x91,  0x92,  0x93,  0x94,  0x95,  0x96,
/* 160 */   0x97,  0x98,  0x99,  0xA2,  0xA3,  0xA4,  0xA5,  0xA6,
/* 170 */   0xA7,  0xA8,  0xA9,  0xC0,  0x4F,  0xD0,  0xA1,  0x00,
};
E 1
