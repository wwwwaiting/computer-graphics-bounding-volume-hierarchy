#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double a, b, c, d, e, f, g, h, i, j, k, l;  
  a = A[0] - B[0];
  b = A[1] - B[1];
  c = A[2] - B[2];
  d = A[0] - C[0]; 
  e = A[1] - C[1];
  f = A[2] - C[2];

  g = ray.direction[0];
  h = ray.direction[1];
  i = ray.direction[2];

  j = A[0] - ray.origin[0]; 
  k = A[1] - ray.origin[1];
  l = A[2] - ray.origin[2]; 
  
  double M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);

  if (M == 0){
    return false;
  }

  double beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g)) / M; 
  double gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c)) / M;
  double temp_t = (-1) * ((f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c)) / M);
  
  // constriants see reference on textbook p79.
  if (temp_t < min_t || temp_t > max_t || gamma < 0 || gamma > 1 || beta < 0 || beta > (1-gamma)){
    return false;  
  } else {
    t = temp_t;  
    return true;
  }
  ////////////////////////////////////////////////////////////////////////////
}

