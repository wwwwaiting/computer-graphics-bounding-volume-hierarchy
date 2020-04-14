#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if (!ray_intersect_box(ray, this->box, min_t, max_t)){
    return false;
  }
  std::shared_ptr<Object> l;
  std::shared_ptr<Object> r;
  double l_t, r_t;
  // check if left and right child are hit
  bool l_hit = (this->left != NULL) && (this->left->ray_intersect(ray, min_t, max_t, l_t, l));
  bool r_hit = (this->right != NULL) && (this->right->ray_intersect(ray, min_t, max_t, r_t, r));
  
  // update l and r is the corresponding child is hit
  if (l_hit && !l){
    l = this->left;
  }
  if (r_hit && !r){
    r = this->right;
  }

  // hit both
  if(l_hit && r_hit){
    if (l_t < r_t){
      t = l_t;
      descendant = l;        
    } else {
      t = r_t;
      descendant = r;        
    }
  }else if(l_hit){
    // only hit left
    t = l_t;
    descendant = l;
  } else if(r_hit){
    // only hit right
    t = r_t;
    descendant = r;
  } else{
    // not hit
    return false;
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

