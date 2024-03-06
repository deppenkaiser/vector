#pragma once

typedef struct vector_3d
{
    double x;
    double y;
    double z;
} *vector_3d_t;

struct vector_3d vector_add(vector_3d_t v1, vector_3d_t v2);
struct vector_3d vector_sub(vector_3d_t v1, vector_3d_t v2);
double vector_norm(vector_3d_t v);
void vector_clear(vector_3d_t v);
