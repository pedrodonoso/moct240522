
#include "JensTransformer.h"
#include <map>

namespace Clobscode
{

    JensTransformer::JensTransformer(FEMesh &mesh)
    {
        this->points = mesh.getPoints();
        this->elementsJens = mesh.getElementsJens();
    }

    // get octants and points with bad quality.
    set<unsigned int> JensTransformer::computeLabeledNodes(double threshold)
    {

        labeledNodes.clear();
        labeledOctants.clear();
        set<unsigned int> ln, lo;
        map<unsigned int, set<unsigned int>> mapPointOctant; // point -> octants

        for (int i = 0; i < elementsJens.size(); i++)
        {
            Element *element = elementsJens[i];
            double q = element->getElementJENS(points); // quality
            Octant o = *(element->octant); // octant of the element
            int octant_id = o.getIndex();
            if (q < threshold)
            {
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