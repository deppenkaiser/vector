#include "vector/vector.h"
#include <math.h>

struct vector_3d vector_add(vector_3d_t a, vector_3d_t b)
{
    struct vector_3d v = {0};
    v.x = a->x + b->x;
    v.y = a->y + b->y;
    v.z = a->z + b->z;
    return v;
}

struct vector_3d vector_sub(vector_3d_t a, vector_3d_t b)
{
    struct vector_3d v = {0};
    v.x = a->x - b->x;
    v.y = a->y - b->y;
    v.z = a->z - b->z;
    return v;
}

double vector_norm(vector_3d_t a)
{
    return sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
}

void vector_clear(vector_3d_t a)
{
    a->x = a->y = a->z = 0.0;
}
