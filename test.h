#include <math.h>

float cosine_interpolate(const float alpha, const float a, const float b) {
    const float ft = alpha * 3.1415927;
    float f = (1 - cos(ft)) * 0.5;
    
    return  a*(1-f) + b*f;
}