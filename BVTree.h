/**
  * This file implements a Bounding Volume Tree.
  */

#include <array>
#include <limits>
#include <vector>
#include <iostream>


/// A point in 3D space, given by its Cartesian coordinates.
using Vec3d = std::array<double, 3>;

/// NOTE: The specific type of bounding volume is not important for implementing nearestPoint().
///       Use BVTreeNode::distanceToVolumeSq() to get the squared-distance from a point to
///       the node's bounding volume (regardless of what shape is being used).
using Box = std::pair<Vec3d, Vec3d>;


/// A Bounding Volume Tree (BVTree)
///
/// An N-ary tree made up of BVTreeNodes.
/// Every node has a 'bounding volume' describing its spatial extent.
/// An interior node's bounding volume covers the bounding volumes of all its children.
/// Leaf nodes have a collection of one or more points inside the bounding volume.
///
/// An interior node may have any number of children, but usually between 2 and 4.
class BVTreeNode
{
public:
  BVTreeNode(const Box & volume, std::vector<Vec3d> && points, std::vector<BVTreeNode> && children)
      : volume_(volume)
      , points_(std::move(points))
      , children_(std::move(children))
  {
  }

  /// Return the square of the Euclidean distance from `x` to the bounding volume of this node.
  /// Points inside the bounding volume have distance `0.0`.
  ///
  /// The KEY invariant is that `distanceToVolumeSq(x)` is less than or equal to
  /// the squared distance from `x` to any point in the entire tree rooted at this node.
  double distanceToVolumeSq(const Vec3d & x) const;

  /// If this node is a leaf, return the points it contains.
  /// Else, return empty vector.
  const std::vector<Vec3d> & points() const { return points_; }

  /// If this node is a leaf, return empty vector.
  /// Else, return the children of this node.
  const std::vector<BVTreeNode> & children() const { return children_; }

  /// Return the bounding volume of this node.
  /// NOTE: This function is provided for API completeness and testing/debugging purposes.
  ///       It is not required for implementing nearestPoint().
  const Box & volume() const { return volume_; }
  
private:
  Box volume_; ///< This node's bounding volume
  std::vector<Vec3d> points_;
  std::vector<BVTreeNode> children_;
};

/// Create a BVTree containing the given set of points.
/// Partitioning/balancing is done on a "best-effort" basis.
/// There are no guarantees of a perfectly-balanced result.
///
/// This function is provided primarily for testing purposes, and for demonstrating how a BVTree
/// is structured. You do not need to call this function in your implementation of nearestPoint().
BVTreeNode makeBVTree(std::vector<Vec3d> points, int maxPointsInLeaf = 10);

/**
 * This function returns the distance between two points in 3D space
 */
double distanceCalcIn3DSpace(const Vec3d first, const Vec3d second);

/// Find the closest point to `queryPoint` in the tree.
Vec3d nearestPoint(const BVTreeNode & root, const Vec3d & queryPoint);

