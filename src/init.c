
#include <Rinternals.h>
#include <R_ext/Rdynload.h>



/* .Call calls */
extern SEXP InPoly_C(SEXP xx, SEXP yy, SEXP px, SEXP py);
static const R_CallMethodDef CallEntries[] = {
  {"InPoly_C",  (DL_FUNC) &InPoly_C,  4},
  {NULL, NULL, 0}
};

void R_init_insidesexp(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
