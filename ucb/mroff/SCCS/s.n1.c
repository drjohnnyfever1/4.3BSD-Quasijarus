h11146
s 00001/00004/01001
d D 5.15 2012/07/23 18:12:53 msokolov 15 14
c back to just one -T that does R,I,B,S,S1,ZD,SS
e
s 00003/00002/01002
d D 5.14 2012/07/17 08:29:01 msokolov 14 13
c .fz S F N is known to do nothing, so don't bother trying
e
s 00004/00001/01000
d D 5.13 2012/03/09 22:05:29 msokolov 13 12
c TroffEmu fonts restructured once again
e
s 00004/00004/00997
d D 5.12 2012/03/06 04:12:34 msokolov 12 11
c converted to ftXX files and font search paths
e
s 00007/00001/00994
d D 5.11 2012/03/05 00:07:43 msokolov 11 10
c first restructuring steps for fcXX and .bd simulation
e
s 00002/00002/00993
d D 5.10 2012/03/04 02:06:14 msokolov 10 9
c tr handles the full 512-char set now
e
s 00001/00000/00994
d D 5.9 2012/02/16 07:05:47 msokolov 9 8
c put full A.D. year in \n(Yr
e
s 00007/00000/00987
d D 5.8 10/10/07 02:11:35 msokolov 8 7
c -T option: the new way to invoke the extra compatibility fonts
e
s 00005/00000/00982
d D 5.7 10/08/29 03:35:17 msokolov 7 6
c drawing operations added to pstroff
e
s 00004/00007/00978
d D 5.6 04/10/24 20:19:51 msokolov 6 5
c use mkstemp for the temp file
e
s 00002/00000/00983
d D 5.5 04/09/16 07:45:08 msokolov 5 4
c support -t option for troff compatibility
e
s 00033/00000/00950
d D 5.4 04/09/13 01:20:00 msokolov 4 3
c \Xxx and \Sxx are here
e
s 00001/00001/00949
d D 5.3 04/09/11 10:32:36 msokolov 3 2
c call mchbits() after ptinit() as the latter reads the width tables
e
s 00001/00001/00949
d D 5.2 04/09/09 08:07:25 msokolov 2 1
c do box drawing characters by adding line-drawn chars to Symbol
c (Type3-like chars added to a Type1 font)
e
s 00950/00000/00000
d D 5.1 04/09/08 16:41:54 msokolov 1 0
c first working version
e
u
U
t
T
I 1
#ifndef lint
D 11
static char sccsid[] = "%W% (Berkeley) %G%";
E 11
I 11
static char sccsid[] = "%W% (Berkeley) %E%";
E 11
#endif lint

#include "tdef.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
extern
#include "d.h"
extern
#include "v.h"
#ifdef NROFF
extern
#include "tw.h"
#endif
#include "sdef.h"
#include <setjmp.h>
jmp_buf sjbuf;
#include	<sgtty.h>
/*
troff1.c

consume options, initialization, main loop,
input routines, escape function calling
*/

int	inchar[LNSIZE], *pinchar = inchar;	/* XXX */
extern struct s *frame, *stk, *nxf;
extern struct s *ejl, *litlev;
extern filep ip;
extern filep offset;
extern filep nextb;


extern int stdi;
extern int waitf;
extern int nofeed;
extern int quiet;
extern int ptid;
extern int ascii;
extern int npn;
extern int stop;
extern char ibuf[IBUFSZ];
extern char xbuf[IBUFSZ];
extern char *ibufp;
extern char *xbufp;
extern char *eibuf;
extern char *xeibuf;
extern int cbuf[NC];
extern int *cp;
extern int *vlist;
extern int nx;
extern int mflg;
extern int ch;
extern int pto;
extern int pfrom;
extern int chbits;
extern int ibf;
extern int ttyod;
extern struct sgttyb ttys;
extern int iflg;
extern int init;
extern int rargc;
extern char **argp;
D 10
extern char trtab[256];
E 10
I 10
extern u_short trtab[512];
E 10
extern int lgf;
extern int copyf;
extern int eschar;
extern int ch0;
extern int cwidth;
extern int nlflg;
extern int *ap;
extern int donef;
extern int nflush;
extern int nchar;
extern int rchar;
extern int nfo;
extern int ifile;
extern int fc;
extern int padc;
extern int tabc;
extern int dotc;
extern int raw;
extern int tabtab[NTAB];
extern char nextf[];
extern int nfi;
#ifdef NROFF
extern char termtab[];
extern int tti;
#endif
extern int ifl[NSO];
extern int ifi;
extern int pendt;
extern int flss;
extern int fi;
extern int lg;
extern char ptname[];
extern int print;
extern int nonumb;
extern int pnlist[];
extern int *pnp;
extern int nb;
extern int trap;
extern int tflg;
extern int ejf;
extern int lit;
extern int cc;
extern int c2;
extern int spread;
extern int oline[];
extern int *olinep;
extern int dpn;
extern int noscale;
extern char *unlkp;
extern int pts;
extern int level;
extern int ttysave;
extern int tdelim;
extern int dotT;
extern int tabch, ldrch;
extern int eqflg;
extern no_out;
extern int hflg;
D 14
#ifndef NROFF
E 14
I 14
#if 0
E 14
extern int spbits;
#endif
extern int xxx;
int stopmesg;
filep ipl[NSO];
long offl[NSO];
long ioff;
char *ttyp;
extern struct contab {
	int rq;
	union {
		int (*f)();
		unsigned mx;
	}x;
}contab[NM];
extern int fmt[NN];
#ifndef NROFF
extern int psout_omit_troffencoding;
extern int psout_8bit_strings;
extern int psout_hex_strings;
#endif

main(argc,argv)
int argc;
char **argv;
{
	char *p, *q;
	register i, j;
	extern catch(), fpecatch(), kcatch();

	signal(SIGHUP,catch);
	if(signal(SIGINT,catch) == SIG_IGN){
		signal(SIGHUP,SIG_IGN);
		signal(SIGINT,SIG_IGN);
		signal(SIGQUIT,SIG_IGN);
	}
	signal(SIGFPE,fpecatch);
	signal(SIGPIPE,catch);
	signal(SIGTERM,kcatch);
	init1(argv[0][0]);
options:
	while(--argc > 0 && (++argv)[0][0]=='-')
		switch(argv[0][1]){

		case 0:
			goto start;
		case 'i':
			stdi++;
			continue;
		case 'q':
			quiet++;
			if(gtty(0, &ttys) >= 0)
				ttysave = ttys.sg_flags;
			continue;
		case 'n':
			npn = cnum(&argv[0][2]);
			continue;
		case 'S':
			stopmesg++;
			continue;
		case 's':
			if(!(stop = cnum(&argv[0][2])))stop++;
			continue;
		case 'r':
			vlist[findr(argv[0][2])] = cnum(&argv[0][3]);
			continue;
		case 'm':
			p = &nextf[nfi];
			q = &argv[0][2];
			while((*p++ = *q++) != 0);
			if (access(nextf, 4) < 0) {
char *local = "/usr/local/lib/tmac/tmac.\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
				strcat(local, &argv[0][2]);
				if (access(local, 4) == 0)
					strcpy(nextf, local);
			}
			mflg++;
			continue;
		case 'o':
			getpn(&argv[0][2]);
			continue;
#ifdef NROFF
		case 'h':
			hflg++;
			continue;
		case 'z':
			no_out++;
			continue;
		case 'e':
			eqflg++;
			continue;
		case 'T':
			p = &termtab[tti];
			q = &argv[0][2];
			if(!((*q) & 0177))continue;
			while((*p++ = *q++) != 0);
			dotT++;
			continue;
#endif
#ifndef NROFF
		case 'z':
			no_out++;
		case 'a':
			ascii = 1;
			continue;
I 5
		case 't':		/* compatibility */
			continue;
E 5
		case 'N':
			psout_omit_troffencoding++;
			continue;
		case 'e':
			psout_8bit_strings++;
			continue;
		case 'h':
			psout_hex_strings++;
			continue;
		case 'f':
			{
			  extern char *fontlist;
			  fontlist = &argv[0][2];
			}
			continue;
		case 'F':
			{
D 12
			  extern char *fontdir;
			  fontdir = &argv[0][2];
E 12
I 12
			  extern char *fontpath;
			  fontpath = &argv[0][2];
E 12
			}
			continue;
I 8
		case 'T':
			{
D 12
			  extern char *fontdir, *fontlist;
			  fontdir = "/usr/lib/pstroff/troffemu";
E 12
I 12
			  extern char *fontpath, *fontlist;
			  fontpath = "/usr/lib/pstroff/troffemu";
E 12
D 13
			  fontlist = "R,I,B,S,SS";
E 13
I 13
D 15
			  if (argv[0][2] == 'b')
				fontlist = "R,I,B,Sv,ZD,SS";
			  else
				fontlist = "R,I,B,S,ZD,SS";
E 15
I 15
			  fontlist = "R,I,B,S,S1,ZD,SS";
E 15
E 13
I 11
			}
			continue;
		case 'b':
			{
			  extern char *bdsimlist;
			  bdsimlist = &argv[0][2];
E 11
			}
			continue;
E 8
#endif
		default:
			pto = cnum(&argv[0][1]);
			continue;
		}

	if(argv[0][0] == '+'){
		pfrom = cnum(&argv[0][1]);
		print = 0;
		if(argc > 0)goto options;
	}

start:
	argp = argv;
	rargc = argc;
	init2();
	setjmp(sjbuf);
loop:
	copyf = lgf = nb = nflush = nlflg = 0;
	if(ip && (rbf0(ip)==0) && ejf && (frame->pframe <= ejl)){
		nflush++;
		trap = 0;
		eject((struct s *)0);
		goto loop;
	}
	i = getch();
	if(pendt)goto lt;
	if(lit && (frame <= litlev)){
		lit--;
		goto lt;
	}
	if((j = (i & CMASK)) == XPAR){
		copyf++;
		tflg++;
		for(;(i & CMASK) != '\n';)pchar(i = getch());
		tflg = 0;
		copyf--;
		goto loop;
	}
	if((j == cc) || (j == c2)){
		if(j == c2)nb++;
		copyf++;
		while(((j=((i=getch()) & CMASK)) == ' ') ||
			(j == '\t'));
		ch = i;
		copyf--;
		control(getrq(),1);
		flushi();
		goto loop;
	}
lt:
	ch = i;
	text();
	goto loop;
}
catch(){
/*
	prstr("Interrupt\n");
*/
	done3(01);
}
fpecatch(){
	prstrfl("Floating Exception.\n");
	signal(SIGFPE,fpecatch);
}
kcatch(){
	signal(SIGTERM,SIG_IGN);
	done3(01);
}
init1(a)
char a;
{
D 6
	register char *p;
	char *mktemp();
E 6
I 6
	static char tmpf[] = "/tmp/taXXXXX";
E 6
	register i;

D 6
	p = mktemp("/tmp/taXXXXX");
	if(a == 'a')p = &p[5];
	if((close(creat(p, 0600))) < 0){
E 6
I 6
	ibf = mkstemp(tmpf);
	if(ibf < 0){
E 6
		prstr("Cannot create temp file.\n");
		exit(-1);
	}
D 6
	ibf = open(p, 2);
E 6
D 10
	for(i=256; --i;)trtab[i]=i;
E 10
I 10
	for(i=512; --i;)trtab[i]=i;
E 10
	trtab[UNPAD] = ' ';
	trtab['-'] = 0xAD;
D 3
	mchbits();
E 3
D 6
	if(a != 'a')unlkp = p;
E 6
I 6
	unlkp = tmpf;
E 6
}
init2()
{
	register i,j;
	extern int block;
	extern char *setbrk();
	extern char *ttyname();

	ttyod = 2;
	if(((ttyp=ttyname(j=0)) != (char *)0) ||
	   ((ttyp=ttyname(j=1)) != (char *)0) ||
	   ((ttyp=ttyname(j=2)) != (char *)0)
	  );else ttyp = "notty";
	iflg = j;
	if(ascii)mesg(0);

	ptinit();
I 3
	mchbits();
E 3
	for(i=NEV; i--;)write(ibf, (char *)&block, EVS*sizeof(int));
	olinep = oline;
	ibufp = eibuf = ibuf;
	v.hp = init = 0;
	pinchar = inchar;	/* XXX */
	ioff = 0;
	v.nl = -1;
	cvtime();
	frame = stk = (struct s *)setbrk(DELTA);
	dip = &d[0];
	nxf = frame + 1;
	nx = mflg;
}
cvtime()
{
	extern time_t time();
	time_t t;
	register struct tm *tmp;

	t = time((time_t *)0);
	tmp = localtime(&t);
	v.dy = tmp->tm_mday;
	v.dw = tmp->tm_wday + 1;
	v.yr = tmp->tm_year % 100;
	fmt[2] = 2;	/* make \n(yr 2 digits */
	v.cn = 19 + tmp->tm_year / 100;
I 9
	v.Yr = tmp->tm_year + 1900;
E 9
	v.mo = tmp->tm_mon + 1;
}
cnum(a)
char *a;
{
	register i;

	ibufp = a;
	eibuf = (char *) MAXPTR;
	i = atoi();
	ch = 0;
	return(i);
}
mesg(f)
int f;
{
	static int mode;

	if (ttyp==0)
		return;
	if(!f){
		stat(ttyp,cbuf);
		mode = ((struct stat *)(cbuf))->st_mode;
		chmod(ttyp,mode & ~022);
	}else{
		chmod(ttyp,mode);
	}
}
prstrfl(s)
char *s;
{
	flusho();
	prstr(s);
}
prstr(s)
char *s;
{
	register i;
	register char *j;

	j = s;
	for(i=0;*s;i++)s++;
	write(ttyod,j,i);
}
control(a,b)
int a,b;
{
	register i,j;
	extern filep boff();

	i = a;
	if((i == 0) || ((j = findmn(i)) == -1))return(0);
	if(contab[j].rq & MMASK){
		nxf->nargs = 0;
		if(b)collect();
		flushi();
		return(pushi(((filep)contab[j].x.mx)<<BLKBITS));
	}else{
		if(!b)return(0);
		return((*contab[j].x.f)(0));
	}
}

getrq(){
	register i,j;

	if(((i=getach()) == 0) ||
	   ((j=getach()) == 0))goto rtn;
	i = PAIR(i,j);
rtn:
	return(i);
}
getch(){
	register int i, j, k;

	level++;
g0:
	if(ch){
		if(((i = ch) & CMASK) == '\n')nlflg++;
		ch = 0;
		level--;
		return(i);
	}

	if(nlflg){
		level--;
		return('\n');
	}

	if((k = (i = getch0()) & CMASK) != ESC){
		if(i & MOT)goto g2;
		if(k == FLSS){
			copyf++; raw++;
			i = getch0();
			if(!fi)flss = i;
			copyf--; raw--;
			goto g0;
		}
		if(k == RPT){
			setrpt();
			goto g0;
		}
		if(!copyf){
			if((k == 'f') && lg && !lgf){
				i = getlg(i);
				goto g2;
			}
			if((k == fc) || (k == tabch) || (k == ldrch)){
				if((i=setfield(k)) == 0)goto g0; else goto g2;
			}
			if(k == 010){
				i = makem(-width(' ' | chbits));
				goto g2;
			}
		}
		goto g2;
	}
	k = (j = getch0()) & CMASK;
	if(j & MOT){
		i = j;
		goto g2;
	}
/*
	if(k == tdelim){
		i = TDELIM;
		tdelim = IMP;
		goto g2;
	}
*/
	switch(k){

		case '\n':	/*concealed newline*/
			goto g0;
		case 'n':	/*number register*/
			setn();
			goto g0;
		case '*':	/*string indicator*/
			setstr();
			goto g0;
		case '$':	/*argument indicator*/
			seta();
			goto g0;
		case '{':	/*LEFT*/
			i = LEFT;
			goto gx;
		case '}':	/*RIGHT*/
			i = RIGHT;
			goto gx;
		case '"':	/*comment*/
			while(((i=getch0()) & CMASK ) != '\n');
			goto g2;
		case ESC:	/*double backslash*/
			i = eschar;
			goto gx;
		case 'e':	/*printable version of current eschar*/
			i = PRESC;
			goto gx;
		case ' ':	/*unpaddable space*/
			i = UNPAD;
			goto gx;
		case '|':	/*narrow space*/
			i = NARSP;
			goto gx;
		case '^':	/*half of narrow space*/
			i = HNSP;
			goto gx;
		case '\'':	/*\(aa*/
			i = 0222;
			goto gx;
		case '`':	/*\(ga*/
			i = 0221;
			goto gx;
		case '_':	/*\(ul*/
D 2
			i = 0x15F;
E 2
I 2
			i = UNDRULE;
E 2
			goto gx;
		case '-':	/*current font minus*/
			i = CFMINUS;
			goto gx;
		case '&':	/*filler*/
			i = FILLER;
			goto gx;
		case 'c':	/*to be continued*/
			i = CONT;
			goto gx;
		case ':':	/*lem's char*/
			i = COLON;
			goto gx;
		case '!':	/*transparent indicator*/
			i = XPAR;
			goto gx;
		case 't':	/*tab*/
			i = '\t';
			goto g2;
		case 'a':	/*leader (SOH)*/
			i = LEADER;
			goto g2;
		case '%':	/*ohc*/
			i = OHC;
			goto g2;
		case '.':	/*.*/
			i = '.';
		gx:
			i = (j & ~CMASK) | i;
			goto g2;
	}
	if(!copyf)
		switch(k){

			case 'p':	/*spread*/
				spread++;
				goto g0;
			case '(':	/*special char name*/
				if((i=setch()) == 0)goto g0;
				break;
I 4
			case 'X':	/*hex char*/
				if((i=getxch()) == 0)goto g0;
				i |= chbits;
				break;
			case 'S':	/*hex Symbol char*/
				if((i=getxch()) == 0)goto g0;
				if ((i & 0x7F) < 0x20)
					goto g0;
				i |= 0x100 | chbits;
				break;
E 4
			case 's':	/*size indicator*/
				setps();
				goto g0;
			case 'f':	/*font indicator*/
				setfont(0);
				goto g0;
			case 'w':	/*width function*/
				setwd();
				goto g0;
			case 'v':	/*vert mot*/
				if(i = vmot())break;
				goto g0;
			case 'h': 	/*horiz mot*/
				if(i = hmot())break;
				goto g0;
			case 'z':	/*zero with char*/
				i = setz();
				break;
			case 'l':	/*hor line*/
				setline();
				goto g0;
			case 'L':	/*vert line*/
				setvline();
				goto g0;
			case 'b':	/*bracket*/
				setbra();
				goto g0;
			case 'o':	/*overstrike*/
				setov();
				goto g0;
I 7
#ifndef NROFF
			case 'D':
				drawop_frontend();
				goto g0;
#endif
E 7
			case 'k':	/*mark hor place*/
				if((i=findr(getsn())) == -1)goto g0;
				vlist[i] = v.hp = sumhp();	/* XXX */
				goto g0;
			case 'j':	/*mark output hor place*/
				if(!(i=getach()))goto g0;
				i = (i<<16) | JREG;
				break;
			case '0':	/*number space*/
				i = makem(width('0' | chbits));
				break;
			case 'x':	/*extra line space*/
				if(i = xlss())break;
				goto g0;
			case 'u':	/*half em up*/
			case 'r':	/*full em up*/
			case 'd':	/*half em down*/
				i = sethl(k);
				break;
			default:
				i = j;
		}
	else{
		ch0 = j;
		i = eschar;
	}
g2:
	if((i & CMASK) == '\n'){
		nlflg++;
		v.hp = 0;
		pinchar = inchar;	/* XXX */
		if(ip == 0)v.cd++;
	}
	if(!--level){
		/* j = width(i); */
		/* v.hp += j; */
		/* cwidth = j; */
		if (pinchar >= inchar + LNSIZE) {	/* XXX */
			inchar[0] = makem(sumhp());
			pinchar = &inchar[1];
		}
		*pinchar++ = i;	/* XXX */
	}
	return(i);
I 4
}

getxch(){
	register i,j;

	if ((i=getach()) == 0) goto rtn;
	if ((i=hexdigit(i)) < 0) goto rtn;
	if ((j=getach()) == 0) goto rtn;
	if ((j=hexdigit(j)) < 0) goto rtn;
	i = (i << 4) | j;
rtn:
	return(i);
}
hexdigit(c)
	register c;
{
	if (c >= '0' && c <= '9')
		return(c - '0');
	if (c >= 'A' && c <= 'F')
		return(c - 'A' + 10);
	if (c >= 'a' && c <= 'f')
		return(c - 'a' + 10);
	return(-1);
E 4
}

sumhp()	/* XXX - add up widths in inchar array */
{
	register int n;
	register int *p;

	n = 0;
	for (p = inchar; p < pinchar; p++)
		n += width(*p);
	return(n);
}
char ifilt[32] = {0,001,002,003,0,005,006,007,010,011,012};
getch0(){
	register int i, j;

	if(ch0){i=ch0; ch0=0; return(i);}
	if(nchar){nchar--; return(rchar);}

again:
	if(cp){
		if((i = *cp++) == 0){
			cp = 0;
			goto again;
		}
	}else if(ap){
		if((i = *ap++) == 0){
			ap = 0;
			goto again;
		}
	}else if(ip){
		if(ip == -1)i = rdtty();
		else i = rbf();
	}else{
		if(donef)done(0);
		if(nx || ((ibufp >= eibuf) && (eibuf != (char *) MAXPTR))){
			if(nfo)goto g1;
		g0:
			if(nextfile()){
				if(ip)goto again;
				if(ibufp < eibuf)goto g2;
			}
		g1:
			nx = 0;
			if((j=read(ifile,ibuf,IBUFSZ)) <= 0)goto g0;
			ibufp = ibuf;
			eibuf = ibuf + j;
			if(ip)goto again;
		}
	g2:
		i = *ibufp++ & 0377;
		ioff++;
		if(i >= 040)goto g4; else i = ifilt[i];
	}
	if(raw)return(i);
	if((j = i & CMASK) == IMP)goto again;
	if((i == 0) && !init)goto again;
g4:
	if((copyf == 0) && ((i & ~0x1FF) == 0) && !is_xinfo_char(i & CMASK))
D 14
#ifndef NROFF
E 14
I 14
#if 0
		/* see the comment in mchbits() in t6.c */
E 14
		if(spbits && (i >= 0x120)) i |= spbits;
		else
#endif
		i |= chbits;
	if((i & CMASK) == eschar)i = (i & ~CMASK) | ESC;
	return(i);
}
nextfile(){
	register char *p;

n0:
	if(ifile)close(ifile);
	if(nx){
		p = nextf;
		if(*p != 0)goto n1;
	}
	if(ifi > 0){
		if(popf())goto n0; /*popf error*/
		return(1); /*popf ok*/
	}
	if(rargc-- <= 0)goto n2;
	p = (argp++)[0];
n1:
	if((p[0] == '-') && (p[1] == 0)){
		ifile = 0;
	}else if((ifile=open(p,0)) < 0){
		prstr("Cannot open ");
		prstr(p);
		prstr("\n");
		nfo -= mflg;
		done(02);
	}
	nfo++;
	v.cd = 0;
	ioff = 0;
	return(0);
n2:
	if((nfo -= mflg) && !stdi)done(0);
	nfo++;
	v.cd = ifile =  stdi = mflg = 0;
	ioff = 0;
	return(0);
}
popf(){
	register i;
	register char *p, *q;
	extern char *ttyname();

	ioff = offl[--ifi];
	ip = ipl[ifi];
	if((ifile = ifl[ifi]) == 0){
		p = xbuf;
		q = ibuf;
		ibufp = xbufp;
		eibuf = xeibuf;
		while(q < eibuf)*q++ = *p++;
		return(0);
	}
	if((lseek(ifile,(long)(ioff & ~(IBUFSZ-1)),0) < 0) ||
	   ((i = read(ifile,ibuf,IBUFSZ)) < 0))return(1);
	eibuf = ibuf + i;
	ibufp = ibuf;
	if(ttyname(ifile) == (char *)0)
		if((ibufp = ibuf + (int)(ioff & (IBUFSZ-1)))  >= eibuf)return(1);
	return(0);
}
flushi(){
	if(nflush)return;
	ch = 0;
	if((ch0 & CMASK) == '\n')nlflg++;
	ch0 = 0;
	copyf++;
	while(!nlflg){
		if(donef && (frame == stk))break;
		getch();
	}
	copyf--;
	v.hp = 0;
	pinchar = inchar;	/* XXX */
}
getach(){
	register i;

	lgf++;
	if(((i = getch()) & MOT) ||
	    ((i&CMASK) == ' ') ||
	    ((i&CMASK) == '\n')||
	    (i & 0600)){
			ch = i;
			i = 0;
	}
	lgf--;
	return(i & 0177);
}
casenx(){
	lgf++;
	skip();
	getname();
	nx++;
	nextfile();
	nlflg++;
	ip = 0;
	ap = 0;
	nchar = pendt = 0;
	frame = stk;
	nxf = frame + 1;
}
getname(){
	register int i, j, k;

	lgf++;
	for(k=0; k < (NS-1); k++){
		if(((j=(i=getch()) & CMASK) <= ' ') ||
			(j > 0176))break;
		nextf[k] = j;
	}
	nextf[k] = 0;
	ch = i;
	lgf--;
	return(nextf[0]);
}
caseso(){
	register i;
	register char *p, *q;

	lgf++;
	nextf[0] = 0;
	if(skip() || !getname() || ((i=open(nextf,0)) <0) || (ifi >= NSO)) {
		prstr("can't open file ");
		prstr(nextf);
		prstr("\n");
		done(02);
	}
	flushi();
	ifl[ifi] = ifile;
	ifile = i;
	offl[ifi] = ioff;
	ioff = 0;
	ipl[ifi] = ip;
	ip = 0;
	nx++;
	nflush++;
	if(!ifl[ifi++]){
		p = ibuf;
		q = xbuf;
		xbufp = ibufp;
		xeibuf = eibuf;
		while(p < eibuf)*q++ = *p++;
	}
}

casecf(){	/* copy file without change */
	int fd, i, n;
	char buf[OBUFSZ];

	flusho();
	lgf++;
	nextf[0] = 0;
	if(skip() || !getname() || ((fd=open(nextf,0)) <0) || (ifi >= NSO)) {
		prstr("can't open file ");
		prstr(nextf);
		prstr("\n");
		done(02);
	}
	while ((n = read(fd, buf, OBUFSZ)) > 0)
		for (i = 0; i < n; i++)
			oput(buf[i]);
	flusho();
	close(fd);
}
getpn(a)
char *a;
{
	register i, neg;
	long atoi1();

	if((*a & 0177) == 0)return;
	neg = 0;
	ibufp = a;
	eibuf = (char *) MAXPTR;
	noscale++;
	while((i = getch() & CMASK) != 0)switch(i){
		case '+':
		case ',':
			continue;
		case '-':
			neg = MOT;
			goto d2;
		default:
			ch = i;
		d2:
			i = atoi1();
			if(nonumb)goto fini;
			else{
				*pnp++ = i | neg;
				neg = 0;
				if(pnp >= &pnlist[NPN-2]){
					prstr("Too many page numbers\n");
					done3(-3);
				}
			}
		}
fini:
	if(neg)*pnp++ = -2;
	*pnp = -1;
	ch = noscale = print = 0;
	pnp = pnlist;
	if(*pnp != -1)chkpn();
}
setrpt(){
	register i, j;

	copyf++;raw++;
	i = getch0();
	copyf--;raw--;
	if((i < 0) ||
	   (((j = getch0()) & CMASK) == RPT))return;
	rchar = j;
	nchar = i & BMASK;
}
E 1
