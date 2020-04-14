#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // see lecture4 as reference
  double ax = 1/ray.direction(0);
  double ay = 1/ray.direction(1);
  double az = 1/ray.direction(2);
  double txmin, txmax, tymin, tymax, tzmin, tzmax;
  
  if (ax >= 0){
    txmin = ax * (box.min_corner(0) - ray.origin(0));
    txmax = ax * (box.max_corner(0) - ray.origin(0));  
  } else {
    txmax = ax * (box.min_corner(0) - ray.origin(0));
    txmin = ax * (box.max_corner(0) - ray.origin(0));  
  }
  
  if (ay >= 0){
    tymin = ay * (box.min_corner(1) - ray.origin(1));
    tymax = ay * (box.max_corner(1) - ray.origin(1));  
  } else {
    tymax = ay * (box.min_corner(1) - ray.origin(1));
    tymin = ay * (box.max_corner(1) - ray.origin(1));  
  }
  
  if (az >= 0){
    tzmin = az * (box.min_corner(2) - ray.origin(2));
    tzmax = az * (box.max_corner(2) - ray.origin(2));  
  } else {
    tzmax = az * (box.min_corner(2) - ray.origin(2));
    tzmin = az * (box.max_corner(2) - ray.origin(2));  
  }

  double largest_min = fmax(fmax(txmin, tymin), tzmin);
  double smallest_max = fmin(fmin(txmax ,tymax), tzmax);

  if (smallest_max < largest_min){
    return false;
  }

  double min = fmax(min_t, largest_min);
  double max = fmin(max_t, smallest_max);
  if (max < min){
    return false;  
  }
  return true;  
  ////////////////////////////////////////////////////////////////////////////
}
