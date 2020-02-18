#pragma once
#include "..\src\AABB.h"
#include "Container.h"
#include "..\src\Shape.h"

class Node 
{
public:
	Node() {};
	Node(AABB Box) { m_box = Box; };

	virtual Node* Left() = 0;
	virtual Node* Right() = 0;
	virtual void SetLeft(Node* new_left) = 0;
	virtual void SetRight(Node* new_right) = 0;

	virtual Shape* GetObject(const Ray& RayReference, float& t) = 0;

protected:

	AABB m_box;
};

class BranchNode : public Node
{
public:
	BranchNode(AABB Box) : Node(Box) {}

	Node* Left() { return m_left_node; }
	void SetLeft(Node* new_left) { m_left_node = new_left; }
	Node* Right() { return m_right_node; }
	void SetRight(Node* new_right) { m_right_node = new_right; }
	Shape* GetObject(const Ray& RayReference, float& t)
	{
		if (m_box.RayIntersect(RayReference))
		{
			float t_l = INFINITY;
			float t_r = INFINITY;
			Shape* l = Left()->GetObject(RayReference, t_l);
			Shape* r = Right()->GetObject(RayReference, t_r);

		
			if (t_l < t_r)
			{
				t = t_l; return l;
			}
			else if (t_r < t_l)
			{
			
				t = t_r; return r;
			}
			else
			{
				return nullptr;
			}


		}
		return nullptr;
	}
private:
	Node* m_left_node = nullptr;
	Node* m_right_node = nullptr;
};

class LeafNode : public Node
{
public:
	LeafNode(AABB Box, Shape* Data) : Node(Box) 
	{
		m_object = Data;
	}
	Shape* GetObject(const Ray& RayReference, float &closest_t)
	{
		float this_object_t = 0;
		if (m_object->RayIntersect(RayReference, this_object_t)) 
		{
			closest_t = this_object_t;
			return m_object;
		}
		else
		{
			return nullptr;
		}

	}

	Node* Left() { return nullptr; }
	Node* Right() { return nullptr; }
	void SetLeft(Node*) {  }
	void SetRight(Node*) {  }

private:
	Shape* m_object = nullptr;
};