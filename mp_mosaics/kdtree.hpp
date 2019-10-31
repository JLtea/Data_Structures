/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) {
      return true;
    } else if (first[curDim] == second[curDim]) {
      if (first < second) {
        return true;
      }
    }

    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int potDist = 0;
    int currDist = 0;
    for (int i = 0; i < Dim; i++) {
      potDist += pow((target[i] - potential[i]),2);
      currDist += pow((target[i] - currentBest[i]),2);
    }
    if (potDist < currDist) {
      return true;
    } else if (potDist == currDist) {
      if (potential < currentBest) {
        return true;
      }
    }
     return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> copy;
    for (int i = 0; i < (int)newPoints.size(); i++) {
      copy.push_back(newPoints[i]);
    }
    //copy = newPoints;
    root = makeTree(copy,0, newPoints.size()-1, 0);
    
}
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::makeTree(vector<Point<Dim>> &toSort, int from, int to, int currDim) {
  int range = to-from;
  int medIdx = range/2;
    if (range == 0) {
    KDTreeNode* newNode = new KDTreeNode(toSort[from]);
    return newNode;
  }
  if (range == 1) {
    KDTreeNode* newNode = new KDTreeNode(quickselect(toSort, medIdx + 1, from, to, currDim));
    KDTreeNode* rightNode = new KDTreeNode(toSort[to]);
    newNode->right = rightNode;
    return newNode;
  }
  if (range < 0) {
    return NULL;
  }
  KDTreeNode* newNode = new KDTreeNode(quickselect(toSort, medIdx + 1, from, to, currDim));
  
  newNode->left = makeTree(toSort, from, from + medIdx -1, (currDim+1)%Dim);
  newNode->right = makeTree(toSort, from + medIdx +1, to, (currDim+1)%Dim);
  return newNode;

}
// template <int Dim>
// void KDTree<Dim>::makeTree(KDTreeNode* subRoot, vector<Point<Dim>> &toSort, int from, int to, int currDim) {
//   if (to-from <= 0) {
//     return;
//   }
//   int medIdx = (to-from)/2;
//   subRoot->point = quickselect(toSort, medIdx + 1, from, to, currDim);
//   if (to-from > 0){
//   subRoot->left = new KDTreeNode;
//   makeTree(subRoot->left, toSort, from, medIdx -1, (currDim+1)%Dim);
//   subRoot->right = new KDTreeNode;
//   makeTree(subRoot->right,toSort, medIdx +1, to, (currDim+1)%Dim);
//   }

// }

template <int Dim>
Point<Dim> KDTree<Dim>::quickselect(vector<Point<Dim>> &toSort, int k, int from, int to, int currDim) {
  //std::cout<<"from = "<<from<<", to = "<<to<<", medIdx = " <<medIdx<<std::endl;
  if (k > 0 && k <= to - from +1) {
    int index = partition(toSort, from, to, currDim);
    //std::cout<<"quickselect"<<toSort[index][currDim]<<std::endl;
    if (index - from == k - 1) {
      // std::cout<<"quickselect "<<toSort[index][currDim]<<std::endl;
      // std::cout<<"index : "<<index<< ", k: " <<k<<std::endl;
      // std::cout<<"from : "<<from<<std::endl;
      return toSort[index];
    }
    if (index - from > k - 1) {
      //std::cout<<"from = "<<from<<", to = "<<to<< ", index = "<<index<<", medIdx = " <<medIdx<<std::endl;
      return quickselect(toSort, k, from, index - 1, currDim);
    }
      //std::cout<<"from = "<<from<<", to = "<<to<< ", index = "<<index<<", medIdx = " <<medIdx<<std::endl;
  return quickselect(toSort, k - index + from - 1, index + 1, to, currDim);
  }
  return Point<Dim>();
}
template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> &toSort, int from, int to, int currDim) {
  int track = from;
  //std::cout<<"from = "<<from<<", to = "<<to<<std::endl;
  for (int curr = from; curr <= to-1; curr++) {
    if (toSort[curr][currDim] < toSort[to][currDim] || (toSort[curr][currDim] == toSort[to][currDim] && toSort[curr]<toSort[to])) {
      swap(toSort[track],toSort[curr]);
      track++;
    }
    //std::cout<<"curr = "<<curr<<", track "<<track<<std::endl;
    // if (toSort[curr] < toSort[to]) {
    //   swap(toSort[track],toSort[curr]);
    //   track++;
    // }
  }
  swap(toSort[track], toSort[to]);
  //std::cout<<"partition " <<toSort[track][currDim]<<std::endl;
  return track;
}



template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}
