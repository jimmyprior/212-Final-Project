#include <color.h>
#include <vector>
#include <limits>


ColorLAB bruteForceNearestNeighbor(ColorLAB &input, std::vector <ColorLAB> &colors) {    
    /*
    input : input color to find nearest neighbor of
    colors : list of colors to that we are attempting to find which 
        is the nearest neighbor to the input
    */

    //set min initially to max to closests will be set on first iteration    
    float minDist = std::numeric_limits<float>::max(); 
    ColorLAB closestColor; //intially unset

    //loop through all the colors in the palette and find the closest to the input
    for (int i = 0; i < colors.size(); i++) {
        //find distance between colors in palette and input color
        float dist = getEuclideanDist(input, colors.at(i));
        if (dist < minDist) {
            //distance between these points is lower than 
            //previous so set it to be the new min distance
            minDist = dist; 
            closestColor = colors.at(i);
        }
    }
    return closestColor;
}