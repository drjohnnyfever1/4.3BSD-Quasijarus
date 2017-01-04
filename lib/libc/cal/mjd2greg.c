/*
 * This function implements the guts of the Gregorian date calculation
 * for the localtime() and gmtime() legacy interfaces, and is used
 * in the Quasijarus reimplementation of the latter.
 * It is not documented in a man page and should not be used from
 * outside of the libc implementation.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)mjd2greg.c	5.1 (IFCTF) 2012/06/20";
#endif LIBC_SCCS and not lint

#include <sys/types.h>
#include <calendardefs.h>
#include <time.h>

#define	MJD_1600_03_01	-94493
#define	MJD_1900_01_01	15020
#define	MJD_9999_12_31	2973483

#define	MAR_THRU_DEC	(365 - 31 - 28)

static struct mon_day {
	u_char	month;	/* tm_mon style, i.e., off by one */
	u_char	day;
} lut[366] = {
	/* March */
	{2,1}, {2,2}, {2,3}, {2,4}, {2,5}, {2,6}, {2,7}, {2,8}, {2,9},
	{2,10},{2,11},{2,12},{2,13},{2,14},{2,15},{2,16},{2,17},{2,18},{2,19},
	{2,20},{2,21},{2,22},{2,23},{2,24},{2,25},{2,26},{2,27},{2,28},{2,29},
	{2,30},{2,31},
	/* April */
	{3,1}, {3,2}, {3,3}, {3,4}, {3,5}, {3,6}, {3,7}, {3,8}, {3,9},
	{3,10},{3,11},{3,12},{3,13},{3,14},{3,15},{3,16},{3,17},{3,18},{3,19},
	{3,20},{3,21},{3,22},{3,23},{3,24},{3,25},{3,26},{3,27},{3,28},{3,29},
	{3,30},
	/* May */
	{4,1}, {4,2}, {4,3}, {4,4}, {4,5}, {4,6}, {4,7}, {4,8}, {4,9},
	{4,10},{4,11},{4,12},{4,13},{4,14},{4,15},{4,16},{4,17},{4,18},{4,19},
	{4,20},{4,21},{4,22},{4,23},{4,24},{4,25},{4,26},{4,27},{4,28},{4,29},
	{4,30},{4,31},
	/* June */
	{5,1}, {5,2}, {5,3}, {5,4}, {5,5}, {5,6}, {5,7}, {5,8}, {5,9},
	{5,10},{5,11},{5,12},{5,13},{5,14},{5,15},{5,16},{5,17},{5,18},{5,19},
	{5,20},{5,21},{5,22},{5,23},{5,24},{5,25},{5,26},{5,27},{5,28},{5,29},
	{5,30},
	/* July */
	{6,1}, {6,2}, {6,3}, {6,4}, {6,5}, {6,6}, {6,7}, {6,8}, {6,9},
	{6,10},{6,11},{6,12},{6,13},{6,14},{6,15},{6,16},{6,17},{6,18},{6,19},
	{6,20},{6,21},{6,22},{6,23},{6,24},{6,25},{6,26},{6,27},{6,28},{6,29},
	{6,30},{6,31},
	/* August */
	{7,1}, {7,2}, {7,3}, {7,4}, {7,5}, {7,6}, {7,7}, {7,8}, {7,9},
	{7,10},{7,11},{7,12},{7,13},{7,14},{7,15},{7,16},{7,17},{7,18},{7,19},
	{7,20},{7,21},{7,22},{7,23},{7,24},{7,25},{7,26},{7,27},{7,28},{7,29},
	{7,30},{7,31},
	/* September */
	{8,1}, {8,2}, {8,3}, {8,4}, {8,5}, {8,6}, {8,7}, {8,8}, {8,9},
	{8,10},{8,11},{8,12},{8,13},{8,14},{8,15},{8,16},{8,17},{8,18},{8,19},
	{8,20},{8,21},{8,22},{8,23},{8,24},{8,25},{8,26},{8,27},{8,28},{8,29},
	{8,30},
	/* October */
	{9,1}, {9,2}, {9,3}, {9,4}, {9,5}, {9,6}, {9,7}, {9,8}, {9,9},
	{9,10},{9,11},{9,12},{9,13},{9,14},{9,15},{9,16},{9,17},{9,18},{9,19},
	{9,20},{9,21},{9,22},{9,23},{9,24},{9,25},{9,26},{9,27},{9,28},{9,29},
	{9,30},{9,31},
	/* November */
	{10,1}, {10,2}, {10,3}, {10,4}, {10,5}, {10,6}, {10,7}, {10,8}, {10,9},
	{10,10},{10,11},{10,12},{10,13},{10,14},{10,15},{10,16},{10,17},
	{10,18},{10,19},{10,20},{10,21},{10,22},{10,23},{10,24},{10,25},
	{10,26},{10,27},{10,28},{10,29},{10,30},
	/* December */
	{11,1}, {11,2}, {11,3}, {11,4}, {11,5}, {11,6}, {11,7}, {11,8}, {11,9},
	{11,10},{11,11},{11,12},{11,13},{11,14},{11,15},{11,16},{11,17},
	{11,18},{11,19},{11,20},{11,21},{11,22},{11,23},{11,24},{11,25},
	{11,26},{11,27},{11,28},{11,29},{11,30},{11,31},
	/* January */
	{0,1}, {0,2}, {0,3}, {0,4}, {0,5}, {0,6}, {0,7}, {0,8}, {0,9},
	{0,10},{0,11},{0,12},{0,13},{0,14},{0,15},{0,16},{0,17},{0,18},{0,19},
	{0,20},{0,21},{0,22},{0,23},{0,24},{0,25},{0,26},{0,27},{0,28},{0,29},
	{0,30},{0,31},
	/* February */
	{1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7}, {1,8}, {1,9},
	{1,10},{1,11},{1,12},{1,13},{1,14},{1,15},{1,16},{1,17},{1,18},{1,19},
	{1,20},{1,21},{1,22},{1,23},{1,24},{1,25},{1,26},{1,27},{1,28},{1,29},
};

_mjd2greg(tm)
	register struct tm *tm;
{
	register long day;
	register int year, quot;
	int big_cycles;

	if (tm->tm_mjd < MJD_1900_01_01) {
		tm->tm_year = 0;
		tm->tm_mon = 0;
		tm->tm_mday = 1;
		tm->tm_yday = 0;
		return -1;
	}
	if (tm->tm_mjd > MJD_9999_12_31) {
		tm->tm_year = 9999 - 1900;
		tm->tm_mon = 11;
		tm->tm_mday = 31;
		tm->tm_yday = 364;
		return -1;
	}

	/*
	 * The following algorithm is a slight modification
	 * of djb's caldate_frommjd from libtai-0.60.
	 */
	day = tm->tm_mjd - MJD_1600_03_01;
	big_cycles = day / GREG400Y;
	day -= big_cycles * GREG400Y;

	if (day == (GREG400Y - 1)) {
		year = 399;
		day = 365;
	} else {
		quot = day / 36524L;
		year = quot * 100;
		day -= quot * 36524L;
		quot = day / 1461L;
		year += quot * 4;
		day -= quot * 1461L;
		if (day == 1460) {
			year += 3;
			day = 365;
		} else {
			quot = day / 365;
			year += quot;
			day -= quot * 365;
		}
	}

	tm->tm_mon = lut[day].month;
	tm->tm_mday = lut[day].day;
	if (day >= MAR_THRU_DEC) {
		year++;
		day -= MAR_THRU_DEC;
	} else {
		if (year & 3 || year == 100 || year == 200 || year == 300)
			day += (31 + 28);
		else
			day += (31 + 29);
	}
	tm->tm_year = year + big_cycles * 400 - 300;
	tm->tm_yday = day;
	return 0;
}
