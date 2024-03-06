#include "vector/vector.h"
#include <math.h>

struct vector_3d vector_add(vector_3d_t v1, vector_3d_t v2)
{
    struct vector_3d v = {0};
    v.x = v1->x + v2->x;
    v.y = v1->y + v2->y;
    v.z = v1->z + v2->z;
    return v;
}

struct vector_3d vector_sub(vector_3d_t v1, vector_3d_t v2)
{
    struct vector_3d v = {0};
    v.x = v1->x - v2->x;
    v.y = v1->y - v2->y;
    v.z = v1->z - v2->z;
    return v;
}

double vector_norm(vector_3d_t v)
{
    return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

void vector_clear(vector_3d_t v)
{
    v->x = v->y = v->z = 0.0;
}
