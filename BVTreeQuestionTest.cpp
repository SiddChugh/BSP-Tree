#include "BVTreeQuestion.h"

#include <cassert>
#include <iostream>
#include <vector>


//-------------------------------Test Data Start-------------------------------
// Arbitrary Coordinates
// Should not matter
const std::vector<Vec3d> coordinates = {{-1, 1, 1}, 
																				{-2, 3, 2}, 
																				{-2, 3, 2}, 
																				{-2, 3, 1}, 
																				{-1, 3, 1}, 
																				{-1, 3, 11}};												
// Arbitrary Coordinates
// Should not matter
const std::vector<Vec3d> onlyOneCoordinate = {{1, 1, 1}};
	
// Query Point Exists in the tree
const Vec3d queryPointPresentInTree = {-2, 3, 1};

// Query Point Does not Exists in the tree
const Vec3d queryPointNotPresentInTree = {0, 0, 0};

// The root node would contain all the coordinates
const int createTreeHeightEqualThanOne = coordinates.size() + 1;
// 	Maximum amount of coordinates allowed in a node is less than the number 
// 	of coordinates. Hence, a Binary space partitioning Tree would be 
//	generated.
const int createTreeHeightGreaterThanOne = coordinates.size() / 2;
//------------------------------Test Data End----------------------------------																		
//-------------------------Test Cases Start------------------------------------
void TestClosestPointWhenTreeHeightEqualToOneAndQueryPointExistsInTree()
{
	BVTreeNode test_BVTree = makeBVTree(coordinates, 
																			createTreeHeightEqualThanOne);
	Vec3d closestPointBasedOnBVHTreeTraversal = nearestPoint(test_BVTree, 
																			 			  queryPointPresentInTree);

	Vec3d closestPointBasedOnCoordinateTraversal = coordinates[0];
	double shortestDistanceBasedOnCoordinateTraversal = 
	distanceCalcIn3DSpace(coordinates[0], queryPointPresentInTree);

	// Coordinate at Index 0 is used for assumption purposes
	for (int i = 1; i <coordinates.size(); ++i)
	{
		if (shortestDistanceBasedOnCoordinateTraversal > 
				distanceCalcIn3DSpace(coordinates[i], queryPointPresentInTree))
		{
			shortestDistanceBasedOnCoordinateTraversal = 
			distanceCalcIn3DSpace(coordinates[i], queryPointPresentInTree);
			closestPointBasedOnCoordinateTraversal = coordinates[i];
		}
	}

	assert(closestPointBasedOnCoordinateTraversal.size()
												==
				 closestPointBasedOnBVHTreeTraversal.size());
	
	for (int dim = 0; dim < closestPointBasedOnBVHTreeTraversal.size(); ++dim)
	{
		assert(closestPointBasedOnBVHTreeTraversal[dim]
													==
					 closestPointBasedOnCoordinateTraversal[dim]);
	}
}

void TestClosestPointWhenTreeHeightEqualToOneAndQueryPointDoesNotExistsInTree()
{
	BVTreeNode test_BVTree = makeBVTree(coordinates, 
																			createTreeHeightEqualThanOne);
	Vec3d closestPointBasedOnBVHTreeTraversal = nearestPoint(test_BVTree, 
																			 			  queryPointNotPresentInTree);

	Vec3d closestPointBasedOnCoordinateTraversal = coordinates[0];
	double shortestDistanceBasedOnCoordinateTraversal = 
	distanceCalcIn3DSpace(coordinates[0], queryPointNotPresentInTree);

	// Coordinate at Index 0 is used for assumption purposes
	for (int i = 1; i <coordinates.size(); ++i)
	{
		if (shortestDistanceBasedOnCoordinateTraversal > 
				distanceCalcIn3DSpace(coordinates[i], queryPointNotPresentInTree))
		{
			shortestDistanceBasedOnCoordinateTraversal = 
			distanceCalcIn3DSpace(coordinates[i], queryPointNotPresentInTree);
			closestPointBasedOnCoordinateTraversal = coordinates[i];
		}
	}

	assert(closestPointBasedOnCoordinateTraversal.size()
												==
				 closestPointBasedOnBVHTreeTraversal.size());
	
	for (int dim = 0; dim < closestPointBasedOnBVHTreeTraversal.size(); ++dim)
	{
		assert(closestPointBasedOnBVHTreeTraversal[dim]
													==
					 closestPointBasedOnCoordinateTraversal[dim]);
	}
}

void TestClosestPointWhenTreeHeightGreaterThanOneAndQueryPointExistsInTree()
{
	BVTreeNode test_BVTree = makeBVTree(coordinates, 
																			createTreeHeightGreaterThanOne);
	Vec3d closestPointBasedOnBVHTreeTraversal = nearestPoint(test_BVTree, 
																			 			  queryPointPresentInTree);

	Vec3d closestPointBasedOnCoordinateTraversal = coordinates[0];
	double shortestDistanceBasedOnCoordinateTraversal = 
	distanceCalcIn3DSpace(coordinates[0], queryPointPresentInTree);

	// Coordinate at Index 0 is used for assumption purposes
	for (int i = 1; i <coordinates.size(); ++i)
	{
		if (shortestDistanceBasedOnCoordinateTraversal > 
				distanceCalcIn3DSpace(coordinates[i], queryPointPresentInTree))
		{
			shortestDistanceBasedOnCoordinateTraversal = 
			distanceCalcIn3DSpace(coordinates[i], queryPointPresentInTree);
			closestPointBasedOnCoordinateTraversal = coordinates[i];
		}
	}

	assert(closestPointBasedOnCoordinateTraversal.size()
												==
				 closestPointBasedOnBVHTreeTraversal.size());
	
	for (int dim = 0; dim < closestPointBasedOnBVHTreeTraversal.size(); ++dim)
	{
		assert(closestPointBasedOnBVHTreeTraversal[dim]
													==
					 closestPointBasedOnCoordinateTraversal[dim]);
	}
}

void TestClosestPointWhenTreeHeightGreaterThanOneAndQueryPointDoesNotExistsInTree()
{
	BVTreeNode test_BVTree = makeBVTree(coordinates, 
																			createTreeHeightGreaterThanOne);
	Vec3d closestPointBasedOnBVHTreeTraversal = nearestPoint(test_BVTree, 
																			 			  queryPointNotPresentInTree);

	Vec3d closestPointBasedOnCoordinateTraversal = coordinates[0];
	double shortestDistanceBasedOnCoordinateTraversal = 
	distanceCalcIn3DSpace(coordinates[0], queryPointNotPresentInTree);

	// Coordinate at Index 0 is used for assumption purposes
	for (int i = 1; i <coordinates.size(); ++i)
	{
		if (shortestDistanceBasedOnCoordinateTraversal > 
				distanceCalcIn3DSpace(coordinates[i], queryPointNotPresentInTree))
		{
			shortestDistanceBasedOnCoordinateTraversal = 
			distanceCalcIn3DSpace(coordinates[i], queryPointNotPresentInTree);
			closestPointBasedOnCoordinateTraversal = coordinates[i];
		}
	}

	assert(closestPointBasedOnCoordinateTraversal.size()
												==
				 closestPointBasedOnBVHTreeTraversal.size());
	
	for (int dim = 0; dim < closestPointBasedOnBVHTreeTraversal.size(); ++dim)
	{
		assert(closestPointBasedOnBVHTreeTraversal[dim]
													==
					 closestPointBasedOnCoordinateTraversal[dim]);
	}
}

void TestClosestPointWhenTreeHasOnePoint()
{
	BVTreeNode test_BVTree = makeBVTree(onlyOneCoordinate, 
																			createTreeHeightEqualThanOne);
	Vec3d closestPointBasedOnBVHTreeTraversal = nearestPoint(test_BVTree, 
																			 			  queryPointNotPresentInTree);
	assert(closestPointBasedOnBVHTreeTraversal == onlyOneCoordinate[0]);
}
//-------------------------Test Cases End--------------------------------------

int main()
{
	TestClosestPointWhenTreeHeightEqualToOneAndQueryPointExistsInTree();
	TestClosestPointWhenTreeHeightEqualToOneAndQueryPointDoesNotExistsInTree();
	TestClosestPointWhenTreeHeightGreaterThanOneAndQueryPointExistsInTree();
	TestClosestPointWhenTreeHeightGreaterThanOneAndQueryPointDoesNotExistsInTree();
	TestClosestPointWhenTreeHasOnePoint();
	return 0;
}