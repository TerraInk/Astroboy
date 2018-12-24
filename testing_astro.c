/*
 * testing_astro.c
 * 
 * Copyright 2018 Unknown <anton@mx1>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>

#include "swephexp.h" /* this includes  "sweodef.h" */

int main()

{

  char *sp, sdate[AS_MAXCH], snam[40], serr[AS_MAXCH]; 
  int jday = 1, jmon = 1, jyear = 2000;
  double jut = 0.0;
  double tjd_ut, te, x2[6];
  long iflag, iflgret;
  int p;

  swe_set_ephe_path(NULL);
  iflag = SEFLG_SPEED;

  while (TRUE) {

    printf("\nDate (d.m.y) ?");
    gets(sdate);
          /* stop if a period . is entered */
    if (*sdate == '.')
      return OK;
    if (sscanf (sdate, "%d%*c%d%*c%d", &jday,&jmon,&jyear) < 1) exit(1);
             /*
              * we have day, month and year and convert to Julian day number
              */
    tjd_ut = swe_julday(jyear,jmon,jday,jut,SE_GREG_CAL);       
             /*
              * compute Ephemeris time from Universal time by adding delta_t
              * not required for Swisseph versions smaller than 1.60
              */
       /* te = tjd_ut + swe_deltat(tjd_ut); */
    printf("date: %02d.%02d.%d at 0:00 Universal time\n", jday, jmon, jyear);
    printf("planet     \tlongitude\tlatitude\tdistance\tspeed long.\n");
             /*
              * a loop over all planets
              */
    for (p = SE_SUN; p <= SE_CHIRON; p++) {
		if (p == SE_EARTH) continue;
			/*
			* do the coordinate calculation for this planet p
			*/
				iflgret = swe_calc_ut(tjd_ut, p, iflag, x2, serr);
				/* Swisseph versions older than 1.60 require the following
				 * statement instead */
				/* iflgret = swe_calc(te, p, iflag, x2, serr); */
               /*
                * if there is a problem, a negative value is returned and an
                * error message is in serr.
                */
				if (iflgret < 0)
				printf("error: %s\n", serr);
				/*
				* get the name of the planet p
				*/
				swe_get_planet_name(p, snam);
				/*
				* print the coordinates
				*/
		printf("%10s\t%11.7f\t%10.7f\t%10.7f\t%10.7f\n",
				snam, x2[0], x2[1], x2[2], x2[3]);
		}
	}
  return OK;
}
