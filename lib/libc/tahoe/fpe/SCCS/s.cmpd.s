h54957
s 00004/00000/00043
d D 1.2 86/07/02 16:27:04 sam 2 1
c add sccsid
e
s 00043/00000/00000
d D 1.1 86/07/02 16:25:46 sam 1 0
c date and time created 86/07/02 16:25:46 by sam
e
u
U
t
T
I 2
#ifdef LIBC_SCCS
	.asciz	"%W% (Berkeley/CCI) %G%"
#endif LIBC_SCCS

E 2
I 1
#include "DEFS.h"

XENTRY(cmpd, R12|R11|R10|R9)
	movl	4(fp),r12
	movl	8(fp),r10
	movl	12(fp),r11
	movl	16(fp),r9
	tstl	r12
	jgeq	L16
	xorl2	$-2147483648,r12
	tstl	r10
	jeql	L17
	mnegl	r10,r10
	mcoml	r12,r12
	jbr	L16
L17:	mnegl	r12,r12
L16:	tstl	r11
	jgeq	L19
	xorl2	$-2147483648,r11
	tstl	r9
	jeql	L20
	mnegl	r9,r9
	mcoml	r11,r11
	jbr	L19
L20:	mnegl	r11,r11
L19:	cmpl	r12,r11
	jeql	L22
	cmpl	r12,r11
	jleq	L9999
	movl	$1,r0
	jbr	L9998
L9999:	mnegl	$1,r0
L9998:	ret
L22:	cmpl	r10,r9
	jeql	L23
	cmpl	r10,r9
	jlequ	L9997
	movl	$1,r0
	jbr	L9996
L9997:	mnegl	$1,r0
L9996:	ret
L23:	clrl	r0
	ret
E 1
