#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  for (int i = 0; i < 3; i++){
    double minA = A.min_corner(i);
    double maxA = A.max_corner(i);
    double minB = B.min_corner(i);
    double maxB = B.max_corner(i);
    
    bool hitA = minB <= minA && minA <= maxB;
    bool hitB = minA <= minB && minB <= maxA;
     
    if (!(hitA || hitB)){ 
      return false;     
    }  
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

