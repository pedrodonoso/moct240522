
#include "JensTransformer.h"

namespace Clobscode
{

    JensTransformer::JensTransformer() {}
    JensTransformer::JensTransformer(FEMesh &mesh, vector<MeshPoint> &mpts)
    {
        this->points = mesh.getPoints();
        this->elements = mesh.getElements();
        this->meshPoints = mpts;
    }

    // vector<Element *> JensTransformer::transformElements()
    // {
    //     vector<Element *> els;
    //     els.reserve(elements.size());
    //     printf("TRANSFORM ELEMENTS\n");
    //     for (auto element : elements)
    //     {
    //         vector<int> aux(element.begin(), element.end());
    //         int n = element.size();
    //         if (n == 4) // T
    //         {
    //             els.push_back(new Tetrahedron(aux));
    //         }
    //         else if (n == 5) // P
    //         {
    //             els.push_back(new Pyramid(aux));
    //         }
    //         else if (n == 6) // R
    //         {
    //             els.push_back(new Prism(aux));
    //         }
    //         else // H
    //         {
    //             els.push_back(new Hexahedron(aux));
    //         }
    //     }
    //     return els;
    // }

    Element *JensTransformer::transformElement(vector<unsigned int> element)
    {
        vector<int> aux(element.begin(), element.end());
        int n = element.size();
        if (n == 4) // T
        {
            return new Tetrahedron(aux);
        }
        else if (n == 5) // P
        {
            return new Pyramid(aux);
        }
        else if (n == 6) // R
        {
            return new Prism(aux);
        }
        else // H
        {
            return new Hexahedron(aux);
        }
    }
    // necesita elementsJens y meshPoints actualizados.
    set<unsigned int> JensTransformer::computeLabeledNodes(double threshold)
    {
        cout << "computeLabeledNodes\n";
        cout << "\tPoints: " << (points).size() << endl;
        cout << "\tElementJens: " << (elementsJens).size() << endl;
        cout << "\tMeshPoints: " << (meshPoints).size() << endl;

        int count = 0;
        labeledNodes.clear();
        labeledOctants.clear();
        set<unsigned int> ln, lo;
        // set<unsigned int> nodes;
        // for (Element *element : elementsJens)
        for (int i = 0; i < elementsJens.size(); i++)
        {
            Element *element = elementsJens[i];
            double q = element->getElementJENS(points);

            if (q < threshold)
            {
                count++;
                for (unsigned int node : element->getPoints())
                    ln.insert(node);
            }
        }
        // printf("Labeled nodes: %ld\n", l.size());

        labeledNodes = ln;

        for (unsigned int i : ln)
        {
            (meshPoints).at(i).setLabeled(true);
            for (auto oct_index : (meshPoints).at(i).getElements())
            {
                lo.insert(oct_index);
            }
        }

        labeledOctants = lo;
        cout << "computeLabeledNodes labeled octants: " << lo.size() << "\n";
        return ln;
    };
}