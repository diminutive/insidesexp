

/*
 This code is described in "Computational Geometry in C" (Second Edition),
 Chapter 7.  It is not written to be comprehensible without the
 explanation in that book.

 For each query point q, InPoly returns one of four char's:
 i : q is strictly interior to P
 o : q is strictly exterior to P
 v : q is a vertex of P
 e : q lies on the relative interior of an edge of P
 These represent mutually exclusive categories.
 For an explanation of the code, see Chapter 7 of
 "Computational Geometry in C (Second Edition)."

 Written by Joseph O'Rourke, contributions by Min Xu, June 1997.
 Questions to orourke@cs.smith.edu.
 --------------------------------------------------------------------
 This code is Copyright 1998 by Joseph O'Rourke.  It may be freely
 redistributed in its entirety provided that this copyright notice is
 not removed.
 --------------------------------------------------------------------
 */

/*
 InPoly returns a char in {i,o,v,e}.  See above for definitions.
 */


# include <R.h>
# include <Rinternals.h>

int InPoly(double xx, double yy, SEXP px, SEXP py)
{


  // modified from InPoly O'Rourke Ch 7.

  // was POLYGON *Poly becomes doubles px,py
  //  int n = Poly->lines;
  //  PLOT_POINT *P=Poly->p; becomes double xx, yy
  int n = LENGTH(px);
  int	 i, i1;      /* point index; i1 = i-1 mod n */
double x;          /* x intersection of e with ray */
// xx,yy is the point (was PLOT_POINT q)
//double xx=q.x, yy=q.y;
int	 Rcross = 0; /* number of right edge/ray crossings */
int    Lcross = 0; /* number of left edge/ray crossings */

/* For each edge e=(i-1,i), see if crosses ray. */
for( i = 0; i < n; i++ ) {
  /* First see if q=(0,0) is a vertex. */
  if (( REAL(px)[i] - xx )==0 &&( REAL(py)[i] - yy )==0 ) return 3; //return 'v';
  i1 = ( i + n - 1 ) % n;
  /* printf("e=(%d,%d)\t", i1, i); */

  /* if e "straddles" the x-axis... */
  /* The commented-out statement is logically equivalent to the one
   following. */
  /* if( ( ( P[i].y > 0 ) && ( P[i1].y <= 0 ) ) ||
   ( ( P[i1].y > 0 ) && ( P[i] .y <= 0 ) ) ) { }*/

  if( (( REAL(py)[i] - yy ) > 0 ) != (( REAL(py)[i1] - yy ) > 0 ) ) {

    /* e straddles ray, so compute intersection with ray. */
    x = (( REAL(px)[i] - xx) *( REAL(py)[i1] - yy ) -( REAL(px)[i1]- xx ) *( REAL(py)[i] - yy )) /
      (REAL(py)[i1] - REAL(py)[i] );
    /* printf("straddles: x = %g\t", x); */

    /* crosses ray if strictly positive intersection. */
    if (x > 0) Rcross++;
  }
  /* printf("Right cross=%d\t", Rcross); */

  /* if e straddles the x-axis when reversed... */
  /* if( ( ( P[i] .y < 0 ) && ( P[i1].y >= 0 ) ) ||
   ( ( P[i1].y < 0 ) && ( P[i] .y >= 0 ) ) )  { }*/

  if ( (( REAL(py)[i] - yy ) < 0 ) != (( REAL(py)[i1] - yy ) < 0 ) ) {

    /* e straddles ray, so compute intersection with ray. */
    x = (( REAL(px)[i] - xx) *( REAL(py)[i1] - yy ) -( REAL(px)[i1]- xx ) *( REAL(py)[i] - yy )) /
      (REAL(py)[i1] - REAL(py)[i]);
    /* printf("straddles: x = %g\t", x); */

    /* crosses ray if strictly positive intersection. */
    if (x < 0) Lcross++;
  }
  /* printf("Left cross=%d\n", Lcross); */
}

/* q on the edge if left and right cross are not the same parity. */
if( ( Rcross % 2 ) != (Lcross % 2 ) )
  return 2;
  //return 'e';

/* q inside iff an odd number of crossings. */
if( (Rcross % 2) == 1 )
  return 1;
  //return 'i';
else
  return 0;
  //return 'o';
}


SEXP InPoly_C(SEXP xx, SEXP yy, SEXP px, SEXP py) {

  int nn = LENGTH(xx);

  SEXP out = PROTECT(Rf_allocVector(INTSXP, nn));

  //PROTECT(out = NEW_INTEGER(nn));
double xi, yi;
  for (int i = 0; i < nn; i++) {
    xi = REAL(xx)[i];
    yi = REAL(yy)[i];
    INTEGER(out)[i] = InPoly(xi, yi, px, py);
  // switch (InPoly(xx[i], yy[i], px, py)) {
  // case 'i': out[i] = 1; break;
  // case 'o': out[i] = 0; break;
  // case 'v': out[i] = 3; break;
  // case 'e': out[i] = 2; break;
  // default:  out[i] =-1; break;
  // }
  //
  }
  UNPROTECT(1);
  return out;
}
