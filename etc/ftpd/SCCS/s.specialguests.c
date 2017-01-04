h23333
s 00053/00000/00000
d D 5.1 11/04/16 00:34:49 msokolov 1 0
c date and time created 11/04/16 00:34:49 by msokolov
e
u
U
t
T
I 1
/* ftpd support for "special guest" users like hhuser */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %E%";
#endif

#include <stdio.h>
#include <ctype.h>
#include <strings.h>

#define	MAX_SPECIAL_GUESTS	16
#define	GUESTUSER_NAME_BUF	16

static char special_guests_file[] = "/etc/ftpguestusers";

static char special_guest_list[MAX_SPECIAL_GUESTS][GUESTUSER_NAME_BUF];

init_special_guests()
{
	register FILE *f;
	char buf[GUESTUSER_NAME_BUF];
	register char *cp;
	int cnt;

	f = fopen(special_guests_file, "r");
	if (!f)
		return(0);
	for (cnt = 0; cnt < MAX_SPECIAL_GUESTS && fgets(buf, sizeof buf, f); ) {
		cp = index(buf, '\n');
		if (!cp)
			break;
		*cp = '\0';
		if (!isalpha(buf[0]))
			continue;
		strcpy(special_guest_list[cnt++], buf);
	}
	fclose(f);
	return(cnt);
}

is_special_guest(name)
	register char *name;
{
	register int i;

	for (i = 0; i < MAX_SPECIAL_GUESTS; i++) {
		if (!special_guest_list[i][0])
			break;
		if (!strcmp(name, special_guest_list[i]))
			return(1);
	}
	return(0);
}
E 1
