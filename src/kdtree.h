//https://blog.krum.io/k-d-trees/

#include <color.h>
#include <vector>

//https://blog.krum.io/k-d-trees/
//https://courses.engr.illinois.edu/cs225/sp2019/notes/kd-tree/#:~:text=Overview,based%20on%20a%20certain%20dimension.


class Node {
    private : 
        ColorLAB *color;
        int dimension; //dimension of ColorLAB (0:l, 1:a, 2:b)

    public:
        Node *left;
        Node *right;
        Node *parent; //do i need a reference to the parent?
};


Node recursiveCreate(std::vector < ColorLAB > colors, int depth) {
    //COLORS MUST BE SORTED BEFORE BEING PASSED
    //https://www.baeldung.com/cs/k-d-trees (pseudo referenced for this)
    
}

class KDTree {
    /*
    3D tree implementation (kd tree) for CIELAB colors
    does not support insertion or deletion (no need since pallette is constant)
    */
    private:

    public: 

        KDTree(std::vector< ColorLAB > colors) {
            //https://www.baeldung.com/cs/k-d-trees (pseudo code for this)

            /*
                initialize with a vector of colors (palette). 
                i am not going to support adding colors later 
                i think this would probably unbalance the tree 
                all colors will be added when initialized
            */

            //construct the tree
        }

        ColorLAB findNearestNeighbors(ColorLAB &reference, int number = 1) {
            /*
            find the nearest neightbor (CIELAB) color to the reference color
            number : number of neighbors 
            */
        }
};