#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  //define a priority queue
  auto compare = [](std::pair<double, std::shared_ptr<AABBTree>> n1, std::pair<double, std::shared_ptr<AABBTree>> n2) {
    return n1.first > n2.first;  
  };
  std::priority_queue<std::pair<double, std::shared_ptr<AABBTree>>, std::vector<std::pair<double, std::shared_ptr<AABBTree>>>, decltype(compare)> queue(compare);
  
  // see README.md as reference
  sqrd = std::numeric_limits<double>::infinity();
  double d_r = point_box_squared_distance(query, root->box);
  queue.emplace(d_r, root);
  
  while(!queue.empty()){
    double d_s = queue.top().first;
    std::shared_ptr<AABBTree> n = queue.top().second;
    queue.pop();
     
    if (d_s < sqrd){
      if (n->num_leaves <= 2){   
        // subtree is leaf
        double t_sqrd;
        std::shared_ptr<Object> t_desc;
        // pick the smaller one from left and right
        if (n->left->point_squared_distance(query, min_sqrd, max_sqrd, t_sqrd, t_desc) && (t_sqrd < sqrd)){
          sqrd = t_sqrd;
          descendant = n->left;
        }
        if (n->right && n->right->point_squared_distance(query, min_sqrd, max_sqrd, t_sqrd, t_desc) && (t_sqrd < sqrd)){
          sqrd = t_sqrd;
          descendant = n->right;
        }
      } else {
        double d_l = point_box_squared_distance(query, n->left->box);
        queue.emplace(d_l, std::dynamic_pointer_cast<AABBTree>(n->left));
        double d_r = point_box_squared_distance(query, n->right->box);
        queue.emplace(d_r, std::dynamic_pointer_cast<AABBTree>(n->right));
      }
    }  
  }
  return descendant != NULL;
}
