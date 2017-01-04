h52477
s 00010/00005/00114
d D 5.4 88/07/09 11:16:30 bostic 4 3
c install approved copyright notice
e
s 00005/00005/00114
d D 5.3 88/01/13 16:26:18 bostic 3 2
c it's rogue now, not pdrogue
e
s 00005/00005/00114
d D 5.2 87/12/01 18:02:48 bostic 2 1
c rename so won't conflict with KA's rogue
e
s 00119/00000/00000
d D 5.1 87/11/25 15:30:53 bostic 1 0
c from Tim Stoehr
e
u
U
t
T
I 1
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 4
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific written prior permission. This software
# is provided ``as is'' without express or implied warranty.
E 4
I 4
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
#
#	%W% (Berkeley) %G%
#
CFLAGS=	-O -DUNIX -DUNIX_BSD4_2
LIBC=	/lib/libc.a
SRCS=	curses.c hit.c init.c inventory.c level.c machdep.c main.c \
	message.c monster.c move.c object.c pack.c play.c random.c ring.c \
	room.c save.c score.c spec_hit.c throw.c trap.c use.c zap.c
OBJS=	curses.o hit.o init.o inventory.o level.o machdep.o main.o \
	message.o monster.o move.o object.o pack.o play.o random.o ring.o \
	room.o save.o score.o spec_hit.o throw.o trap.o use.o zap.o

D 2
all: rogue
E 2
I 2
D 3
all: pdrogue
E 3
I 3
all: rogue
E 3
E 2

D 2
rogue: ${OBJS} ${LIBC}
E 2
I 2
D 3
pdrogue: ${OBJS} ${LIBC}
E 3
I 3
rogue: ${OBJS} ${LIBC}
E 3
E 2
	${CC} ${OBJS} -o $@ -lcurses -ltermlib

clean: FRC
D 2
	rm -f ${OBJS} core rogue
E 2
I 2
D 3
	rm -f ${OBJS} core pdrogue
E 3
I 3
	rm -f ${OBJS} core rogue
E 3
E 2

depend: FRC
	mkdep ${CFLAGS} ${SRCS}

install: FRC
D 2
	install -s -o games -g bin -m 4700 rogue ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f rogue; ln -s dm rogue; chown games.bin rogue)
E 2
I 2
D 3
	install -s -o games -g bin -m 4700 pdrogue ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f pdrogue; ln -s dm pdrogue; chown games.bin pdrogue)
E 3
I 3
	install -s -o games -g bin -m 4700 rogue ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f rogue; ln -s dm rogue; chown games.bin rogue)
E 3
E 2

lint: FRC
	lint ${CFLAGS} ${SRCS}

tags: FRC
	ctags ${SRCS}

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

curses.o: curses.c
hit.o: hit.c rogue.h /usr/include/curses.h /usr/include/stdio.h
hit.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
hit.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
init.o: init.c /usr/include/stdio.h rogue.h /usr/include/curses.h
init.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
init.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
inventory.o: inventory.c rogue.h /usr/include/curses.h /usr/include/stdio.h
inventory.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
inventory.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
level.o: level.c rogue.h /usr/include/curses.h /usr/include/stdio.h
level.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
level.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
machdep.o: machdep.c /usr/include/stdio.h /usr/include/sys/types.h
machdep.o: /usr/include/sys/file.h /usr/include/sys/stat.h
machdep.o: /usr/include/sys/time.h /usr/include/time.h /usr/include/sgtty.h
machdep.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
machdep.o: /usr/include/sys/ttydev.h /usr/include/signal.h
machdep.o: /usr/include/machine/trap.h rogue.h /usr/include/curses.h
machdep.o: /usr/include/stdio.h /usr/include/sgtty.h
main.o: main.c rogue.h /usr/include/curses.h /usr/include/stdio.h
main.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
main.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
message.o: message.c /usr/include/stdio.h rogue.h /usr/include/curses.h
message.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
message.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
monster.o: monster.c rogue.h /usr/include/curses.h /usr/include/stdio.h
monster.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
monster.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
move.o: move.c rogue.h /usr/include/curses.h /usr/include/stdio.h
move.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
move.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
object.o: object.c rogue.h /usr/include/curses.h /usr/include/stdio.h
object.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
object.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
pack.o: pack.c rogue.h /usr/include/curses.h /usr/include/stdio.h
pack.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
pack.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
play.o: play.c rogue.h /usr/include/curses.h /usr/include/stdio.h
play.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
play.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
random.o: random.c
ring.o: ring.c rogue.h /usr/include/curses.h /usr/include/stdio.h
ring.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
ring.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
room.o: room.c rogue.h /usr/include/curses.h /usr/include/stdio.h
room.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
room.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
save.o: save.c /usr/include/stdio.h rogue.h /usr/include/curses.h
save.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
save.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
score.o: score.c /usr/include/stdio.h rogue.h /usr/include/curses.h
score.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
score.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
spec_hit.o: spec_hit.c rogue.h /usr/include/curses.h /usr/include/stdio.h
spec_hit.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
spec_hit.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
throw.o: throw.c rogue.h /usr/include/curses.h /usr/include/stdio.h
throw.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
throw.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
trap.o: trap.c rogue.h /usr/include/curses.h /usr/include/stdio.h
trap.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
trap.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
use.o: use.c rogue.h /usr/include/curses.h /usr/include/stdio.h
use.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
use.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
zap.o: zap.c rogue.h /usr/include/curses.h /usr/include/stdio.h
zap.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
zap.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 1
