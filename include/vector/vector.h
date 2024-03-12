#pragma once

typedef struct vector_3d
{
    double x;
    double y;
    double z;
} *vector_3d_t;

struct vector_3d vector_add(vector_3d_t a, vector_3d_t b);
struct vector_3d vector_sub(vector_3d_t a, vector_3d_t b);
double vector_norm(vector_3d_t a);
void vector_clear(vector_3d_t a);
