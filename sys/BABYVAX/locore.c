#ifdef LOCORE
#define	P_LINK 0
#define	P_RLINK 4
#define	P_XLINK 108
#define	P_ADDR 16
#define	P_PRI 21
#define	P_STAT 23
#define	P_WCHAN 96
#define	P_TSIZE 68
#define	P_DSIZE 72
#define	P_SSIZE 76
#define	P_P0BR 104
#define	P_SZPT 66
#define	P_TEXTP 100
#define	P_FLAG 44
#define	SSLEEP 1
#define	SRUN 3
#define	UBA_BRRVR 48
#define	UH_UBA 4
#define	UH_VEC 28
#define	UH_SIZE 84
#define	RP_FLAG 12
#define	X_CADDR 64
#define	V_SWTCH 0
#define	V_TRAP 4
#define	V_SYSCALL 8
#define	V_INTR 12
#define	V_SOFT 16
#define	V_PDMA 20
#define	V_FAULTS 92
#define	V_PGREC 52
#define	V_FASTPGREC 112
#define	UPAGES 10
#define	CLSIZE 2
#define	SYSPTSIZE 3584
#define	USRPTSIZE 4096
#define	MSGBUFPTECNT 8
#define	NMBCLUSTERS 256
#define	U_PROCP 128
#define	U_ONSTACK 1296
#define	U_RU 1640
#define	RU_MINFLT 32
#else
asm(".set	U_ARG,156");
asm(".set	U_QSAVE,192");
#endif
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)rpb.s	7.1 (Berkeley) 6/5/86
 */

/*
 * This has to get loaded first (physical 0) as 780 memory restart rom
 * only looks for rpb on a 64K page boundary (doc isn't wrong,
 * it never says what size "page boundary" rpb has to be on).
 */
	.globl	_rpb
_rpb:
	.space	508
erpb:
	.space	4
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)scb.s	7.6 (Berkeley) 3/18/04
 */

#include "cpucond.h"
#include "uba.h"

/*
 * System control block
 */
	.set	INTSTK,1	# handle this interrupt on the interrupt stack
	.set	HALT,3		# halt if this interrupt occurs

_scb:	.globl	_scb

#define	KS(a)	.long	_X/**/a
#define	IS(a)	.long	_X/**/a+INTSTK
#define	STOP(a)	.long	_X/**/a+HALT

#define	STRAY(x)	.long	_scbstray+2*(x)+INTSTK
#define	STRAY3(n)	STRAY(n);STRAY(n+4);STRAY(n+8)
#define	STRAY4(n)	STRAY3(n);STRAY(n+12)
#define	STRAY15(n)	STRAY4(n);STRAY4(n+16);STRAY4(n+32);STRAY3(n+48)
#define	STRAY16(n)	STRAY15(n);STRAY(n+60)
#define	NEX0(n)	IS(nex0zvec);STRAY15(n+4)
#define	NEX1(n)	IS(nex1zvec);STRAY15(n+4)

/* 000 */	IS(passiverel);	IS(machcheck);	IS(kspnotval);	STOP(powfail);
/* 010 */	KS(privinflt);	KS(xfcflt);	KS(resopflt);	KS(resadflt);
/* 020 */	KS(protflt);	KS(transflt);	KS(tracep);	KS(bptflt);
/* 030 */	KS(compatflt);	KS(arithtrap);	STRAY(0x38);	STRAY(0x3c);
/* 040 */	KS(syscall);	KS(chme);	KS(chms);	KS(chmu);
/* 050 */	IS(sbisilo);	IS(cmrd);	IS(sbi0alert);	IS(sbi0fault);
/* 060 */	IS(wtime);	IS(sbi0fail);	STRAY(0x68);	STRAY(0x6c);
/* 070 */	STRAY(0x70);	STRAY(0x74);	STRAY(0x78);	STRAY(0x7c);
/* 080 */	STRAY(0x80);	STRAY(0x84);	KS(astflt);	STRAY(0x8c);
/* 090 */	STRAY(0x90);	STRAY(0x94);	STRAY(0x98);	STRAY(0x9c);
/* 0a0 */	IS(softclock);	STRAY(0xa4);	STRAY(0xa8);	STRAY(0xac);
/* 0b0 */	IS(netintr);	STRAY(0xb4);	STRAY(0xb8);	IS(kdbintr);
#if NEED_SAMEMODE_EMU
/* 0c0 */	IS(hardclock);	STRAY(0xc4);	KS(emulate);	KS(emulateFPD);
#else
/* 0c0 */	IS(hardclock);	STRAY(0xc4);	STRAY(0xc8);	STRAY(0xcc);
#endif
/* 0d0 */	STRAY(0xd0);	STRAY(0xd4);	STRAY(0xd8);	STRAY(0xdc);
/* 0e0 */	STRAY(0xe0);	STRAY(0xe4);	STRAY(0xe8);	STRAY(0xec);
/* 0f0 */	IS(consdin);	IS(consdout);	IS(cnrint);	IS(cnxint);
/* 100 */	NEX0(0x100);		/* ipl 0x14, nexus 0-15 */
/* 140 */	NEX0(0x140);		/* ipl 0x15, nexus 0-15 */
/* 180 */	NEX0(0x180);		/* ipl 0x16, nexus 0-15 */
/* 1c0 */	NEX0(0x1c0);		/* ipl 0x17, nexus 0-15 */

/*
 * 750 hardware reads through UNIvec (scb + 512 bytes) to find Unibus
 * interrupt vectors.  780s use this space as a jump table (lookup
 * code in locore.s makes 780s work like 750s).  Additional pages
 * of interrupt vectors for additional UBAs follow immediately.
 *
 * 8600s may use the next page as a second SCB, for which purpose we init
 * it here.  Everything else will simply replace these with Unibus vectors.
 * An additional page is provided for UBA jump tables if the second
 * scb might be present.  Other CPUs with additional scbs should expand
 * this area as needed.
 *
 * BabyVAX note: we treat the BabyVAX interrupt vector page as the second page
 * of the main SCB a la 8600.  Since no BabyVAX has interrupts at 300, 340, 380
 * or 3C0 the nex1zvec initialisation won't cause a problem.
 */
	.globl	_UNIvec
	.globl	_eUNIvec
_UNIvec:
#if VAX8600 || NEED_BABYVAX_SUPPORT
/* 200 */	STRAY16(0x200);		/* unused (?) */
/* 240 */	STRAY16(0x240);		/* sbi1fail etc. set at boot time */
/* 280 */	STRAY16(0x280);		/* unused (?) */
/* 2c0 */	STRAY16(0x2c0);		/* unused (?) */
/* 300 */	NEX1(0x300);		/* ipl 0x14, nexus 0-15, sbia 1 */
/* 340 */	NEX1(0x340);		/* ipl 0x15, nexus 0-15, sbia 1 */
/* 380 */	NEX1(0x380);		/* ipl 0x16, nexus 0-15, sbia 1 */
/* 3c0 */	NEX1(0x3c0);		/* ipl 0x17, nexus 0-15, sbia 1 */

#endif
#if NUBA > 0
		.space	512*NUBA	# 750 first/second unibus intr vector
					# UBA jump tables on 780's
#endif
_eUNIvec:
#define	I_CLOCK	0
#define	I_CNR	4
#define	I_CNX	8
#define	I_TUR	12
#define	I_TUX	16
#define	I_MBA0	20
#define	I_MBA1	24
#define	I_MBA2	28
#define	I_MBA3	32
#define	I_UBA0	36
#define	I_UBA1	40
#define	I_UBA2	44
#define	I_UBA3	48
/*
 * Copyright (c) 1980, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */

#include "psl.h"
#include "pte.h"

#include "errno.h"
#include "cmap.h"

#include "mtpr.h"
#include "trap.h"
#include "cpu.h"
#include "cpucond.h"
#include "nexus.h"
#include "cons.h"
#include "clock.h"
#include "ioa.h"
#include "ka630.h"
#include "ka650.h"
#include "ka820.h"
#include "../vaxuba/ubareg.h"
#include "../mdec/vmb.h"

#include "dz.h"
#include "ss.h"
#include "uu.h"
#include "ps.h"
#include "mba.h"
#include "uba.h"

	.set	HIGH,0x1f	# mask for total disable
	.set	MCKVEC,4	# offset into scb of machine check vector
	.set	NBPG,512
	.set	PGSHIFT,9
	.set	SYSTEM,0x80000000	# virtual address of system start

	.set	NISP,3		# number of interrupt stack pages

/*
 * User structure is UPAGES at top of user space.
 */
	.globl	_u
	.set	_u,0x80000000 - UPAGES*NBPG

	.globl	_intstack
_intstack:
	.space	NISP*NBPG
eintstack:

/*
 * Do a dump.
 * Called by auto-restart.
 * May be called manually.
 */
	.align	2
	.globl	_doadump
	.globl	_msgbufmapped
_doadump:
	nop; nop				# .word 0x0101
#define	_rpbmap	_Sysmap				# rpb, scb, UNIvec[], istack*4
	bicl2	$PG_PROT,_rpbmap
	bisl2	$PG_KW,_rpbmap
	mtpr	$0,$TBIA
	tstl	_rpb+RP_FLAG			# dump only once!
	bneq	1f
	incl	_rpb+RP_FLAG
	movl	sp,erpb
	movab	erpb,sp
	mfpr	$PCBB,-(sp)
	mfpr	$MAPEN,-(sp)
	mfpr	$IPL,-(sp)
	clrl	_msgbufmapped
	mtpr	$0,$MAPEN
	mtpr	$HIGH,$IPL
	pushr	$0x3fff
	calls	$0,_dumpsys
1:
	clrl	r11				# boot flags
	calls	$0,_vaxboot
	halt

/*
 * Interrupt vector routines
 */ 
	.globl	_waittime

#define	SCBVEC(name)	.align 2; .globl _X/**/name; _X/**/name
#define	PANIC(msg)	clrl _waittime; pushab 1f; \
			calls $1,_panic; 1: .asciz msg
#define	PRINTF(n,msg)	pushab 1f; calls $n+1,_printf; MSG(msg)
#define	MSG(msg)	.data; 1: .asciz msg; .text
#define	PUSHR		pushr $0x3f
#define	POPR		popr $0x3f

	.data
nofault: .long	0	# where to go on predicted machcheck
	.text
SCBVEC(machcheck):
	tstl	nofault
	bneq	1f
	PUSHR; pushab 6*4(sp); calls $1,_machinecheck; POPR;
	addl2 (sp)+,sp; rei
	.align	2
1:
	casel	_cpu,$1,$VAX_MAX
0:
	.word	8f-0b		# 1 is 780
	.word	5f-0b		# 2 is 750
	.word	5f-0b		# 3 is 730
	.word	7f-0b		# 4 is 8600
	.word	5f-0b		# 5 is 8200
	.word	1f-0b		# 6 is 8800 (unsupported)
	.word	1f-0b		# 7 is 610  (unsupported)
	.word	1f-0b		# 8 is 630
	.word	1f-0b		# 9 is 410
	.word	9f-0b		# 0A is 650
	.word	1f-0b		# 0B is 3100
5:
#if defined(VAX8200) || defined(VAX750) || defined(VAX730)
	mtpr	$0xf,$MCESR
#endif
	brb	1f
7:
#if VAX8600
	mtpr	$0,$EHSR
#endif
	brb	1f
8:
#if VAX780
	mtpr	$0,$SBIFS
#endif
	brb	1f
9:
#if VAX650
	bitl	$PG_V,_KA650MERRmap
	beql	1f	# don't bother clearing err reg if not mapped in
	movl	$DSER_CLEAR,_ka650merr+4
#endif
1:
	addl2	(sp)+,sp		# discard mchchk trash
	movl	nofault,(sp)
	rei

SCBVEC(kspnotval):
	PANIC("KSP not valid");
SCBVEC(powfail):
	halt
SCBVEC(chme): SCBVEC(chms): SCBVEC(chmu):
	PANIC("CHM? in kernel");

SCBVEC(nex0zvec):
	PUSHR
	clrl	r0
	brb	1f
SCBVEC(nex1zvec):
	PUSHR
	movl	$1,r0
1:
	cmpl	_cpu,$VAX_8600		# this is a frill
	beql	2f
	mfpr	$IPL,-(sp)
	PRINTF(1, "nexus stray intr ipl%x\n")
	POPR
	rei
2:
	pushl	r0
	mfpr	$IPL,-(sp)
	PRINTF(2, "nexus stray intr ipl%x sbia%d\n")
	POPR
	rei

SCBVEC(cmrd):
	PUSHR; calls $0,_memerr; POPR; rei

SCBVEC(wtime):			/* sbi0err on 8600 */
#if VAX8600
	cmpl	_cpu,$VAX_8600
	bneq	wtimo
	PANIC("sbia0 error")
wtimo:
#endif
	PUSHR; pushl 6*4(sp); PRINTF(1, "write timeout %x\n"); POPR
	PANIC("wtimo")

SCBVEC(sbi0fail):
	PANIC("sbia0 fail")
SCBVEC(sbi0alert):
#if VAX8200
	cmpl	_cpu,$VAX_8200
	bneq	alert
	PUSHR; calls $0,_rxcdintr; POPR; rei
alert:
#endif
	PANIC("sbia0 alert")
SCBVEC(sbi0fault):
	PANIC("sbia0 fault")

#ifdef notyet
#if VAX8600
SCBVEC(sbi1fail):
	PANIC("sbia1 fail")
SCBVEC(sbi1alert):
	PANIC("sbia1 alert")
SCBVEC(sbi1fault):
	PANIC("sbia1 fault")
SCBVEC(sbi1err):
	PANIC("sbia1 error")
#endif
#endif

/*
 * BI 0 bus error (8200), or SBI silo compare error (others)
 * VMS boot leaves us 1 BI error to ignore.
 */
#if VAX8200 && 0
	.data
	.align	2
_ignorebi: .globl _ignorebi
	.long	1
	.text
#endif VAX8200

SCBVEC(sbisilo):
#if VAX8200
	cmpl	_cpu,$VAX_8200
	bneq	sbisilo
#if 0
	blbs	_ignorebi,1f
#else
	blbs	_cold,1f
#endif
	PUSHR; pushl $0; calls $1,_bi_buserr; POPR
1:
	rei
#endif
sbisilo:
	PANIC("sbi silo compare error")

/*
 * SCB stray interrupt catcher.  Compute and print the actual
 * SCB vector (for fault diagnosis).
 */
	.align	2
_scbstray: .globl _scbstray
#define	PJ	PUSHR;jsb 1f
	/* 128 of 'em */
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
#if VAX8600 || NEED_BABYVAX_SUPPORT
	/* and another 128, for the second SBIA's scb */
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
#endif
#undef PJ
1:
	subl3	$_scbstray+8,(sp)+,r0
	mfpr	$IPL,-(sp)
	ashl	$-1,r0,-(sp)
/* call a C handler instead? perhaps later */
	PRINTF(2, "stray scb intr vec 0x%x ipl%x\n")
	POPR
	rei

#if NMBA > 0
SCBVEC(mba3int):
	PUSHR; incl _intrcnt+I_MBA3; pushl $3; brb 1f
SCBVEC(mba2int):
	PUSHR; incl _intrcnt+I_MBA2; pushl $2; brb 1f
SCBVEC(mba1int):
	PUSHR; incl _intrcnt+I_MBA1; pushl $1; brb 1f
SCBVEC(mba0int):
	PUSHR; incl _intrcnt+I_MBA0; pushl $0
1:	calls $1,_mbintr
	POPR
	incl	_cnt+V_INTR
	rei
#endif

#ifdef DW780
/*
 * Registers for the uba handling code
 */
#define	rUBANUM	r0
#define	rUBAHD	r1
#define	rUVEC	r3
#define	rUBA	r4
/* r2,r5 are scratch */

#define	I_UBA	I_UBA0		/* base of UBA interrupt counters */

#if NUBA > 4
SCBVEC(ua7int):
	PUSHR; movl $7,rUBANUM; moval _uba_hd+(7*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua6int):
	PUSHR; movl $6,rUBANUM; moval _uba_hd+(6*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua5int):
	PUSHR; movl $5,rUBANUM; moval _uba_hd+(5*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua4int):
	PUSHR; movl $4,rUBANUM; moval _uba_hd+(4*UH_SIZE),rUBAHD; brb 1f
#endif
SCBVEC(ua3int):
	PUSHR; movl $3,rUBANUM; moval _uba_hd+(3*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua2int):
	PUSHR; movl $2,rUBANUM; moval _uba_hd+(2*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua1int):
	PUSHR; movl $1,rUBANUM; moval _uba_hd+(1*UH_SIZE),rUBAHD; brb 1f
SCBVEC(ua0int):
	PUSHR; movl $0,rUBANUM; moval _uba_hd+(0*UH_SIZE),rUBAHD;
1:
	mfpr	$IPL,r2				/* r2 = mfpr(IPL); */
	movl	UH_UBA(rUBAHD),rUBA		/* uba = uhp->uh_uba; */
	movl	UBA_BRRVR-0x14*4(rUBA)[r2],rUVEC
					/* uvec = uba->uba_brrvr[r2-0x14] */
ubanorm:
	bleq	ubaerror 
	addl2	UH_VEC(rUBAHD),rUVEC		/* uvec += uh->uh_vec */
	bicl3	$3,(rUVEC),r1 
	jmp	2(r1)				/* 2 skips ``pushr $0x3f'' */
ubaerror:
	PUSHR; calls $0,_ubaerror; POPR		/* ubaerror r/w's r0-r5 */
	tstl rUVEC; jneq ubanorm		/* rUVEC contains result */
	incl _intrcnt+I_UBA[rUBANUM]
	incl	_cnt+V_INTR
	POPR
	rei
#endif
SCBVEC(cnrint):
	PUSHR; calls $0,_cnrint; POPR
	incl _cnt+V_INTR
	incl _intrcnt+I_CNR
	rei
SCBVEC(cnxint):
	PUSHR; calls $0,_cnxint; POPR
	incl _cnt+V_INTR
	incl _intrcnt+I_CNX
	rei
SCBVEC(hardclock):
	PUSHR
	mtpr $ICCS_RUN|ICCS_IE|ICCS_INT|ICCS_ERR,$ICCS
#if NPS > 0
	pushl	4+6*4(sp); pushl 4+6*4(sp);
	calls	$2,_psextsync
#endif
	pushl 4+6*4(sp); pushl 4+6*4(sp);
	calls $2,_hardclock			# hardclock(pc,psl)
	POPR;
	incl	_cnt+V_INTR
	incl	_intrcnt+I_CLOCK
	rei
SCBVEC(softclock):
	PUSHR
	pushl	4+6*4(sp); pushl 4+6*4(sp);
	calls	$2,_softclock			# softclock(pc,psl)
	POPR; 
	incl	_cnt+V_SOFT
	rei

#include "../net/netisr.h"
	.globl	_netisr
SCBVEC(netintr):
	PUSHR
#include "imp.h"
#if NIMP > 0
	bbcc	$NETISR_IMP,_netisr,1f; calls $0,_impintr; 1:
#endif
#ifdef INET
	bbcc	$NETISR_IP,_netisr,1f; calls $0,_ipintr; 1:
#endif
#ifdef NS
	bbcc	$NETISR_NS,_netisr,1f; calls $0,_nsintr; 1:
#endif
#include "ppp.h"
#if NPPP > 0
	bbcc	$NETISR_PPPCTL,_netisr,1f; calls $0,_pppctlintr; 1:
#endif
	bbcc	$NETISR_RAW,_netisr,1f; calls $0,_rawintr; 1:
	POPR
	incl	_cnt+V_SOFT
	rei

SCBVEC(consdin):
	PUSHR;
	incl	_intrcnt+I_TUR
	casel	_cpu,$VAX_750,$VAX_8200
0:
	.word	5f-0b		# 2 is VAX_750
	.word	3f-0b		# 3 is VAX_730
	.word	6f-0b		# 4 is VAX_8600
	.word	7f-0b		# 5 is VAX_8200
	halt
5:
#if defined(VAX750) && !defined(MRSP)
	jsb	tudma
#endif
3:
#if defined(VAX750) || defined(VAX730)
	calls	$0,_turintr
	brb	2f
#else
	halt
#endif
7:
#if VAX8200
	calls	$0,_rx50intr
	brb	2f
#else
	halt
#endif
6:
#if VAX8600
	calls	$0,_crlintr
#else
	halt
#endif
2:
	POPR
	incl	_cnt+V_INTR
	rei

#if defined(VAX750) || defined(VAX730)
SCBVEC(consdout):
	PUSHR; calls $0,_tuxintr; POPR
	incl _cnt+V_INTR
	incl _intrcnt+I_TUX
	rei
#else
SCBVEC(consdout):
	halt
#endif

#if NDZ > 0
/*
 * DZ pseudo dma routine:
 *	r0 - controller number
 */
	.align	1
	.globl	dzdma
dzdma:
	mull2	$8*20,r0
	movab	_dzpdma(r0),r3		# pdma structure base
					# for this controller
dzploop:
	movl	r3,r0	
	movl	(r0)+,r1		# device register address
	movzbl	1(r1),r2		# get line number
	bitb	$0x80,r2		# TRDY on?
	beql	dzprei			# no	
	bicb2	$0xf8,r2		# clear garbage bits
	mull2	$20,r2
	addl2	r2,r0			# point at line's pdma structure
	movl	(r0)+,r2		# p_mem
	cmpl	r2,(r0)+		# p_mem < p_end ?
	bgequ	dzpcall			# no, go call dzxint
	movb	(r2)+,6(r1)		# dztbuf = *p_mem++
	movl	r2,-8(r0)
	brb 	dzploop			# check for another line
dzprei:
	POPR
	incl	_cnt+V_PDMA
	rei

dzpcall:
	pushl	r3
	pushl	(r0)+			# push tty address
	calls	$1,*(r0)		# call interrupt rtn
	movl	(sp)+,r3
	brb 	dzploop			# check for another line
#endif

#if NSS > 0
/*
 * ss pseudo dma routine:
 *	r0 - controller number (ignored since there is only one ss)
 */
	.align	1
	.globl	ssdma
ssdma:
	movab	_sspdma,r3		# pdma structure base
					# for this controller
ssploop:
	movl	r3,r0	
	movl	(r0)+,r1		# device register address
	movzbl	1(r1),r2		# get line number
	bitb	$0x80,r2		# TRDY on?
	beql	ssprei			# no	
	bicb2	$0xf8,r2		# clear garbage bits
	mull2	$20,r2
	addl2	r2,r0			# point at line's pdma structure
	movl	(r0)+,r2		# p_mem
	cmpl	r2,(r0)+		# p_mem < p_end ?
	bgequ	sspcall			# no, go call dzxint
	movb	(r2)+,0xC(r1)		# dztbuf = *p_mem++
	movl	r2,-8(r0)
	brb 	ssploop			# check for another line
ssprei:
	POPR
	incl	_cnt+V_PDMA
	rei

sspcall:
	pushl	r3
	pushl	(r0)+			# push tty address
	calls	$1,*(r0)		# call interrupt rtn
	movl	(sp)+,r3
	brb 	ssploop			# check for another line
#endif

#if NUU > 0 && defined(UUDMA)
/*
 * Pseudo DMA routine for tu58 (on DL11)
 *	r0 - controller number
 */
	.align	1
	.globl	uudma
uudma:
	movl	_uudinfo[r0],r2
	movl	16(r2),r2		# r2 = uuaddr
	mull3	$48,r0,r3
	movab	_uu_softc(r3),r5	# r5 = uuc

	cvtwl	2(r2),r1		# c = uuaddr->rdb
	bbc	$15,r1,1f		# if (c & UUDB_ERROR)
	movl	$13,16(r5)		#	uuc->tu_state = TUC_RCVERR;
	rsb				#	let uurintr handle it
1:
	tstl	4(r5)			# if (uuc->tu_rcnt) {
	beql	1f
	movb	r1,*0(r5)		#	*uuc->tu_rbptr++ = r1
	incl	(r5)
	decl	4(r5)			#	if (--uuc->tu_rcnt)
	beql	2f			#		done
	tstl	(sp)+
	POPR				# 	registers saved in ubglue.s
	rei				# }
2:
	cmpl	16(r5),$8		# if (uuc->tu_state != TUS_GETH)
	beql	2f			# 	let uurintr handle it
1:
	rsb
2:
	mull2	$14,r0			# sizeof(uudata[ctlr]) = 14
	movab	_uudata(r0),r4		# data = &uudata[ctlr];
	cmpb	$1,(r4)			# if (data->pk_flag != TUF_DATA)
	bneq	1b
#ifdef notdef
	/* this is for command packets */
	beql	1f			# 	r0 = uuc->tu_rbptr
	movl	(r5),r0
	brb	2f
1:					# else
#endif
	movl	24(r5),r0		# 	r0 = uuc->tu_addr
2:
	movzbl	1(r4),r3		# counter to r3 (data->pk_count)
	movzwl	(r4),r1			# first word of checksum (=header)
	mfpr	$IPL,-(sp)		# s = spl5();
	mtpr	$0x15,$IPL		# to keep disk interrupts out
	clrw	(r2)			# disable receiver interrupts
3:	bbc	$7,(r2),3b		# while ((uuaddr->rcs & UUCS_READY)==0);
	cvtwb	2(r2),(r0)+		# *buffer = uuaddr->rdb & 0xff
	sobgtr	r3,1f			# continue with next byte ...
	addw2	2(r2),r1		# unless this was the last (odd count)
	brb	2f

1:	bbc	$7,(r2),1b		# while ((uuaddr->rcs & UUCS_READY)==0);
	cvtwb	2(r2),(r0)+		# *buffer = uuaddr->rdb & 0xff
	addw2	-2(r0),r1		# add to checksum..
2:
	adwc	$0,r1			# get the carry
	sobgtr	r3,3b			# loop while r3 > 0
/*
 * We're ready to get the checksum
 */
1:	bbc	$7,(r2),1b		# while ((uuaddr->rcs & UUCS_READY)==0);
	cvtwb	2(r2),12(r4)		# get first (lower) byte
1:	bbc	$7,(r2),1b
	cvtwb	2(r2),13(r4)		# ..and second
	cmpw	12(r4),r1		# is checksum ok?
	beql	1f
	movl	$14,16(r5)		# uuc->tu_state = TUS_CHKERR
	brb	2f			# exit
1:
	movl	$11,16(r5)		# uuc->tu_state = TUS_GET (ok)
2:
	movw	$0x40,(r2)		# enable receiver interrupts
	mtpr	(sp)+,$IPL		# splx(s);
	rsb				# continue processing in uurintr
#endif

#if defined(VAX750) && !defined(MRSP)
/*
 * Pseudo DMA routine for VAX-11/750 console tu58 
 *   	    (without MRSP)
 */
	.align	1
	.globl	tudma
tudma:
	movab	_tu,r5			# r5 = tu
	tstl	4(r5)			# if (tu.tu_rcnt) {
	beql	3f
	mfpr	$CSRD,r1		# get data from tu58
	movb	r1,*0(r5)		#	*tu.tu_rbptr++ = r1
	incl	(r5)
	decl	4(r5)			#	if (--tu.tu_rcnt)
	beql	1f			#		done
	tstl	(sp)+
	POPR				# 	registers saved in ubglue.s
	rei				# 	data handled, done
1:					# }
	cmpl	16(r5),$8		# if (tu.tu_state != TUS_GETH)
	beql	2f			# 	let turintr handle it
3:
	rsb
2:
	movab	_tudata,r4		# r4 = tudata
	cmpb	$1,(r4)			# if (tudata.pk_flag != TUF_DATA)
	bneq	3b			# 	let turintr handle it
1:					# else
	movl	24(r5),r1		# get buffer pointer to r1
	movzbl	1(r4),r3		# counter to r3
	movzwl	(r4),r0			# first word of checksum (=header)
	mtpr	$0,$CSRS		# disable receiver interrupts
3:
	bsbw	5f			# wait for next byte
	mfpr	$CSRD,r5
	movb	r5,(r1)+		# *buffer = rdb
	sobgtr	r3,1f			# continue with next byte ...
	mfpr	$CSRD,r2		# unless this was the last (odd count)
	brb	2f

1:	bsbw	5f			# wait for next byte
	mfpr	$CSRD,r5
	movb	r5,(r1)+		# *buffer = rdb
	movzwl	-2(r1),r2		# get the last word back from memory
2:
	addw2	r2,r0			# add to checksum..
	adwc	$0,r0			# get the carry
	sobgtr	r3,3b			# loop while r3 > 0
/*
 * We're ready to get the checksum.
 */
	bsbw	5f
	movab	_tudata,r4
	mfpr	$CSRD,r5
	movb	r5,12(r4)		# get first (lower) byte
	bsbw	5f
	mfpr	$CSRD,r5
	movb	r5,13(r4)		# ..and second
	movab	_tu,r5
	cmpw	12(r4),r0		# is checksum ok?
	beql	1f
	movl	$14,16(r5)		# tu.tu_state = TUS_CHKERR
	brb	2f			# exit
1:
	movl	$11,16(r5)		# tu.tu_state = TUS_GET
2:
	mtpr	$0x40,$CSRS		# enable receiver interrupts
	rsb				# continue processing in turintr
/*
 * Loop until a new byte is ready from
 * the tu58, make sure we don't loop forever
 */
5:
	movl	$5000,r5		# loop max 5000 times
1:
	mfpr	$CSRS,r2
	bbs	$7,r2,1f
	sobgtr	r5,1b
	movab	_tu,r5
	movl	$13,16(r5)		# return TUS_RCVERR
	tstl	(sp)+			# and let turintr handle it
1:
	rsb
#endif

/*
 * BI passive release things.
 */
SCBVEC(passiverel):
	rei				# well that was useless

/*
 * Stray UNIBUS interrupt catch routines
 */
	.data
	.align	2
#define	PJ	PUSHR;jsb _Xustray
	.globl	_catcher
_catcher:
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ
	PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ;PJ

	.globl	_cold
	.globl	_br
	.globl	_cvec
_cold:	.long	1
_br:	.long	0
_cvec:	.long	0
	.data

	.text
SCBVEC(ustray):
	blbc	_cold,1f
	mfpr	$IPL,r11
	movl	r11,_br
	subl3	$_catcher+8,(sp)+,r10
	ashl	$-1,r10,r10
	movl	r10,_cvec
	POPR
	rei
1:
	subl3	$_catcher+8,(sp)+,r0
	ashl	$-1,r0,-(sp)
	mfpr	$IPL,-(sp)
	PRINTF(2, "uba?: stray intr ipl %x vec %o\n")
	POPR
	rei

/*
 * Trap and fault vector routines
 */ 
#define	TRAP(a)	pushl $T_/**/a; jbr alltraps

/*
 * Ast delivery (profiling and/or reschedule)
 */
SCBVEC(astflt):
	pushl $0; TRAP(ASTFLT)

SCBVEC(privinflt):
#if EMULFFLT || EMULDFLT || EMULGFLT || EMULHFLT
	jsb	_Resinstr_check_emul
#endif
	pushl $0; TRAP(PRIVINFLT)

SCBVEC(xfcflt):
	pushl $0; TRAP(XFCFLT)
SCBVEC(resopflt):
	pushl $0; TRAP(RESOPFLT)
SCBVEC(resadflt):
	pushl $0; TRAP(RESADFLT)
SCBVEC(bptflt):
	pushl $0; TRAP(BPTFLT)
SCBVEC(compatflt):
	TRAP(COMPATFLT);
SCBVEC(kdbintr):
	pushl $0; TRAP(KDBTRAP)
SCBVEC(tracep):
	pushl $0; TRAP(TRCTRAP)
SCBVEC(arithtrap):
	TRAP(ARITHTRAP)
SCBVEC(protflt):
	blbs	(sp)+,segflt
	TRAP(PROTFLT)
segflt:
	TRAP(SEGFLT)

SCBVEC(transflt):
	bitl	$2,(sp)+
	bnequ	tableflt
 	jsb	Fastreclaim		# try and avoid pagein
	TRAP(PAGEFLT)
tableflt: 
	TRAP(TABLEFLT)

alltraps:
	mfpr	$USP,-(sp); calls $0,_trap; mtpr (sp)+,$USP
	incl	_cnt+V_TRAP
	addl2	$8,sp			# pop type, code
	mtpr	$HIGH,$IPL		## dont go to a higher IPL (GROT)
	rei

SCBVEC(syscall):
	pushl	$T_SYSCALL
	mfpr	$USP,-(sp); calls $0,_syscall; mtpr (sp)+,$USP
	incl	_cnt+V_SYSCALL
	addl2	$8,sp			# pop type, code
	mtpr	$HIGH,$IPL		## dont go to a higher IPL (GROT)
	rei

/*
 * System page table
 * Mbmap and Usrptmap are enlarged by CLSIZE entries
 * as they are managed by resource maps starting with index 1 or CLSIZE.
 */ 
#define	vaddr(x)	((((x)-_Sysmap)/4)*NBPG+0x80000000)
#define	SYSMAP(mname, vname, npte)			\
_/**/mname:	.globl	_/**/mname;		\
	.space	(npte)*4;				\
	.globl	_/**/vname;			\
	.set	_/**/vname,vaddr(_/**/mname)

	.data
	.align	2
	SYSMAP(Sysmap	,Sysbase	,SYSPTSIZE	)
	SYSMAP(Forkmap	,forkutl	,UPAGES		)
	SYSMAP(Xswapmap	,xswaputl	,UPAGES		)
	SYSMAP(Xswap2map,xswap2utl	,UPAGES		)
	SYSMAP(Swapmap	,swaputl	,UPAGES		)
	SYSMAP(Pushmap	,pushutl	,UPAGES		)
	SYSMAP(Vfmap	,vfutl		,UPAGES		)
	SYSMAP(CMAP1	,CADDR1		,1		)
	SYSMAP(CMAP2	,CADDR2		,1		)
	SYSMAP(mmap	,vmmap		,1		)
	SYSMAP(alignmap	,alignutl	,1		)	/* XXX */
	SYSMAP(msgbufmap,msgbuf		,MSGBUFPTECNT	)
	SYSMAP(Mbmap	,mbutl		,NMBCLUSTERS*CLSIZE+CLSIZE )
	SYSMAP(kmempt	,kmembase	,200*CLSIZE	)
#ifdef	GPROF
	SYSMAP(profmap	,profbase	,600*CLSIZE	)
#endif
	SYSMAP(vmbinfomap,vmb_info	,128		)
	SYSMAP(ekmempt	,kmemlimit	,0		)

	SYSMAP(UMBAbeg	,umbabeg	,0		)
	SYSMAP(Nexmap	,nexus		,16*MAXNNEXUS	)
#ifdef QBA
#if (QBAPAGES+UBAIOPAGES) > (UBAPAGES+UBAIOPAGES)*NUBA 
	SYSMAP(UMEMmap	,umem		,(QBAPAGES+UBAIOPAGES) )
#else
	SYSMAP(UMEMmap	,umem		,(UBAPAGES+UBAIOPAGES)*NUBA )
#endif
#else /* QBA */
	SYSMAP(UMEMmap	,umem		,(QBAPAGES+UBAIOPAGES)*NUBA )
#endif /* QBA */
#if VAX8600
	SYSMAP(Ioamap	,ioa		,MAXNIOA*IOAMAPSIZ/NBPG	)
#endif
#if VAX8200 || VAX630
	SYSMAP(Clockmap	,ka630clock	,1		)
#endif
#if VAX8200
	/* alas, the clocks on the 8200 and 630 are not quite identical */
	/* they could be shared for now, but this seemed cleaner */
	.globl _ka820clock; .set _ka820clock,_ka630clock
	SYSMAP(Ka820map	,ka820port	,1		)
	SYSMAP(RX50map	,rx50device	,1		)
#ifdef notyet
	SYSMAP(BRAMmap	,ka820bootram	,KA820_BRPAGES	)
	SYSMAP(EEPROMmap,ka820eeprom	,KA820_EEPAGES	)
#endif
#endif
#if VAX630
	SYSMAP(Ka630map	,ka630cpu	,1		)
#endif
#if VAX650
	SYSMAP(KA650MERRmap	,ka650merr	,1		)
	SYSMAP(KA650SSCmap	,ka650ssc	,3		)
	SYSMAP(KA650IPCRmap	,ka650ipcr	,1		)
#endif
#if VAX650 || VAX3100
	/*
	 * XXX This is a kludge - using KA650 structures for a different CPU
	 * But KA42's L2 cache is close enough to the 650's
	 */
	SYSMAP(KA650CBDmap	,ka650cbd	,1		)
	SYSMAP(KA650CACHEmap	,ka650cache	,KA650_CACHESIZE/NBPG )
#endif
#if NEED_BABYVAX_SUPPORT
	SYSMAP(Babyvaxmap,bv_regs	,8		)
#endif
#ifdef QBA
	/*
	 * qvss and qdss don't coexist - one map will suffice
	 * for either. qvss is 256K each and qdss is 64K each.
	 */
#include "qv.h"
#include "qd.h"
#if NQV > 0 || NQD > 0
	SYSMAP(QVmap	,qvmem		,((512*NQV)+(128*NQD)))
#endif
#endif
	SYSMAP(UMBAend	,umbaend	,0		)

	SYSMAP(Usrptmap	,usrpt		,USRPTSIZE+CLSIZE )

eSysmap:
	.globl	_Syssize
	.set	_Syssize,(eSysmap-_Sysmap)/4
	.text

/*
 * Initialization
 *
 * ipl 0x1f; mapen 0; scbb, pcbb, sbr, slr, isp, ksp not set
 *
 * We are called as a procedure with 0 or 1 arguments.
 * The optional argument is a pointer to vmb_info for the VMB boot path.
 * This argument may be 0, which is equivalent to not passing it at all.
 */
	.data
	.globl	_cpu
_cpu:	.long	0
	.globl	_cpusid
_cpusid: .long	0
	.globl	_cpusie
_cpusie: .long	0
	.text
	.globl	start
start:
	.word	0
	tstl	(ap)			# arg present?
	beql	1f			# if not, skip ahead
	movl	4(ap),_vmbinfo		# otherwise, save the address passed
1:	mtpr	$0,$ICCS
/* set system control block base and system page table params */
	mtpr	$_scb-0x80000000,$SCBB
	mtpr	$_Sysmap-0x80000000,$SBR
	mtpr	$_Syssize,$SLR
/* double map the kernel into the virtual user addresses of phys mem */
	mtpr	$_Sysmap,$P0BR
	mtpr	$_Syssize,$P0LR
/* set ISP and get cpu type */
	movl	$_intstack+NISP*NBPG,sp
	calls	$0,_cpuid
/* init RPB */
	movab	_rpb,r0
	movl	r0,(r0)+			# rp_selfref
	movab	_doadump,r1
	movl	r1,(r0)+			# rp_dumprout
	movl	$0x1f,r2
	clrl	r3
1:	addl2	(r1)+,r3; sobgtr r2,1b
	movl	r3,(r0)+			# rp_chksum
/*
 * Did we boot in the traditional BSD way?  If we did, count up memory.
 * But if we booted via VMB, take physmem from the vmb_info structure and
 * set maxmem to protect it.
 *
 * Note that counting up memory may not work on all machines and VMB booting
 * may be required for some.  On the KA410 BabyVAX, for example, the cheap
 * hardware (standard cell) has no NXM indication at all (!).
 */
	movl	_vmbinfo,r8
	beql	1f
	movl	INFO_MEMSIZ(r8),r7
	jbr	9f
1:	clrl	r7
1:	pushl	$4; pushl r7; calls $2,_badaddr; tstl r0; bneq 2f
	acbl	$MAXMEM*1024-1,$64*1024,r7,1b
2:	movl	r7,r8
#if  VAX630 || VAX650
/* reserved area at top of memory for processor specific use */
	cmpb	_cpu,$VAX_630
	beql	1f
	cmpb	_cpu,$VAX_650
	bneq	9f
	subl2	$32768,r7	# space for Qbus map registers
	brb	9f
1:
	subl2   $4096,r8	# space for console scratchpad
#endif
9:
/* clear memory from kernel bss and pages for proc 0 u. and page table */
	movab	_edata,r6; bicl2 $SYSTEM,r6
	movab	_end,r5; bicl2 $SYSTEM,r5
#ifdef KADB
	subl2	$4,r5
1:	clrl	(r6); acbl r5,$4,r6,1b		# clear just bss
	addl2	$4,r5
	bbc	$6,r11,0f			# check RB_KDB
	bicl3	$SYSTEM,r9,r5			# skip symbol & string tables
	bicl3	$SYSTEM,r9,r6			# r9 obtained from boot
#endif
0:	bisl3	$SYSTEM,r5,r9			# convert to virtual address
	addl2	$NBPG-1,r9			# roundup to next page
	addl2	$(UPAGES*NBPG)+NBPG+NBPG,r5
1:	clrq	(r6); acbl r5,$8,r6,1b
/* trap() and syscall() save r0-r11 in the entry mask (per ../h/reg.h) */
/* panic() is convenient place to save all for debugging */
	bisw2	$0x0fff,_trap
	bisw2	$0x0fff,_syscall
	bisw2	$0x0fff,_panic
	calls	$0,_fixctlrmask
/* initialize system page table: uba vectors and int stack writeable */
	clrl	r2
	movab	eintstack,r1; bbcc $31,r1,0f; 0: ashl $-PGSHIFT,r1,r1
1:	bisl3	$PG_V|PG_KW,r2,_Sysmap[r2]; aoblss r1,r2,1b
/*
 * make rpb read-only as red zone for interrupt stack
 * (scb(s) and UNIvec are write-protected later)
 */
	bicl2	$PG_PROT,_rpbmap
	bisl2	$PG_KR,_rpbmap
/* make kernel text space read-only */
	movab	_etext+NBPG-1,r1; bbcc $31,r1,0f; 0: ashl $-PGSHIFT,r1,r1
1:	bisl3	$PG_V|PG_URKR,r2,_Sysmap[r2]; aoblss r1,r2,1b
/* make kernel data, bss, read-write */
	bicl3	$SYSTEM,r9,r1; ashl $-PGSHIFT,r1,r1
1:	bisl3	$PG_V|PG_KW,r2,_Sysmap[r2]; aoblss r1,r2,1b
/* now go to mapped mode */
	mtpr	$0,$TBIA; mtpr $1,$MAPEN; jmp *$0f; 0:
/* init mem sizes */
	ashl	$-PGSHIFT,r7,_physmem
	ashl	$-PGSHIFT,r8,_maxmem
	movl	_maxmem,_freemem
/* setup context for proc[0] == Scheduler */
	bicl3	$SYSTEM|(NBPG-1),r9,r6	# make phys, page boundary
/* setup page table for proc[0] */
	ashl	$-PGSHIFT,r6,r3			# r3 = btoc(r6)
	bisl3	$PG_V|PG_KW,r3,_Usrptmap	# init first upt entry
	incl	r3
	movab	_usrpt,r0
	mtpr	r0,$TBIS
/* init p0br, p0lr */
	mtpr	r0,$P0BR
	mtpr	$0,$P0LR
/* init p1br, p1lr */
	movab	NBPG(r0),r0
	movl	$0x200000-UPAGES,r1
	mtpr	r1,$P1LR
	mnegl	r1,r1
	moval	-4*UPAGES(r0)[r1],r2
	mtpr	r2,$P1BR
/* setup mapping for UPAGES of _u */
	movl	$UPAGES,r2; movab _u+NBPG*UPAGES,r1; addl2 $UPAGES,r3; jbr 2f
1:	decl	r3
	moval	-NBPG(r1),r1;
	bisl3	$PG_V|PG_URKW,r3,-(r0)
	mtpr	r1,$TBIS
2:	sobgeq	r2,1b
/* initialize (slightly) the pcb */
	movab	UPAGES*NBPG(r1),PCB_KSP(r1)
	mnegl	$1,PCB_ESP(r1)
	mnegl	$1,PCB_SSP(r1)
	movl	r1,PCB_USP(r1)
	mfpr	$P0BR,PCB_P0BR(r1)
	mfpr	$P0LR,PCB_P0LR(r1)
	movb	$4,PCB_P0LR+3(r1)		# disable ast
	mfpr	$P1BR,PCB_P1BR(r1)
	mfpr	$P1LR,PCB_P1LR(r1)
	movl	$CLSIZE,PCB_SZPT(r1)		# init u.u_pcb.pcb_szpt
	movl	r9,PCB_R9(r1)
	movl	r10,PCB_R10(r1)
	movl	r11,PCB_R11(r1)
	movab	1f,PCB_PC(r1)			# initial pc
	clrl	PCB_PSL(r1)			# mode(k,k), ipl=0
	ashl	$PGSHIFT,r3,r3
	mtpr	r3,$PCBB			# first pcbb
/* set regs, p0br, p0lr, p1br, p1lr, astlvl, ksp and change to kernel mode */
	ldpctx
	rei
/* put signal trampoline code in u. area */
1:	movab	_u,r0
	movc3	$19,sigcode,PCB_SIGC(r0)
/* save boot device in global _bootdev */
	movl	r10,_bootdev
/* save reboot flags in global _boothowto */
	movl	r11,_boothowto
#ifdef KADB
/* save end of symbol & string table in global _bootesym */
	subl3	$NBPG-1,r9,_bootesym
#endif
/* calculate firstaddr, and call main() */
	bicl3	$SYSTEM,r9,r0; ashl $-PGSHIFT,r0,-(sp)
	addl2	$UPAGES+1,(sp); calls $1,_main
/* proc[1] == /etc/init now running here; run icode */
	pushl	$PSL_CURMOD|PSL_PRVMOD; pushl $0; rei

/* signal trampoline code: it is known that this code takes exactly 19 bytes */
/* in ../vax/pcb.h and in the movc3 above */
sigcode:
	calls	$4,8(pc)	# params pushed by sendsig
	movl	sp,ap		# calls frame built by sendsig
	chmk	$103		# cleanup mask and onsigstack
	halt			# sigreturn() does not return!
	.word	0x3f		# registers 0-5
	callg	(ap),*16(ap)	# call the signal handler
	ret			# return to code above

	.set	exec,11
	.set	exit,1
	.globl	_icode
	.globl	_initflags
	.globl	_szicode
/*
 * Icode is copied out to process 1 to exec /etc/init.
 * If the exec fails, process 1 exits.
 */
_icode:
	pushab	b`argv-l0(pc)
l0:	pushab	b`init-l1(pc)
l1:	pushl	$2
	movl	sp,ap
	chmk	$exec
	pushl	r0
	chmk	$exit

init:	.asciz	"/etc/init"
	.align	2
_initflags:
	.long	0
argv:	.long	init+5-_icode
	.long	_initflags-_icode
	.long	0
_szicode:
	.long	_szicode-_icode

/*
 * Primitives
 */ 

#ifdef GPROF
#define	ENTRY(name, regs) \
	.globl _/**/name; .align 1; _/**/name: .word regs; jsb mcount
#define	JSBENTRY(name, regs) \
	.globl _/**/name; _/**/name: \
	movl fp,-(sp); movab -12(sp),fp; pushr $(regs); jsb mcount; \
	popr $(regs); movl (sp)+,fp
#else
#define	ENTRY(name, regs) \
	.globl _/**/name; .align 1; _/**/name: .word regs
#define	JSBENTRY(name, regs) \
	.globl _/**/name; _/**/name:
#endif GPROF
#define R0 0x01
#define R1 0x02
#define R2 0x04
#define R3 0x08
#define R4 0x10
#define R5 0x20
#define R6 0x40

/*
 * badaddr(addr, len)
 *	see if access addr with a len type instruction causes a machine check
 *	len is length of access (1=byte, 2=short, 4=long)
 */
	.globl	_badaddr
_badaddr:
	.word	0
	movl	$1,r0
	mfpr	$IPL,r1
	mtpr	$HIGH,$IPL
	movl	4(ap),r3
	movl	8(ap),r4
	movab	2f,nofault		# jump to 2f on machcheck
	bbc	$0,r4,1f; tstb	(r3)
1:	bbc	$1,r4,1f; tstw	(r3)
1:	bbc	$2,r4,1f; tstl	(r3)
1:	clrl	r0			# made it w/o machine checks
2:	clrl	nofault
	mtpr	r1,$IPL
	ret

/*
 * update profiling information for the user
 * addupc(pc, &u.u_prof, ticks)
 */
ENTRY(addupc, 0)
	movl	8(ap),r2		# &u.u_prof
	subl3	8(r2),4(ap),r0		# corrected pc
	blss	9f
	extzv	$1,$31,r0,r0		# logical right shift
	extzv	$1,$31,12(r2),r1	# ditto for scale
	emul	r1,r0,$0,r0
	ashq	$-14,r0,r0
	tstl	r1
	bneq	9f
	bicl2	$1,r0
	cmpl	r0,4(r2)		# length
	bgequ	9f
	addl2	(r2),r0			# base
	probew	$3,$2,(r0)
	beql	8f
	addw2	12(ap),(r0)
9:
	ret
8:
	clrl	12(r2)
	ret

/*
 * Copy a null terminated string from the user address space into
 * the kernel address space.
 *
 * copyinstr(fromaddr, toaddr, maxlength, &lencopied)
 */
ENTRY(copyinstr, R6)
	movl	12(ap),r6		# r6 = max length
	jlss	8f
	movl	4(ap),r1		# r1 = user address
	bicl3	$~(NBPG*CLSIZE-1),r1,r2	# r2 = bytes on first page
	subl3	r2,$NBPG*CLSIZE,r2
	movl	8(ap),r3		# r3 = kernel address
1:
	cmpl	r6,r2			# r2 = min(bytes on page, length left);
	jgeq	2f
	movl	r6,r2
2:
	prober	$3,r2,(r1)		# bytes accessible?
	jeql	8f
	subl2	r2,r6			# update bytes left count
#ifdef NOSUBSINST
	# fake the locc instr. for processors that don't have it
	movl	r2,r0
6:
	tstb	(r1)+
	jeql	5f
	sobgtr	r0,6b
	jbr	7f
5:
	decl	r1
	jbr	3f
7:
#else
	locc	$0,r2,(r1)		# null byte found?
	jneq	3f
#endif
	subl2	r2,r1			# back up pointer updated by `locc'
	movc3	r2,(r1),(r3)		# copy in next piece
	movl	$(NBPG*CLSIZE),r2	# check next page
	tstl	r6			# run out of space?
	jneq	1b
	movl	$ENOENT,r0		# set error code and return
	jbr	9f
3:
	tstl	16(ap)			# return length?
	beql	4f
	subl3	r6,12(ap),r6		# actual len = maxlen - unused pages
	subl2	r0,r6			#	- unused on this page
	addl3	$1,r6,*16(ap)		#	+ the null byte
4:
	subl2	r0,r2			# r2 = number of bytes to move
	subl2	r2,r1			# back up pointer updated by `locc'
	incl	r2			# copy null byte as well
	movc3	r2,(r1),(r3)		# copy in last piece
	clrl	r0			# redundant
	ret
8:
	movl	$EFAULT,r0
9:
	tstl	16(ap)
	beql	1f
	subl3	r6,12(ap),*16(ap)
1:
	ret

/*
 * Copy a null terminated string from the kernel
 * address space to the user address space.
 *
 * copyoutstr(fromaddr, toaddr, maxlength, &lencopied)
 */
ENTRY(copyoutstr, R6)
	movl	12(ap),r6		# r6 = max length
	jlss	8b
	movl	4(ap),r1		# r1 = kernel address
	movl	8(ap),r3		# r3 = user address
	bicl3	$~(NBPG*CLSIZE-1),r3,r2	# r2 = bytes on first page
	subl3	r2,$NBPG*CLSIZE,r2
1:
	cmpl	r6,r2			# r2 = min(bytes on page, length left);
	jgeq	2f
	movl	r6,r2
2:
	probew	$3,r2,(r3)		# bytes accessible?
	jeql	8b
	subl2	r2,r6			# update bytes left count
#ifdef NOSUBSINST
	# fake the locc instr. for processors that don't have it
	movl	r2,r0
6:
	tstb	(r1)+
	jeql	5f
	sobgtr	r0,6b
	jbr	7f
5:
	decl	r1
	jbr	3b
7:
#else
	locc	$0,r2,(r1)		# null byte found?
	jneq	3b
#endif
	subl2	r2,r1			# back up pointer updated by `locc'
	movc3	r2,(r1),(r3)		# copy in next piece
	movl	$(NBPG*CLSIZE),r2	# check next page
	tstl	r6			# run out of space?
	jneq	1b
	movl	$ENOENT,r0		# set error code and return
	jbr	9b

/*
 * Copy a null terminated string from one point to another in
 * the kernel address space.
 *
 * copystr(fromaddr, toaddr, maxlength, &lencopied)
 */
ENTRY(copystr, R6)
	movl	12(ap),r6		# r6 = max length
	jlss	8b
	movl	4(ap),r1		# r1 = src address
	movl	8(ap),r3		# r3 = dest address
1:
	movzwl	$65535,r2		# r2 = bytes in first chunk
	cmpl	r6,r2			# r2 = min(bytes in chunk, length left);
	jgeq	2f
	movl	r6,r2
2:
	subl2	r2,r6			# update bytes left count
#ifdef NOSUBSINST
	# fake the locc instr. for processors that don't have it
	movl	r2,r0
6:
	tstb	(r1)+
	jeql	5f
	sobgtr	r0,6b
	jbr	7f
5:
	decl	r1
	jbr	3b
7:
#else
	locc	$0,r2,(r1)		# null byte found?
	jneq	3b
#endif
	subl2	r2,r1			# back up pointer updated by `locc'
	movc3	r2,(r1),(r3)		# copy in next piece
	tstl	r6			# run out of space?
	jneq	1b
	movl	$ENOENT,r0		# set error code and return
	jbr	9b

/* 
 * Copy specified amount of data from user space into the kernel
 * Copyin(from, to, len)
 *	r1 == from (user source address)
 *	r3 == to (kernel destination address)
 *	r5 == length
 */
	.align	1
JSBENTRY(Copyin, R1|R3|R5)
	cmpl	r5,$(NBPG*CLSIZE)	# probing one page or less ?
	bgtru	1f			# no
	prober	$3,r5,(r1)		# bytes accessible ?
	beql	ersb			# no
	movc3	r5,(r1),(r3)
/*	clrl	r0			# redundant */
	rsb
1:
	blss	ersb			# negative length?
	pushl	r6			# r6 = length
	movl	r5,r6
	bicl3	$~(NBPG*CLSIZE-1),r1,r0	# r0 = bytes on first page
	subl3	r0,$(NBPG*CLSIZE),r0
	addl2	$(NBPG*CLSIZE),r0	# plus one additional full page
	jbr	2f

ciloop:
	movc3	r0,(r1),(r3)
	movl	$(2*NBPG*CLSIZE),r0	# next amount to move
2:
	cmpl	r0,r6
	bleq	3f
	movl	r6,r0
3:
	prober	$3,r0,(r1)		# bytes accessible ?
	beql	ersb1			# no
	subl2	r0,r6			# last move?
	bneq	ciloop			# no

	movc3	r0,(r1),(r3)
/*	clrl	r0			# redundant */
	movl	(sp)+,r6		# restore r6
	rsb

ersb1:
	movl	(sp)+,r6		# restore r6
ersb:
	movl	$EFAULT,r0
	rsb

/* 
 * Copy specified amount of data from kernel to the user space
 * Copyout(from, to, len)
 *	r1 == from (kernel source address)
 *	r3 == to (user destination address)
 *	r5 == length
 */
	.align	1
JSBENTRY(Copyout, R1|R3|R5)
	cmpl	r5,$(NBPG*CLSIZE)	# moving one page or less ?
	bgtru	1f			# no
	probew	$3,r5,(r3)		# bytes writeable?
	beql	ersb			# no
	movc3	r5,(r1),(r3)
/*	clrl	r0			# redundant */
	rsb
1:
	blss	ersb			# negative length?
	pushl	r6			# r6 = length
	movl	r5,r6
	bicl3	$~(NBPG*CLSIZE-1),r3,r0	# r0 = bytes on first page
	subl3	r0,$(NBPG*CLSIZE),r0
	addl2	$(NBPG*CLSIZE),r0	# plus one additional full page
	jbr	2f

coloop:
	movc3	r0,(r1),(r3)
	movl	$(2*NBPG*CLSIZE),r0	# next amount to move
2:
	cmpl	r0,r6
	bleq	3f
	movl	r6,r0
3:
	probew	$3,r0,(r3)		# bytes writeable?
	beql	ersb1			# no
	subl2	r0,r6			# last move?
	bneq	coloop			# no

	movc3	r0,(r1),(r3)
/*	clrl	r0			# redundant */
	movl	(sp)+,r6		# restore r6
	rsb

/*
 * non-local goto's
 */
#ifdef notdef		/* this is now expanded completely inline */
	.align	1
JSBENTRY(Setjmp, R0)
	movl	fp,(r0)+	# current stack frame
	movl	(sp),(r0)	# resuming pc
	clrl	r0
	rsb
#endif

#define PCLOC 16	/* location of pc in calls frame */
#define APLOC 8		/* location of ap,fp in calls frame */
	.align	1
JSBENTRY(Longjmp, R0)
	movl	(r0)+,newfp	# must save parameters in memory as all
	movl	(r0),newpc	# registers may be clobbered.
1:
	cmpl	fp,newfp	# are we there yet?
	bgequ	2f		# yes
	moval	1b,PCLOC(fp)	# redirect return pc to us!
	ret			# pop next frame
2:
	beql	3f		# did we miss our frame?
	pushab	4f		# yep ?!?
	calls	$1,_panic
3:
	movl	newpc,r0	# all done, just return to the `setjmp'
	jmp	(r0)		# ``rsb''

	.data
newpc:	.space	4
newfp:	.space	4
4:	.asciz	"longjmp"
	.text
/*
 * setjmp that saves all registers as the call frame may not
 * be available to recover them in the usual mannor by longjmp.
 * Called before swapping out the u. area, restored by resume()
 * below.
 */
ENTRY(savectx, 0)
	movl	4(ap),r0
	movq	r6,(r0)+
	movq	r8,(r0)+
	movq	r10,(r0)+
	movq	APLOC(fp),(r0)+	# save ap, fp
	addl3	$8,ap,(r0)+	# save sp
	movl	PCLOC(fp),(r0)	# save pc
	clrl	r0
	ret

#ifdef KADB
/*
 * C library -- reset, setexit
 *
 *	reset(x)
 * will generate a "return" from
 * the last call to
 *	setexit()
 * by restoring r6 - r12, ap, fp
 * and doing a return.
 * The returned value is x; on the original
 * call the returned value is 0.
 */
ENTRY(setexit, 0)
	movab	setsav,r0
	movq	r6,(r0)+
	movq	r8,(r0)+
	movq	r10,(r0)+
	movq	8(fp),(r0)+		# ap, fp
	movab	4(ap),(r0)+		# sp
	movl	16(fp),(r0)		# pc
	clrl	r0
	ret

ENTRY(reset, 0)
	movl	4(ap),r0	# returned value
	movab	setsav,r1
	movq	(r1)+,r6
	movq	(r1)+,r8
	movq	(r1)+,r10
	movq	(r1)+,r12
	movl	(r1)+,sp
	jmp 	*(r1)

	.data
	.align  2
setsav:	.space	10*4
	.text
#endif

	.globl	_whichqs
	.globl	_qs
	.globl	_cnt

	.globl	_noproc
	.comm	_noproc,4
	.globl	_runrun
	.comm	_runrun,4

/*
 * The following primitives use the fancy VAX instructions
 * much like VMS does.  _whichqs tells which of the 32 queues _qs
 * have processes in them.  Setrq puts processes into queues, Remrq
 * removes them from queues.  The running process is on no queue,
 * other processes are on a queue related to p->p_pri, divided by 4
 * actually to shrink the 0-127 range of priorities into the 32 available
 * queues.
 */

/*
 * Setrq(p), using fancy VAX instructions.
 *
 * Call should be made at splclock(), and p->p_stat should be SRUN
 */
	.align	1
JSBENTRY(Setrq, R0)
	tstl	P_RLINK(r0)		## firewall: p->p_rlink must be 0
	beql	set1			##
	pushab	set3			##
	calls	$1,_panic		##
set1:
	movzbl	P_PRI(r0),r1		# put on queue which is p->p_pri / 4
	ashl	$-2,r1,r1
	movaq	_qs[r1],r2
	insque	(r0),*4(r2)		# at end of queue
	bbss	r1,_whichqs,set2	# mark queue non-empty
set2:
	rsb

set3:	.asciz	"setrq"

/*
 * Remrq(p), using fancy VAX instructions
 *
 * Call should be made at splclock().
 */
	.align	1
JSBENTRY(Remrq, R0)
	movzbl	P_PRI(r0),r1
	ashl	$-2,r1,r1
	bbsc	r1,_whichqs,rem1
	pushab	rem3			# it wasn't recorded to be on its q
	calls	$1,_panic
rem1:
	remque	(r0),r2
	beql	rem2
	bbss	r1,_whichqs,rem2
rem2:
	clrl	P_RLINK(r0)		## for firewall checking
	rsb

rem3:	.asciz	"remrq"

/*
 * Masterpaddr is the p->p_addr of the running process on the master
 * processor.  When a multiprocessor system, the slave processors will have
 * an array of slavepaddr's.
 */
	.globl	_masterpaddr
	.data
_masterpaddr:
	.long	0

	.text
sw0:	.asciz	"swtch"

/*
 * When no processes are on the runq, Swtch branches to idle
 * to wait for something to come ready.
 */
	.globl	Idle
Idle: idle:
	movl	$1,_noproc
	mtpr	$0,$IPL			# must allow interrupts here
1:
	tstl	_whichqs		# look for non-empty queue
	bneq	sw1
	brb	1b

badsw:	pushab	sw0
	calls	$1,_panic
	/*NOTREACHED*/

/*
 * Swtch(), using fancy VAX instructions
 */
	.align	1
JSBENTRY(Swtch, 0)
	incl	_cnt+V_SWTCH
sw1:	ffs	$0,$32,_whichqs,r0	# look for non-empty queue
	beql	idle			# if none, idle
	mtpr	$0x18,$IPL		# lock out all so _whichqs==_qs
	bbcc	r0,_whichqs,sw1		# proc moved via interrupt
	movaq	_qs[r0],r1
	remque	*(r1),r2		# r2 = p = highest pri process
	bvs	badsw			# make sure something was there
	beql	sw2
	insv	$1,r0,$1,_whichqs	# still more procs in this queue
sw2:
	clrl	_noproc
	clrl	_runrun
#ifdef notdef
	tstl	P_WCHAN(r2)		## firewalls
	bneq	badsw			##
	cmpb	P_STAT(r2),$SRUN	##
	bneq	badsw			##
#endif
	clrl	P_RLINK(r2)		##
	movl	*P_ADDR(r2),r0
#ifdef notdef
	cmpl	r0,_masterpaddr		# resume of current proc is easy
	beql	res0
#endif
	movl	r0,_masterpaddr
	ashl	$PGSHIFT,r0,r0		# r0 = pcbb(p)
/* fall into... */

/*
 * Resume(pf)
 */
JSBENTRY(Resume, R0)
	mtpr	$HIGH,$IPL			# no interrupts, please
	movl	_CMAP2,_u+PCB_CMAP2	# yech
	svpctx
	mtpr	r0,$PCBB
	ldpctx
	movl	_u+PCB_CMAP2,_CMAP2	# yech
	mtpr	$_CADDR2,$TBIS
res0:
	tstl	_u+PCB_SSWAP
	bneq	res1
	rei
res1:
	movl	_u+PCB_SSWAP,r0			# longjmp to saved context
	clrl	_u+PCB_SSWAP
	movq	(r0)+,r6			# restore r6, r7
	movq	(r0)+,r8			# restore r8, r9
	movq	(r0)+,r10			# restore r10, r11
	movq	(r0)+,r12			# restore ap, fp
	movl	(r0)+,r1			# saved sp
	cmpl	r1,sp				# must be a pop
	bgequ	1f
	pushab	2f
	calls	$1,_panic
	/* NOTREACHED */
1:
	movl	r1,sp				# restore sp
	pushl	$PSL_PRVMOD			# return psl
	pushl	(r0)				# address to return to
	rei

2:	.asciz	"ldctx"

/*
 * {fu,su},{byte,word}, all massaged by asm.sed to jsb's
 */
	.align	1
JSBENTRY(Fuword, R0)
	prober	$3,$4,(r0)
	beql	fserr
	movl	(r0),r0
	rsb
fserr:
	mnegl	$1,r0
	rsb

	.align	1
JSBENTRY(Fubyte, R0)
	prober	$3,$1,(r0)
	beql	fserr
	movzbl	(r0),r0
	rsb

	.align	1
JSBENTRY(Suword, R0|R1)
	probew	$3,$4,(r0)
	beql	fserr
	movl	r1,(r0)
	clrl	r0
	rsb

	.align	1
JSBENTRY(Subyte, R0|R1)
	probew	$3,$1,(r0)
	beql	fserr
	movb	r1,(r0)
	clrl	r0
	rsb

/*
 * Copy 1 relocation unit (NBPG bytes)
 * from user virtual address to physical address
 */
ENTRY(copyseg, 0)
	bisl3	$PG_V|PG_KW,8(ap),_CMAP2
	mtpr	$_CADDR2,$TBIS	# invalidate entry for copy 
	movc3	$NBPG,*4(ap),_CADDR2
	ret

/*
 * zero out physical memory
 * specified in relocation units (NBPG bytes)
 */
ENTRY(clearseg, 0)
	bisl3	$PG_V|PG_KW,4(ap),_CMAP1
	mtpr	$_CADDR1,$TBIS
	movc5	$0,(sp),$0,$NBPG,_CADDR1
	ret

/*
 * Check address.
 * Given virtual address, byte count, and rw flag
 * returns 0 on no access.
 */
ENTRY(useracc, 0)
	movl	4(ap),r0		# get va
	movl	8(ap),r1		# count
	tstl	12(ap)			# test for read access ?
	bneq	userar			# yes
	cmpl	$NBPG,r1			# can we do it in one probe ?
	bgeq	uaw2			# yes
uaw1:
	probew	$3,$NBPG,(r0)
	beql	uaerr			# no access
	addl2	$NBPG,r0
	acbl	$NBPG+1,$-NBPG,r1,uaw1
uaw2:
	probew	$3,r1,(r0)
	beql	uaerr
	movl	$1,r0
	ret

userar:
	cmpl	$NBPG,r1
	bgeq	uar2
uar1:
	prober	$3,$NBPG,(r0)
	beql	uaerr
	addl2	$NBPG,r0
	acbl	$NBPG+1,$-NBPG,r1,uar1
uar2:
	prober	$3,r1,(r0)
	beql	uaerr
	movl	$1,r0
	ret
uaerr:
	clrl	r0
	ret

/*
 * kernacc - check for kernel access privileges
 *
 * We can't use the probe instruction directly because
 * it ors together current and previous mode.
 */
 ENTRY(kernacc, 0)
	movl	4(ap),r0	# virtual address
	bbcc	$31,r0,kacc1
	bbs	$30,r0,kacerr
	mfpr	$SBR,r2		# address and length of page table (system)
	bbss	$31,r2,0f; 0:
	mfpr	$SLR,r3
	brb	kacc2
kacc1:
	bbsc	$30,r0,kacc3
	mfpr	$P0BR,r2	# user P0
	mfpr	$P0LR,r3
	brb	kacc2
kacc3:
	mfpr	$P1BR,r2	# user P1 (stack)
	mfpr	$P1LR,r3
kacc2:
	addl3	8(ap),r0,r1	# ending virtual address
	addl2	$NBPG-1,r1
	ashl	$-PGSHIFT,r0,r0
	ashl	$-PGSHIFT,r1,r1
	bbs	$31,4(ap),kacc6
	bbc	$30,4(ap),kacc6
	cmpl	r0,r3		# user stack
	blss	kacerr		# address too low
	brb	kacc4
kacc6:
	cmpl	r1,r3		# compare last page to P0LR or SLR
	bgtr	kacerr		# address too high
kacc4:	
	movl	(r2)[r0],r3
	bbc	$31,4(ap),kacc4a
	bbc	$31,r3,kacerr	# valid bit is off
kacc4a:
	cmpzv	$27,$4,r3,$1	# check protection code
	bleq	kacerr		# no access allowed
	tstb	12(ap)
	bneq	kacc5		# only check read access
	cmpzv	$27,$2,r3,$3	# check low 2 bits of prot code
	beql	kacerr		# no write access
kacc5:
	aoblss	r1,r0,kacc4	# next page
	movl	$1,r0		# no errors
	ret
kacerr:
	clrl	r0		# error
	ret
/*
 * Extracted and unrolled most common case of pagein (hopefully):
 *	resident and not on free list (reclaim of page is purely
 *	for the purpose of simulating a reference bit)
 *
 * Built in constants:
 *	CLSIZE of 2, any bit fields in pte's
 */
	.text
	.globl	Fastreclaim
Fastreclaim:
	PUSHR
#ifdef GPROF
	movl	fp,-(sp)
	movab	12(sp),fp
	jsb	mcount
	movl	(sp)+,fp
#endif GPROF
	extzv	$9,$23,28(sp),r3	# virtual address
	bicl2	$1,r3			# v = clbase(btop(virtaddr)); 
	movl	_u+U_PROCP,r5		# p = u.u_procp 
					# from vtopte(p, v) ...
	movl	$1,r2			# type = CTEXT;
	cmpl	r3,P_TSIZE(r5)
	jlssu	1f			# if (isatsv(p, v)) {
	addl3	P_TSIZE(r5),P_DSIZE(r5),r0
	cmpl	r3,r0
	jgequ	2f
	clrl	r2			#	type = !CTEXT;
1:
	ashl	$2,r3,r4
	addl2	P_P0BR(r5),r4		#	tptopte(p, vtotp(p, v));
	jbr	3f
2:
	cvtwl	P_SZPT(r5),r4		# } else (isassv(p, v)) {
	ashl	$7,r4,r4
	subl2	$0x400000,r4
	addl2	r3,r4
	ashl	$2,r4,r4
	addl2	P_P0BR(r5),r4		#	sptopte(p, vtosp(p, v));
	clrl	r2			# 	type = !CTEXT;
3:					# }
	bitb	$0x82,3(r4)
	beql	2f			# if (pte->pg_v || pte->pg_fod)
	POPR; rsb			#	let pagein handle it
2:
	bicl3	$0xffe00000,(r4),r0
	jneq	2f			# if (pte->pg_pfnum == 0)
	POPR; rsb			# 	let pagein handle it 
2:
	subl2	_firstfree,r0
	ashl	$-1,r0,r0	
	incl	r0			# pgtocm(pte->pg_pfnum) 
	mull2	$SZ_CMAP,r0
	addl2	_cmap,r0		# &cmap[pgtocm(pte->pg_pfnum)] 
	tstl	r2
	jeql	2f			# if (type == CTEXT &&
	jbc	$C_INTRANS,(r0),2f	#     c_intrans)
	POPR; rsb			# 	let pagein handle it
2:
	jbc	$C_FREE,(r0),2f		# if (c_free)
	POPR; rsb			# 	let pagein handle it 
2:
	bisb2	$0x80,3(r4)		# pte->pg_v = 1;
	jbc	$26,4(r4),2f		# if (anycl(pte, pg_m) 
	bisb2	$0x04,3(r4)		#	pte->pg_m = 1;
2:
	bicw3	$0x7f,2(r4),r0
	bicw3	$0xff80,6(r4),r1
	bisw3	r0,r1,6(r4)		# distcl(pte);
	ashl	$PGSHIFT,r3,r0
	mtpr	r0,$TBIS
	addl2	$NBPG,r0
	mtpr	r0,$TBIS		# tbiscl(v); 
	tstl	r2
	jeql	2f			# if (type == CTEXT) 
	movl	P_TEXTP(r5),r0
	movl	X_CADDR(r0),r5		# for (p = p->p_textp->x_caddr; p; ) {
	jeql	2f
	ashl	$2,r3,r3
3:
	addl3	P_P0BR(r5),r3,r0	#	tpte = tptopte(p, tp);
	bisb2	$1,P_FLAG+3(r5)		#	p->p_flag |= SPTECHG;
	movl	(r4),(r0)+		#	for (i = 0; i < CLSIZE; i++)
	movl	4(r4),(r0)		#		tpte[i] = pte[i];
	movl	P_XLINK(r5),r5		#	p = p->p_xlink;
	jneq	3b			# }
2:					# collect a few statistics...
	incl	_u+U_RU+RU_MINFLT	# u.u_ru.ru_minflt++;
	moval	_cnt,r0
	incl	V_FAULTS(r0)		# cnt.v_faults++; 
	incl	V_PGREC(r0)		# cnt.v_pgrec++;
	incl	V_FASTPGREC(r0)		# cnt.v_fastpgrec++;
	incl	V_TRAP(r0)		# cnt.v_trap++;
	POPR
	addl2	$8,sp			# pop pc, code
	mtpr	$HIGH,$IPL		## dont go to a higher IPL (GROT)
	rei
	.globl	_Xssrint0
	.align	2
_Xssrint0:
	pushr	$0x3f
	incl	_fltintrcnt+(4*0)
	pushl	$0
	calls	$1,_ssrint
	popr	$0x3f
	incl	_cnt+V_INTR
	rei

	.globl	_Xssxint0
	.align	2
_Xssxint0:
	pushr	$0x3f
	incl	_fltintrcnt+(4*1)
	pushl	$0
	calls	$1,_ssxint
	popr	$0x3f
	incl	_cnt+V_INTR
	rei


	.globl	_intrnames

	.globl	_eintrnames
	.data
_intrnames:
	.asciz	"clock"
	.asciz	"cnr"
	.asciz	"cnx"
	.asciz	"tur"
	.asciz	"tux"
	.asciz	"mba0"
	.asciz	"mba1"
	.asciz	"mba2"
	.asciz	"mba3"
	.asciz	"uba0"
	.asciz	"uba1"
	.asciz	"uba2"
	.asciz	"uba3"
	.asciz	"ssr0"
	.asciz	"ssx0"
_eintrnames:

	.globl	_intrcnt

	.globl	_eintrcnt
	.align 2
_intrcnt:
	.space	4 * 13
_fltintrcnt:
	.space	4 * 2
_eintrcnt:

	.text
