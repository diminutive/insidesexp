#' Title
#'
#' @param pts
#' @param coords
#'
#' @return
#' @export
#'
#' @examples
inside_sexp <- function(pts, coords) {
  .Call(InPoly_C, pts[,1], pts[,2], coords[,1], coords[,2],
      PACKAGE = "insidesexp")
}
