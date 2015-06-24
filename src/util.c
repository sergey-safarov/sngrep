/**************************************************************************
 **
 ** sngrep - SIP Messages flow viewer
 **
 ** Copyright (C) 2015 Ivan Alonso (Kaian)
 ** Copyright (C) 2015 Irontec SL. All rights reserved.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
/**
 * @file util.c
 * @author Ivan Alonso [aka Kaian] <kaian@irontec.com>
 *
 * @brief Source of functions defined in util.h
 *
 */
#include "config.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"


const char *
timeval_to_date(struct timeval time, char *out)
{
    time_t t = (time_t) time.tv_sec;
    struct tm *timestamp = localtime(&t);
    strftime(out, 11, "%Y/%m/%d", timestamp);
    return out;
}


const char *
timeval_to_time(struct timeval time, char *out)
{
    time_t t = (time_t) time.tv_sec;
    struct tm *timestamp = localtime(&t);
    strftime(out, 19, "%H:%M:%S", timestamp);
    sprintf(out + 8, ".%06d", (int) time.tv_usec);
    return out;
}

const char *
timeval_to_duration(struct timeval start, struct timeval end, char *out)
{
    int seconds;
    char duration[20];

    if (!out || !start.tv_sec || !end.tv_sec)
        return NULL;

    // Differnce in secons
    seconds = end.tv_sec - start.tv_sec;
    // Set Human readable format
    sprintf(duration, "%d:%02d", seconds / 60, seconds % 60);
    sprintf(out, "%7s", duration);
    return out;
}

const char *
timeval_to_delta(struct timeval start, struct timeval end, char *out)
{
    long diff;
    int nsec, nusec;
    int sign;

    if (!out || !start.tv_sec || !end.tv_sec)
        return NULL;

    diff = end.tv_sec  * 1000000 + end.tv_usec;
    diff -= start.tv_sec * 1000000 + start.tv_usec;

    nsec = diff / 1000000;
    nusec = abs(diff - (nsec * 1000000));

    sign = (diff >= 0) ? '+' : '-';

    sprintf(out, "%c%d.%06d", sign, abs(nsec), nusec);
    return out;
}
