#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  I = -1;
  sqrD = std::numeric_limits<double>::infinity();
  double dist, x_diff, y_diff, z_diff;
  for(int i=0; i<points.rows();i++){
    x_diff = points(i, 0) - query[0];
    y_diff = points(i, 1) - query[1];
    z_diff = points(i, 2) - query[2];
    dist = x_diff*x_diff + y_diff*y_diff + z_diff*z_diff;
    if (dist < sqrD){
			sqrD = dist;
			I = i;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
