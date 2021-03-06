/*
 * ss (BabyVAX dz) register definitions
 *
 *	@(#)ssreg.h	7.2 (Berkeley) 3/22/04
 */

/* bits in sscsr */
#define	SSCSR_TRDY	0x8000		/* Transmitter Ready */
#define	SSCSR_SA	0x2000		/* Silo Alarm */
#define	SSCSR_SAE	0x1000		/* Silo Alarm Enable */
#define	SSCSR_TLINE	0x0300		/* Transmitter line # */
#define	SSCSR_RDONE	0x0080		/* Receiver Done */
#define	SSCSR_MSE	0x0020		/* Master Scan Enable */
#define	SSCSR_CLR	0x0010		/* Reset dz */
#define	SSCSR_MAINT	0x0008		/* Maintenance mode */

/* bits in ssrbuf */
#define	SSRBUF_PE	010000
#define	SSRBUF_FE	020000
#define	SSRBUF_DO	040000

/* Line Parameter Register (LPR) */
#define	SSLPR_RXENAB	0x1000
#define	SSLPR_SPEED	0x0F00
#define	SSLPR_OPAR	0x0080
#define	SSLPR_PENABLE	0x0040
#define	SSLPR_TWOSB	0x0020
#define	SSLPR_BITS	0x0018
#define	SSLPR_BITS8	0x0018
#define	SSLPR_BITS7	0x0010
#define	SSLPR_PLINE	0x0003

#define	SSLPR_CONS	0x1E18

/* Modem control register (upper half of TCR) */
#define	SSMCTL_LLBK	0x08
#define	SSMCTL_DTR	0x04
#define	SSMCTL_DSRS	0x02
#define	SSMCTL_RTS	0x01

/* Modem Status Register (MSR) */
#define	SSMSR_SPDI	0x0800
#define	SSMSR_CD	0x0400
#define	SSMSR_DSR	0x0200
#define	SSMSR_CTS	0x0100
#define	SSMSR_RI	0x0004
#define	SSMSR_TMI	0x0001

/* ss interrupt vectors */
#define	SS_RINT_VEC	0x2C0
#define	SS_TINT_VEC	0x2C4
