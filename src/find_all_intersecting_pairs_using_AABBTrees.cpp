#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // use assignment README.md as reference for this function
  std::list<std::pair<std::shared_ptr<AABBTree>, std::shared_ptr<AABBTree>>> queue;
  if (box_box_intersect(rootA->box, rootB->box)){
    queue.emplace_back(rootA, rootB);
  }
  std::shared_ptr<AABBTree> node_A, node_B;
  while (!queue.empty()){
    node_A = queue.front().first;
    node_B = queue.front().second;
    queue.pop_front();

    // node A and node B are leaves
    if (node_A->num_leaves <= 2 && node_B->num_leaves <= 2){
      // did not check left for both node_A and node_B as when we define the aabbtree, if only one object it goes to the left
      if (box_box_intersect(node_A->left->box, node_B->left->box)) {
        leaf_pairs.emplace_back(node_A->left, node_B->left);
      }
      if (node_B->right && box_box_intersect(node_A->left->box, node_B->right->box)) {
        leaf_pairs.emplace_back(node_A->left, node_B->right);
      }
      if (node_A->right && box_box_intersect(node_A->right->box, node_B->left->box)) {
        leaf_pairs.emplace_back(node_A->right, node_B->left);
      }
      if (node_A->right && node_B->right && box_box_intersect(node_A->right->box, node_B->right->box)) {
        leaf_pairs.emplace_back(node_A->right, node_B->right);
      }
    } else if (node_A->num_leaves <= 2) {
      // node_A is a leaf
      if (box_box_intersect(node_A->box, node_B->left->box)) {
        queue.emplace_back(node_A, std::dynamic_pointer_cast<AABBTree>(node_B->left));
      }
      if (box_box_intersect(node_A->box, node_B->right->box)) {
        queue.emplace_back(node_A, std::dynamic_pointer_cast<AABBTree>(node_B->right));
      }
    } else if (node_B->num_leaves <= 2) {
      // node_B is a leaf
      if (box_box_intersect(node_A->left->box, node_B->box)) {
        queue.emplace_back(std::dynamic_pointer_cast<AABBTree>(node_A->left), node_B);
      }
      if (box_box_intersect(node_A->right->box, node_B->box)) {
        queue.emplace_back(std::dynamic_pointer_cast<AABBTree>(node_A->right), node_B);
      }
    } else {
      // node_A and node_B are not leaf
      std::shared_ptr<AABBTree> a_left, b_left, a_right, b_right;
      a_left = std::dynamic_pointer_cast<AABBTree>(node_A->left);
      b_left = std::dynamic_pointer_cast<AABBTree>(node_B->left);
      a_right = std::dynamic_pointer_cast<AABBTree>(node_A->right);
      b_right = std::dynamic_pointer_cast<AABBTree>(node_B->right);
      if (box_box_intersect(node_A->left->box, node_B->left->box)) {
        queue.emplace_back(a_left, b_left);
      }
      if (box_box_intersect(node_A->left->box, node_B->right->box)) {
        queue.emplace_back(a_left, b_right);
      }
      if (box_box_intersect(node_A->right->box, node_B->left->box)) {
        queue.emplace_back(a_right, b_left);
      }
      if (box_box_intersect(node_A->right->box, node_B->right->box)) {
        queue.emplace_back(a_right, b_right);
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
