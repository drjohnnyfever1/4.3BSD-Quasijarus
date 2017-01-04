h04877
s 00006/00001/00090
d D 5.2 2012/07/18 05:21:57 msokolov 2 1
c gentle wash cycle implemented
e
s 00091/00000/00000
d D 5.1 2012/07/18 03:56:31 msokolov 1 0
c pstmerge main.c split into common.c and mergemain.c
e
u
U
t
T
I 1
/*
 * Pstmerge is a program for merging PostScript documents produced by pstroff;
 * it also performs some important finishing functions.  Pstmerge and pstfinish
 * are essentially the same program; only the main module is different.
 * This module implements the pstmerge version of main.
 *
 * Written by Michael Spacefalcon, Quasijarus Project,
 * International Free Computing Task Force.
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %E%";
#endif

#include <sys/types.h>
#include <strings.h>
#include <stdio.h>
#include "struct.h"

extern char *malloc();

char progname[] = "pstmerge";

extern int sheetalign, outpagecnt;
extern struct srcdoc *curdoc;
extern FILE *srcfile;
D 2
extern int Fflag;
E 2
I 2
extern int Fflag, gentlewash;
E 2

static int nsrcdocs;
static struct srcdoc *srcdocs;

usage()
{
	fprintf(stderr, "usage: pstmerge [-8FLNSlps] psfiles...\n");
	exit(1);
}

main(argc, argv)
	char **argv;
{
	register int i;
	extern int optind;

	process_cmdline_opts(argc, argv);
	if (!argv[optind])
		usage();
I 2
	if (gentlewash) {
		fprintf(stderr,
		"pstmerge does not support the gentle wash cycle option\n");
		exit(1);
	}
E 2
	nsrcdocs = argc - optind;
	srcdocs = (struct srcdoc *)malloc(sizeof(struct srcdoc) * nsrcdocs);
	if (!srcdocs) {
		perror("malloc");
		exit(1);
	}

	/* Pass 1: go through the source files and figure out their fonts */
	for (i = optind, curdoc = srcdocs; i < argc; i++, curdoc++) {
		curdoc->filename = argv[i];
		srcfile = fopen(curdoc->filename, "r");
		if (!srcfile) {
			perror(curdoc->filename);
			exit(1);
		}
		pass1();
		curdoc->bodyoffset = ftell(srcfile);
		fclose(srcfile);
	}
	if (Fflag)
		Fflag_mark_as_needed();

	/* Emit merged document header */
	emit_merged_header();
	emit_merged_prolog();
	emit_merged_setup();

	/* Pass 2: reopen the source files and merge the document body */
	for (i = 0, curdoc = srcdocs; i < nsrcdocs; i++, curdoc++) {
		if (sheetalign && (outpagecnt & 1))
			printf("%%%%Page: blank %d\nshowpage\n", ++outpagecnt);
		srcfile = fopen(curdoc->filename, "r");
		if (!srcfile) {
			perror(curdoc->filename);
			exit(1);
		}
		fseek(srcfile, curdoc->bodyoffset, 0);
		pass2();
		fclose(srcfile);
	}

	/* Done! */
	emit_final_trailer();
	return(0);
}
E 1
