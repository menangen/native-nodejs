#include <math.h>

unsigned char mountains = 0;

const double GRAD3[][3] = {
        {1,1,0},{-1,1,0},{1,-1,0},{-1,-1,0},
        {1,0,1},{-1,0,1},{1,0,-1},{-1,0,-1},
        {0,1,1},{0,-1,1},{0,1,-1},{0,-1,-1},
        {1,0,-1},{-1,0,-1},{0,-1,1},{0,1,1}};

unsigned char PERM[] = {
        151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140,
        36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120,
        234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
        88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
        134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133,
        230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161,
        1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130,
        116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250,
        124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227,
        47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44,
        154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98,
        108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34,
        242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14,
        239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121,
        50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243,
        141, 128, 195, 78, 66, 215, 61, 156, 180, 151, 160, 137, 91, 90, 15, 131,
        13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37,
        240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252,
        219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125,
        136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158,
        231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245,
        40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187,
        208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198,
        173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126,
        255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223,
        183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167,
        43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185,
        112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179,
        162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199,
        106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236,
        205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156,
        180};

void resort_permutation() {
    unsigned int random_int, max_random;
    const unsigned short size_permutation = 512;

    //sranddev();

    for (unsigned short counter = 0; counter < size_permutation; counter++) {

        max_random = 256;
        random_int = rand() % max_random;

        PERM[counter] = random_int;

    }


}

double cosine_interpolate(const double alpha, const double a, const double b) {
    const double ft = alpha * 3.1415927;
    double f = (1 - cos(ft)) * 0.5;
    
    return  a*(1-f) + b*f;
}


double inline
grad2(const int hash, const double x, const double y)
{
    const int h = hash & 15;
    return x * GRAD3[h][0] + y * GRAD3[h][1];
}


double
noise2(double x, double y, const double repeatx, const double repeaty, const int base)
{
    double perlin_result;

    double fx, fy;
    int A, AA, AB, B, BA, BB;
    int i = (int)floor(fmod(x, repeatx));
    int j = (int)floor(fmod(y, repeaty));
    int ii = (int)fmod(i + 1, repeatx);
    int jj = (int)fmod(j + 1, repeaty);
    i = (i & 255) + base;
    j = (j & 255) + base;
    ii = (ii & 255) + base;
    jj = (jj & 255) + base;

    x -= floor(x); y -= floor(y);

    /// Maps a value onto a quintic S-curve.
    /// @param x The value to map onto a quintic S-curve.
    /// @returns The mapped value.
    /// x should range from 0.0 to 1.0.
    ///
    /// The first derivitive of a quintic S-curve is zero at a = 0.0 and x = 1.0
    /// The second derivitive of a quintic S-curve is zero at a = 0.0 and x = 1.0
    fx = x*x*x * (x * (x * 6 - 15) + 10);
    fy = y*y*y * (y * (y * 6 - 15) + 10);

    A = PERM[i];
    AA = PERM[A + j];
    AB = PERM[A + jj];
    B = PERM[ii];
    BA = PERM[B + j];
    BB = PERM[B + jj];

    perlin_result = cosine_interpolate(fy,
                                       cosine_interpolate(fx, grad2(PERM[AA], x, y), grad2(PERM[BA], x - 1, y)),
                                       cosine_interpolate(fx, grad2(PERM[AB], x, y - 1), grad2(PERM[BB], x - 1, y - 1))
    );

    switch (mountains) {
        case 1:
            return fabs(perlin_result);
        case 2:
        case 4:
            return 1.0 - fabs(perlin_result);
        case 3:
            return fabs(1.0-fabs(perlin_result)*2.0)*2.0-1.0;
        default:
            return perlin_result;
    }

}