h07054
s 00032/00000/00000
d D 7.1 03/11/16 14:22:51 msokolov 1 0
c date and time created 03/11/16 14:22:51 by msokolov
e
u
U
t
T
I 1
#
# Copyright (c) 1980, 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W% (Berkeley) %G%
#
# Make an 8200 rx50 floppy
# 
BOOTS=	boot
STDBOO=	defboo.cmd anyboo.cmd sngboo.cmd
UTILS=	format copy drtest

# order is NOT random! boot58.exe must be first, the bootblock depends on it
# starting at block 14. If boot58.exe ever changes location or size, the
# bootblock will need to be patched.
OBJS=	boot58.exe ${BOOTS} ${STDBOO} ${UTILS} consol.hlp

FLOPPY=	/dev/csa1

all:	rx50

rx50:	bootblk ${OBJS}
	cp /dev/null rx50
	arff mcrf rx50 ${OBJS}
	dd if=bootblk of=rx50 bs=512 count=1

install: rx50
	dd if=rx50 of=${FLOPPY}

clean:
	rm -f ${BOOTS} ${UTILS} rx50
E 1
