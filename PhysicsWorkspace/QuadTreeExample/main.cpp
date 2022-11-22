#include <vector>
#include <assert.h>


struct Point2D {
	Point2D(float x, float y) : x(x), y(y) { }
	Point2D() : x(0), y(0) { }
	float x;
	float y;

	void Set(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Point2D operator/(const float& scalar) const {
		return Point2D(x / scalar, y / scalar);
	}
	Point2D operator-(const Point2D& p) const {
		return Point2D(x - p.x, y - p.y);
	}
	Point2D operator+(const Point2D& p) const {
		return Point2D(x + p.x, y + p.y);
	}
};

struct Triangle2D {
	Point2D a, b, c;
};

struct Point3D {
	float x;
	float y;
	float z;
};

struct Triangle3D {
	Point3D a, b, c;
};

class QuadTreeNode {
public:
	QuadTreeNode(Point2D p, Point2D e, unsigned int depth) 
		: position(p), halfExtents(e), nodeDepth(depth) {}
	~QuadTreeNode() {}
	unsigned int nodeDepth;
	Point2D position;
	Point2D halfExtents;
	QuadTreeNode* child[4];
	std::vector<Point2D> points;
	std::vector<Triangle2D*> triangles;

	void PrintNodeInfo() {
		printf("Position: (%.2f, %.2f), extents: (%.2f, %.2f), depth: %d\n", position.x, position.y, halfExtents.x, halfExtents.y, nodeDepth);
	}

	unsigned int getChildIndex(const Point2D& center)
	{
		unsigned int index = 0;
		if (center.x > position.x) index += 1;
		if (center.y > position.y) index += 2;
		return index;
	}

	QuadTreeNode* getQuadTreeNodeWithPoint(const Point2D& point)
	{
		if (child[0] == nullptr)
			return this;

		unsigned int childIndex = getChildIndex(point);
		return child[childIndex]->getQuadTreeNodeWithPoint(point);
	}

	void createChildren()
	{
		assert(child[0] == nullptr);
		assert(child[1] == nullptr);
		assert(child[2] == nullptr);
		assert(child[3] == nullptr);

		Point2D halfExtentsHalved = halfExtents / 2.f;
		child[0] = new QuadTreeNode(position - halfExtentsHalved, halfExtentsHalved, nodeDepth + 1);
		child[1] = new QuadTreeNode(position + Point2D(halfExtentsHalved.x, -halfExtentsHalved.y), halfExtentsHalved, nodeDepth + 1);
		child[2] = new QuadTreeNode(position + Point2D(-halfExtentsHalved.x, halfExtentsHalved.y), halfExtentsHalved, nodeDepth + 1);
		child[3] = new QuadTreeNode(position + halfExtentsHalved, halfExtentsHalved, nodeDepth + 1);
	}

	void addPoint(const Point2D& point, unsigned int maxDepth) {
		if (nodeDepth == maxDepth) {
			points.push_back(point);
			return;
		}

		if (child[0] == nullptr) {
			createChildren();
		}

		unsigned int index = getChildIndex(point);
		child[index]->addPoint(point, maxDepth);
	}

	bool TestTriangleChild(Triangle2D* triangle, unsigned int childIndex) {
		QuadTreeNode* childNode = child[childIndex];
		float p0, p1, p2, r;


		Point2D v0 = triangle->a - childNode->position;
		Point2D v1 = triangle->b - childNode->position;
		Point2D v2 = triangle->c - childNode->position;

		float f0 = v1 - v0;
	}

	void addTriangle(Triangle2D* triangle, unsigned int maxDepth) {
		if (nodeDepth == maxDepth) {
			triangles.push_back(triangle);
			return;
		}

		// See if we need to go deeper for the acceptable max depth of our quadtree
		if (child[0] == nullptr) {
			createChildren();
		}

		// Test the triangle vs all children
		// each child is a "box" / "cube" / "square for 2D"
		for (int i = 0; i < 4; i++) {
			if (TestTriangleChild(triangle, i)) {
				child[i]->addTriangle(triangle, maxDepth);
			}
		}
	}
};

class OctTreeNode {
public:
	Point3D position;
	OctTreeNode* child[8];
	std::vector<Triangle3D*> triangles;
	unsigned int getChildIndex(const Point3D& center)
	{
		unsigned int index = 0;
		if (center.x > position.x) index += 1;
		if (center.y > position.y) index += 2;
		if (center.z > position.z) index += 4;
		return index;
	}
};

QuadTreeNode* parent;

int main(int argc, char** argv) {
	parent = new QuadTreeNode(Point2D(8, 8), Point2D(8, 8), 0);

	QuadTreeNode* node;
	unsigned int childIndex;
	Point2D p;
	p.Set(6, 3);
	parent->addPoint(p, 4);

	p.Set(12, 4);
	parent->addPoint(p, 4);

	p.Set(5, 12);
	parent->addPoint(p, 4);

	p.Set(12, 12);
	parent->addPoint(p, 4);



	p.Set(6, 3);
	node = parent->getQuadTreeNodeWithPoint(p);
	printf("(%.2f, %.2f) -> (%.2f, %.2f)\n", p.x, p.y, node->points[0].x, node->points[0].y);
	node->PrintNodeInfo();

	p.Set(12, 4);
	node = parent->getQuadTreeNodeWithPoint(p);
	printf("(%.2f, %.2f) -> (%.2f, %.2f)\n", p.x, p.y, node->points[0].x, node->points[0].y);
	node->PrintNodeInfo();

	p.Set(5, 12);
	node = parent->getQuadTreeNodeWithPoint(p);
	printf("(%.2f, %.2f) -> (%.2f, %.2f)\n", p.x, p.y, node->points[0].x, node->points[0].y);
	node->PrintNodeInfo();

	p.Set(12, 12);
	node = parent->getQuadTreeNodeWithPoint(p);
	printf("(%.2f, %.2f) -> (%.2f, %.2f)\n", p.x, p.y, node->points[0].x, node->points[0].y);
	node->PrintNodeInfo();


}
