h25333
s 00020/00000/00000
d D 5.1 86/11/03 20:00:12 mckusick 1 0
c from CCI
e
u
U
t
T
I 1
/*
 *	%W% (Berkeley) %G%
 */

/* f77 interface to system routine */

system_(s, n)
register char *s;
long int n;
{
char buff[1001];
register char *bp, *blast;

blast = buff + (n<1000 ? n : 1000L);

for(bp = buff ; bp<blast && *s!='\0' ; )
	*bp++ = *s++;
*bp = '\0';
system(buff);
}
E 1