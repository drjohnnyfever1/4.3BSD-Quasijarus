h15452
s 00042/00000/00000
d D 5.1 87/12/12 17:22:15 bostic 1 0
c date and time created 87/12/12 17:22:15 by bostic
e
u
U
t
T
I 1
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W%	(Berkeley)	%G%
#
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	btlgammon.c
OBJS=

all: btlgammon

btlgammon: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${SRCS}

clean: FRC
	rm -f ${OBJS} core btlgammon

depend: FRC
	mkdep -p ${CFLAGS} ${SRCS}

install: FRC
	install -s -o games -g bin -m 4700 btlgammon ${DESTDIR}/usr/games/hide
	install -c -o games -g bin -m 444 backrules ${DESTDIR}/usr/games/lib
	(cd ${DESTDIR}/usr/games; rm -f btlgammon; ln -s dm btlgammon; chown games.bin btlgammon)

lint: FRC
	lint ${CFLAGS} ${SRCS}

tags: FRC
	ctags ${SRCS}

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

btlgammon: btlgammon.c /usr/include/stdio.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 1
