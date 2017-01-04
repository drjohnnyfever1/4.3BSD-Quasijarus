h57482
s 00002/00002/00017
d D 5.2 86/03/09 19:56:02 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00010
d D 5.1 85/06/05 12:33:59 mckusick 2 1
c Add copyright
e
s 00011/00000/00000
d D 4.1 83/06/30 17:20:21 sam 1 0
c date and time created 83/06/30 17:20:21 by sam
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
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

D 3
#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif LIBC_SCCS and not lint
E 3
E 2

/*
 * Backwards compatible setuid.
 */
setuid(uid)
	int uid;
{

	return (setreuid(uid, uid));
}
E 1
