// This file contains implementations of the functions in BVTreeQuestion.h.

#include "BVTree.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

double BVTreeNode::distanceToVolumeSq(const Vec3d & x) const
{
  double distSq = 0.0;
  for (int i = 0; i != 3; ++i)
  {
    double dlo = volume_.first[i] - x[i];
    double dhi = x[i] - volume_.second[i];
    double e = std::max(std::max(dlo, dhi), 0.0);
    distSq += e * e;
  }
  return distSq;
}

static BVTreeNode makeBVTree(std::vector<Vec3d>::iterator start,
                             std::vector<Vec3d>::iterator end,
                             const int maxPointsInLeaf)
{
  assert(start != end);
  
  // Create bounding volume over the given point set.
  int numPoints = 0;
  Box volume = {*start, *start};
  for (auto itr = start; itr != end; ++itr)
  {
    const auto & point = *itr;
    numPoints++;
    for (int i = 0; i < 3; ++i)
    {
      volume.first[i] = std::min(volume.first[i], point[i]);
      volume.second[i] = std::max(volume.second[i], point[i]);
    }
  }
  
  if (numPoints < maxPointsInLeaf)
  {
    // Create a leaf node.
    auto points = std::vector<Vec3d>(start, end);
    return BVTreeNode(volume, std::move(points), {});
  }

  // Partition the point set into separate volumes with minimal overlap.
  int maxDim = -1;
  double maxExtent = -1.0;
  for (int i = 0; i < 3; ++i)
  {
    double extent = volume.second[i] - volume.first[i];
    assert(extent >= 0.0);
    if (extent >= maxExtent)
    {
      maxExtent = extent;
      maxDim = i;
    }
  }
  double midpoint = (volume.first[maxDim] + volume.second[maxDim]) / 2.0;
  
  auto separator =
      std::partition(start, end, [=](const Vec3d & point) { return point[maxDim] < midpoint; });
  return BVTreeNode(
      volume, {},
      {makeBVTree(start, separator, maxPointsInLeaf), makeBVTree(separator, end, maxPointsInLeaf)});
}

BVTreeNode makeBVTree(std::vector<Vec3d> points, const int maxPointsInLeaf)
{
  assert(!points.empty());
  return makeBVTree(points.begin(), points.end(), maxPointsInLeaf);
}

double distanceCalcIn3DSpace(const Vec3d first, const Vec3d second)
{
  return std::sqrt(
                   std::pow(((double)second[0] - double(first[0])), 2.0d) 
                                               +
                   std::pow((double(second[1]) - double(first[1])), 2.0d) 
                                               +
                   std::pow((double(second[2]) - double(first[2])), 2.0d) 
                   );
}

Vec3d nearestPoint(const BVTreeNode & root, const Vec3d & queryPoint)
{ 
  // Coordinate to be returned
  static Vec3d nearestCoordinates;  
  
  // Height of tree > 1
  if (root.children().size() == 1)
  {
    // No need to compare volumes. Node has only one child.
    nearestPoint(root.children()[0], queryPoint);
  } else if (root.children().size() > 1)
  {
    // Initializing the  iterative variables equal to the first child
    BVTreeNode iter = root.children()[0];
    
    // Divide and Conquer Strategy
    if (root.children()[0].distanceToVolumeSq(queryPoint) 
                        >
        root.children()[1].distanceToVolumeSq(queryPoint))
    {
      iter = root.children()[1];      
    }
    // Go one level down the BVH tree.
    nearestPoint(iter, queryPoint);
  } else 
  { 
    // Stop Iterating through the tree
    // The current node is the leaf node that should contain the point
    // closest to the queryPoint

    // Initializing the shortest distance to the query point equal to 
    // the first point contained inside the node
    double shortestDistance = distanceCalcIn3DSpace(root.points()[0], 
                                                    queryPoint);
    nearestCoordinates = root.points()[0];

    for(int points_index = 1; points_index < root.points().size(); 
                                             ++points_index)
    {
      if (shortestDistance > distanceCalcIn3DSpace(root.points()
                             [points_index], queryPoint))
      {
        shortestDistance = distanceCalcIn3DSpace(root.points()
                           [points_index], queryPoint);
        nearestCoordinates = root.points()[points_index];
      }
    }
  }
  return nearestCoordinates;
}
