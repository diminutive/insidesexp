#' Inside with O'Rourke's InPoly
#'
#' Call the O'Rourke InPoly function with the R C API, as in the sp package.
#'
#'    For each query point 'pts', returns one of the following relative to P 'coords':
#'    0 : is strictly interior to P
#'    1 : is strictly exterior to P
#'    3 : is a vertex of P
#'    2 : lies on the relative interior of an edge of P
#'
#' @param pts matrix of points 2 columns x,y
#' @param coords matrix of polygon ring 2 columns x,y
#'
#' @return integer vector of point in polygon status, see Details
#' @export
#'
#' @examples
#' inside_sexp(matrix(runif(10), ncol = 2), cbind(c(0, .5, .5, 0, 0), c(0, 0, .5, 0, 0)))
inside_sexp <- function(pts, coords) {
  .Call(InPoly_C, pts[,1], pts[,2], coords[,1], coords[,2],
      PACKAGE = "insidesexp")
}
