
#include "JensTransformer.h"
#include <map>

namespace Clobscode
{

    JensTransformer::JensTransformer(FEMesh &mesh, vector<MeshPoint> &mpts)
    {
        this->points = mesh.getPoints();
        // this->elements = mesh.getElements();
        this->elementsJens = mesh.getElementsJens();
        this->meshPoints = mpts;
    }

    // necesita elementsJens y meshPoints actualizados.
    set<unsigned int> JensTransformer::computeLabeledNodes(double threshold)
    {
        // cout << "computeLabeledNodes\n";
        // cout << "\tPoints: " << (points).size() << endl;
        // cout << "\tElementJens: " << (elementsJens).size() << endl;
        // cout << "\tMeshPoints: " << (meshPoints).size() << endl;

        int count = 0;
        labeledNodes.clear();
        labeledOctants.clear();
        set<unsigned int> ln, lo;
        map<unsigned int, set<unsigned int>> mapPointOctant; // point -> octants
        // set<unsigned int> nodes;
        // for (Element *element : elementsJens)
        for (int i = 0; i < elementsJens.size(); i++)
        {
            Element *element = elementsJens[i];
            double q = element->getElementJENS(points);
            Octant o = *(element->octant);
            int octant_id = o.getIndex();
            if (q < threshold)
            {
                count++;
                for (unsigned int node : element->getPoints())
                {
                    ln.insert(node);
                    mapPointOctant[node].insert(octant_id);
                }
                lo.insert(octant_id);
            }
        }

        labeledNodes = ln;
        labeledOctants = lo;
        pointsToOctants = mapPointOctant;
        cout << "computeLabeledNodes labeled octants: " << lo.size() << "\n";
        return lo;
    };
}