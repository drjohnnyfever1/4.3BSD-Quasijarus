h47340
s 00001/00003/00091
d D 5.2 85/08/02 17:49:21 jerry 3 2
c get rid of extra blank before '&'.
e
s 00000/00000/00094
d D 5.1 85/07/30 16:51:37 jerry 2 1
c 
e
s 00094/00000/00000
d D 1.1 85/07/30 16:39:21 jerry 1 0
c date and time created 85/07/30 16:39:21 by jerry
e
u
U
t
T
I 1
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W%	%G%
 */

/*
 *		name-list write
 */

#include "fio.h"
#include "lio.h"
#include "nmlio.h"
#include <strings.h>

int l_write(), t_putc();
LOCAL char nml_wrt[] = "namelist write";
char namelistkey_ = '&';

s_wsne(a) namelist_arglist *a;
{
	int n, first;
	struct namelistentry *entries;
	int *dimptr, *spans, ndim, nelem, offset, vlen, vtype, number;
	char *nmlist_nm, *cptr;

	nmlist_nm = a->namelist->namelistname;
	reading = NO;
	formatted = NAMELIST;
	fmtbuf = "ext namelist io";
	if(n=c_le(a,WRITE)) return(n);
	putn = t_putc;
	line_len = LINE-1;	/* so we can always add a comma */
	curunit->uend = NO;
	leof = NO;
	if(!curunit->uwrt && ! nowwriting(curunit)) err(errflag, errno, nml_wrt)

	/* begin line with " &namelistname " */
	if(recpos != 0)
D 3
		PUT('\n')  /* PUT() adds blank */
	else
		PUT(' ');
E 3
I 3
		PUT('\n');  /* PUT() adds blank */
E 3
	PUT(namelistkey_);
	while(*nmlist_nm != '\0') PUT(*nmlist_nm++);
	PUT(' ');

	/* now loop through entries writing them out */
	entries = a->namelist->names;
	first = 1;
	while( entries->varname[0] != 0 )
	{
		/* write out variable name and '=' */
		cptr = entries->varname;
		chk_len( strlen(cptr) + 3);
		if(first++ != 1) PUT(',');
		PUT(' ');
		while( *cptr != '\0') PUT(*cptr++);
		PUT('=');

		/* how many value are there? */
		if( (dimptr = entries->dimp) == NULL ) number = 1;
		else number = dimptr[1];
		/* what is element length? */
		vlen = entries->typelen;
		/* get type */
		vtype = entries->type;
		
		if(n=l_write( &number, entries->varaddr, vlen, vtype ))
				err(errflag,n,nml_wrt);
		entries++;
	}
	PUT('\n');
	PUT(namelistkey_);
	cptr = "end\n";
	while(*cptr != '\0') PUT(*cptr++);
	return(OK);
}

LOCAL
t_putc(c) char c;
{
	if(c=='\n') { 
		recpos=0;
	} else if(recpos == 0) {
		putc(' ',cf);		/* for namelist,	   */
		recpos = 2;		/* never print in column 1 */
	} else {
		recpos++;
	}
	putc(c,cf);
	return(OK);
}
E 1
