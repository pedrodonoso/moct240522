

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
#include "../Octant.h"
#include <set>
#include <map>

using std::vector;

namespace Clobscode
{
	class JensTransformer
	{

	public:
		JensTransformer(FEMesh &mesh);
		// vector<Element *> transformElements();
		// Element *transformElement(vector<unsigned int> element);
		set<unsigned int> computeLabeledNodes(double threshold);
		set<unsigned int> &getLabeledNodes();
		set<unsigned int> &getLabeledOctants();
		map<unsigned int, set<unsigned int>> &getLabeledPtsToOcts();
		void printStatus(string msg);

		static Element *transformElement(vector<unsigned int> element, Clobscode::Octant* oct)
		{
			vector<int> aux(element.begin(), element.end());
			int n = element.size();
			if (n == 4) // T
			{
				Tetrahedron *tet = new Tetrahedron(aux);
				tet->octant = oct;
				return tet;
			}
			else if (n == 5) // P
			{
				Pyramid *pyr = new Pyramid(aux);
				pyr->octant = oct;
				return pyr;
			}
			else if (n == 6) // R
			{
				Prism *prism = new Prism(aux);
				prism->octant = oct;
				return prism;
			}
			else // H
			{
				Hexahedron *hex = new Hexahedron(aux);
				hex->octant = oct;
				return hex;
			}
		}

	protected:
		vector<Point3D> points;
		// vector<vector<unsigned int>> elements;
		vector<Element *> elementsJens;
		set<unsigned int> labeledNodes;
		set<unsigned int> labeledOctants;
		map<unsigned int, set<unsigned int>> pointsToOctants;
	};

	inline map<unsigned int, set<unsigned int>> &JensTransformer::getLabeledPtsToOcts() { return pointsToOctants; }
	inline set<unsigned int> &JensTransformer::getLabeledNodes() { return labeledNodes; }
	inline set<unsigned int> &JensTransformer::getLabeledOctants() { return labeledOctants; }
	inline void JensTransformer::printStatus(string msg = "")
	{
		cout << "STATUS JENSTRANSFORMER: " << msg << endl;
		cout << "\tPoints: " << points.size() << endl;
		cout << "\tElementsJens: " << elementsJens.size() << endl;
		cout << "\tLabeledNodes: " << labeledNodes.size() << endl;
		cout << "\tOctants Labeled: " << labeledOctants.size() << endl;
	}
}
#endif