#pragma once
#include "Node.h"
class BVH
{
public:

	enum class AXIS
	{
		UNINIT = 0,
		X = 1,
		Y = 2,
		Z = 3
	};

	BVH(Vector<Shape*>& ShapeData) 
	{
		Vector<Shape*>* ActualData = new Vector<Shape*>(ShapeData.size());
		for (unsigned int i = 0; i < ShapeData.size(); i++)
		{
			if (static_cast<int>(ShapeData[i]->GetType()) != 3)
			{
				ActualData->push_back(ShapeData[i]);
			}
		}
		if (ActualData->size() != 0)
		{
			// Limited range objects were found
			root = BuildNode(*ActualData, 0);
		}
		// Only unlimited objects on shapes array
		else root = nullptr;
		delete ActualData;
	}

	Shape* GetObjects(const Ray& RayReference, float &tVal)
	{
		if (root == nullptr) return nullptr;
		float d_toObject = INFINITY;
		Shape* obj = root->GetObject(RayReference, d_toObject);
		if (obj != nullptr && d_toObject != INFINITY) { tVal = d_toObject; return obj; }
		else return nullptr;
	}

	Node* BuildNode(Vector<Shape*>& NodeShapeData, int depth)
	{
		// The node we are currently building
		Node* ToBuild = nullptr;
		AXIS SeparatingAxis = AXIS::UNINIT;

		Vector3 Low(INFINITY);
		Vector3 Max(-INFINITY);
	
		if (NodeShapeData.size() >= 2)
		{
			for (unsigned int i = 0; i < NodeShapeData.size(); i++)
			{
				AABB ShapeBounds = NodeShapeData[i]->CalculateBounds();
				Vector3 ShapePositionLow = ShapeBounds.GetMin();
				Vector3 ShapePositionMax = ShapeBounds.GetMax();
				if (ShapePositionLow.x < Low.x) Low.x = ShapePositionLow.x;
				if (ShapePositionLow.y < Low.y) Low.y = ShapePositionLow.y;
				if (ShapePositionLow.z < Low.z) Low.z = ShapePositionLow.z;

				if (ShapePositionMax.x > Max.x) Max.x = ShapePositionMax.x;
				if (ShapePositionMax.y > Max.y) Max.y = ShapePositionMax.y;
				if (ShapePositionMax.z > Max.z) Max.z = ShapePositionMax.z;
			}

			Vector3 Diff(Max.x - Low.x, Max.y - Low.y, Max.z - Low.z);

			if (Diff.x >= Diff.y && Diff.x >= Diff.z) SeparatingAxis = AXIS::X;
			else if (Diff.y >= Diff.z) SeparatingAxis = AXIS::Y;
			else SeparatingAxis = AXIS::Z;

			Vector<Shape*>* Left = new Vector<Shape*>(static_cast<int>(ceil(NodeShapeData.size() * 0.5f)));
			Vector<Shape*>* Right = new Vector<Shape*>(static_cast<int>(ceil(NodeShapeData.size() * 0.5f)));

			float AxisAvgPosition = 0;

			switch (SeparatingAxis)
			{
			case AXIS::X:
				AxisAvgPosition = Diff.x * 0.5f + Low.x;
				for (unsigned int i = 0; i < NodeShapeData.size(); i++)
				{
					if ((NodeShapeData[i]->GetCenter().x) < AxisAvgPosition)  Left->push_back(NodeShapeData[i]);
					else Right->push_back(NodeShapeData[i]);
				}
				break;
			case AXIS::Y:
				AxisAvgPosition = Diff.y * 0.5f + Low.y;
				for (unsigned int i = 0; i < NodeShapeData.size(); i++)
				{
					if ((NodeShapeData[i]->GetCenter().y) < AxisAvgPosition)  Left->push_back(NodeShapeData[i]);
					else Right->push_back(NodeShapeData[i]);
				}
				break;
			case AXIS::Z:
				AxisAvgPosition = Diff.z * 0.5f + Low.z;
				for (unsigned int i = 0; i < NodeShapeData.size(); i++)
				{
					if ((NodeShapeData[i]->GetCenter().z) < AxisAvgPosition) Left->push_back(NodeShapeData[i]);
					else Right->push_back(NodeShapeData[i]);
				}
				break;
			default:
				assert(true == false);
				break;
			}
			
			AABB ThisNodeAABB(Vector3(Low.x, Low.y, Low.z), Vector3(Max.x, Max.y, Max.z));
			ToBuild = new BranchNode(ThisNodeAABB);
			ToBuild->SetLeft(BuildNode(*Left, depth + 1));
			ToBuild->SetRight(BuildNode(*Right, depth + 1));
			delete Left;
			delete Right;
			return ToBuild;
		}
		else
		{
			AABB ThisNodeAABB(Vector3(Low.x, Low.y, Low.z), Vector3(Max.x, Max.y, Max.z));
			ToBuild = new LeafNode(ThisNodeAABB, NodeShapeData[0]);
			return ToBuild;
		}
	}
	
	~BVH() { root = nullptr; }
private:
	Node* root = nullptr;
};