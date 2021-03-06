.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
.\"
.\"	@(#)appendix.ms	6.1 (Berkeley) 4/20/86
.\"
.nr H2 1
.ds RH Appendix A
.SH
\s+2Appendix A\s0
.SH
read_8192
.DS
#define	BUFSIZ 8192
main( argc, argv)
char **argv;
{
	char buf[BUFSIZ];
	int i, j;

	j = open(argv[1], 0);
	for (i = 0; i < 1024; i++)
		read(j, buf, BUFSIZ);
}
.DE
.SH
write_4096
.DS
#define	BUFSIZ 4096
main( argc, argv)
char **argv;
{
	char buf[BUFSIZ];
	int i, j;

	j = creat(argv[1], 0666);
	for (i = 0; i < 2048; i++)
		write(j, buf, BUFSIZ);
}
.DE
.SH
write_8192
.DS
#define	BUFSIZ 8192
main( argc, argv)
char **argv;
{
	char buf[BUFSIZ];
	int i, j;

	j = creat(argv[1], 0666);
	for (i = 0; i < 1024; i++)
		write(j, buf, BUFSIZ);
}
.DE
.bp
.SH
rewrite_8192
.DS
#define	BUFSIZ 8192
main( argc, argv)
char **argv;
{
	char buf[BUFSIZ];
	int i, j;

	j = open(argv[1], 2);
	for (i = 0; i < 1024; i++)
		write(j, buf, BUFSIZ);
}
.DE
