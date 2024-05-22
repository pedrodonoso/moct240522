

#ifndef JensTransformer_h
#define JensTransformer_h 1

#include <vector>
#include "../Jens/Hexahedron.h"
#include "../Jens/Prism.h"
#include "../Jens/Pyramid.h"
#include "../Jens/Tetrahedron.h"
#include "../Jens/Element.h"
#include "../Point3D.h"
#include "../FEMesh.h"
#include "../MeshPoint.h"
#include <set>

using std::vector;

namespace Clobscode
{
	class JensTransformer
	{

	public:
		JensTransformer();
		JensTransformer(FEMesh &mesh, vector<MeshPoint> &mpts);
		vector<Element *> transformElements();
		Element *transformElement(vector<unsigned int> element);
		set<unsigned int> computeLabeledNodes(double threshold);
		set<unsigned int> &getLabeledNodes();
		set<unsigned int> &getLabeledOctants();
		void printStatus(string msg);

	protected:
		vector<Point3D> points;
		vector<MeshPoint> meshPoints;
		vector<vector<unsigned int>> elements;
		vector<Element *> elementsJens;
		set<unsigned int> labeledNodes;
		set<unsigned int> labeledOctants;
	};

	inline set<unsigned int> &JensTransformer::getLabeledNodes() { return labeledNodes; }
	inline set<unsigned int> &JensTransformer::getLabeledOctants() { return labeledOctants; }
	inline void JensTransformer::printStatus(string msg = "")
	{
		cout << "JensTransformer Status: " << msg << endl;
		cout << "\tPoints: " << points.size() << endl;
		cout << "\tMeshPoints: " << (meshPoints).size() << endl;
		cout << "\tElementsJens: " << elementsJens.size() << endl;
		cout << "\tLabeledNodes: " << labeledNodes.size() << endl;
		cout << "\tOctants Labeled: " << labeledOctants.size() << endl;
	}
}
#endif