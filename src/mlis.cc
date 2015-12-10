/*
 * mlis.cc
 *
 *  Created on: Mar 15, 2011
 *      Author: vo
 */

int mlis_get_bound (struct stuff **stp, int argc, char *argv[],Point& xmin, Point& xmax)
{
	register struct specklist *sl;
	register struct speck *sp;
	int minmaxk = MAXVAL+1, maxmaxk = 0;
	int nspecks = 0;

	xmin.x[0] = xmin.x[1] = xmin.x[2] = 1e38;
	xmax.x[0] = xmax.x[1] = xmax.x[2] = -1e38;
	mean.x[0] = mean.x[1] = mean.x[2] = 0;
	for(sl = st->sl; sl != NULL; sl = sl->next) {
	    int i, maxk;
	    if((sp = sl->specks) == NULL)
		continue;
	    for(maxk=0; maxk<MAXVAL && SMALLSPECKSIZE(maxk)<sl->bytesperspeck; maxk++)
		;
	    if(minmaxk > maxk) minmaxk = maxk;
	    if(maxmaxk < maxk) maxmaxk = maxk;
	    for(i = sl->nspecks; --i >= 0; sp = NextSpeck( sp, sl, 1 )) {
		Point tp, *p = &sp->p;

		if(xmin.x[0] > p->x[0]) xmin.x[0] = p->x[0];
		if(xmax.x[0] < p->x[0]) xmax.x[0] = p->x[0];
		mean.x[0] += p->x[0];
		if(xmin.x[1] > p->x[1]) xmin.x[1] = p->x[1];
		if(xmax.x[1] < p->x[1]) xmax.x[1] = p->x[1];
		mean.x[1] += p->x[1];
		if(xmin.x[2] > p->x[2]) xmin.x[2] = p->x[2];
		if(xmax.x[2] < p->x[2]) xmax.x[2] = p->x[2];
		mean.x[2] += p->x[2];
	    }
	    nspecks += sl->nspecks;
	}

	if(nspecks == 0)
		return -1;
	else
		return 1;
}
