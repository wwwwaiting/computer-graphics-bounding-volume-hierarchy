#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int n = objects.size();
  if (n == 0){
    // empty tree
    this->left = NULL;
    this->right = NULL;
  }else if (n == 1){
    // only one object, put the object on the left 
    this->left = objects[0];
    this->right = NULL;
    insert_box_into_box(this->left->box, this->box);
  }else if (n == 2) {
    this->left = objects[0];
    this->right = objects[1];
    insert_box_into_box(this->left->box, this->box);
    insert_box_into_box(this->right->box, this->box);
  }else{
    for (const auto &object: objects){
      insert_box_into_box(object->box, this->box);     
    }

    // find the axis with the longest distance
    int axis; 
    double longest = -std::numeric_limits<double>::infinity();
    for (int i = 0; i < 3; i++){
      double length = this->box.max_corner(i) - this->box.min_corner(i);
      if (length > longest){
        longest = length;    
        axis = i;    
      }    
    }
    // find the mid_point
    double mid_point = (this->box.max_corner(axis) + this->box.min_corner(axis)) / 2;

    // separating object based on the comparision with mid_point: smaller or equal -> left, greater -> right
    std::vector<std::shared_ptr<Object>> l;
    std::vector<std::shared_ptr<Object>> r;
    for (const auto &object: objects){
      if (object->box.center()[axis] <= mid_point){
        l.emplace_back(object);
      }else{
        r.emplace_back(object);
      }
    }

    // try to balance the tree a little: 
    // no left but multiple right -> move one to the left
    // no right but multiple left -> move one to the right
    if (l.size() == 0 && r.size() > 1){
      l.emplace_back(r.back());
      r.pop_back();
    } else if (r.size() == 0 && l.size() > 1){
      r.emplace_back(l.back());
      l.pop_back();
    } 
     
    this->left = std::make_shared<AABBTree>(l, a_depth+1);     
    this->right = std::make_shared<AABBTree>(r, a_depth+1);     
  }
  ////////////////////////////////////////////////////////////////////////////
}
