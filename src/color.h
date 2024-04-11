/*
Includes structs to represent color data in different spaces (mainly RGB and L*A*B*)
Also includes functions for calculating euclidean distance between CIELAB colors
Also includes functions for converting RGB to L*A*B* colors
ColorLAB and ColorRGB have less than comparison ability so that they can be used as map keys 
    for quick lookup so that input ouput cielab can be mapped to input rgb for quick conversion 
    from cielab back to rgb equivalent without the need to recompute it
*/

#include <cmath>



struct ColorLAB {
    /*
    we need to compare colors in the cielab color space for accurate comparisons 
    so this struct is what the algorithms should be using for the comparisons of 3d data points 
    (CIELAB colors)
    */
    float l;
    float a;
    float b;
};


bool operator<(const ColorLAB& c1, const ColorLAB& c2) { 
    //add operator so that ColorLab and ColorRGB can be used as map keys for quick lookup
    //https://www.geeksforgeeks.org/c-map-key-user-define-data-type/
    //will compare using vector length
    int c1mag = std::sqrt(std::pow(c1.l, 2) + std::pow(c1.a, 2) + std::pow(c1.b, 2));
    int c2mag = std::sqrt(std::pow(c2.l, 2) + std::pow(c2.a, 2) + std::pow(c2.b, 2));

    return c1mag < c2mag;
} 

struct ColorRGB {
    //standard RGB 
    int r; 
    int g; 
    int b;
};

bool operator<(const ColorRGB& c1, const ColorRGB& c2) { 
    //add operator so that ColorLab and ColorRGB can be used as map keys for quick lookup
    //https://www.geeksforgeeks.org/c-map-key-user-define-data-type/
    //will compare using vector length
    int c1mag = std::sqrt(std::pow(c1.r, 2) + std::pow(c1.r, 2) + std::pow(c1.r, 2));
    int c2mag = std::sqrt(std::pow(c2.r, 2) + std::pow(c2.r, 2) + std::pow(c2.r, 2));

    return c1mag < c2mag;
} 
  

struct ColorXYZ {
    /*
    intermediate color space needed for conversion from rgb space to cielab space
    */
    float x;
    float y;
    float z;
};


float getEuclideanDist(ColorLAB &color1, ColorLAB &color2) {
    /*
    calculates the euclidean distance between two cielab colors (3d points)
    */
    return std::sqrt(
        std::pow(color1.l - color2.l, 2) + 
        std::pow(color1.a - color2.a, 2) + 
        std::pow(color1.b - color2.b, 2) 
    );
}


float getDistApprox(ColorLAB &color1, ColorLAB &color2) {
    /*
    for increased performance no square root is needed and comparisons will still be valid
    not actual distance but still can be used for valid comparisons of distance 
    */
    return std::pow(color1.l - color2.l, 2) + std::pow(color1.a - color2.a, 2) + std::pow(color1.b - color2.b, 2);
}


ColorXYZ RGBtoXYZ(ColorRGB &color) {
    /*
    function to convert color representation in RGB space to color representation in XYZ space
    */

    //PSEUDO CODE FOR CONVERSIONS TAKEN FROM http://www.easyrgb.com/en/math.php

    float var_R = float(color.r) / 255;
    float var_G = float(color.g) / 255;
    float var_B = float(color.b) / 255;

    if (var_R > 0.04045) {
        var_R = std::pow((var_R + 0.055 ) / 1.055, 2.4);
    }
    else {
        var_R = var_R / 12.92;
    }            
    if ( var_G > 0.04045 ) {
        var_G = std::pow((var_G + 0.055 ) / 1.055, 2.4);
    }
    else {
        var_G = var_G / 12.92;
    }
    if ( var_B > 0.04045 ) {
        var_B = std::pow((var_B + 0.055 ) / 1.055, 2.4);
    }
    else {
        var_B = var_B / 12.92;
    }

    var_R = var_R * 100;
    var_G = var_G * 100;
    var_B = var_B * 100;

    ColorXYZ output;

    //X, Y and Z output refer to a D65/2° standard illuminant.

    output.x = var_R * 0.4124 + var_G * 0.3576 + var_B * 0.1805;
    output.y = var_R * 0.2126 + var_G * 0.7152 + var_B * 0.0722;
    output.z = var_R * 0.0193 + var_G * 0.1192 + var_B * 0.9505;

    return output;
}


ColorLAB XYZtoLAB(ColorXYZ &color) {
    /*
    function to convert RGB color to XYZ color

    code is taken from here: http://www.easyrgb.com/en/math.php
    uses (95.047, 100.000, 108.883) (D65 2 degree)

    PSEUDO CODE FOR CONVERSIONS TAKEN FROM http://www.easyrgb.com/en/math.php

    */

    float var_X = color.x / 95.047;
    float var_Y = color.y / 100.000;
    float var_Z = color.z / 108.883;

    if ( var_X > 0.008856 ) {
        var_X = std::pow(var_X, 1.0/3);
    }
    else {
        var_X = ( 7.787 * var_X ) + (16.0/116);
    }
    if ( var_Y > 0.008856 ) {
        var_Y = std::pow(var_Y, 1.0/3);
    }
    else {
        var_Y = ( 7.787 * var_Y ) + (16.0/116);
    }
    if ( var_Z > 0.008856 ) {
        var_Z = std::pow(var_Z, 1.0/3);
    }
    else {
        var_Z = ( 7.787 * var_Z ) + (16.0/116);
    }

    ColorLAB output;

    output.l = ( 116 * var_Y ) - 16;
    output.a = 500 * ( var_X - var_Y );
    output.b = 200 * ( var_Y - var_Z );
}