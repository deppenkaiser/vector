#include "vector/vector.h"
#include <math.h>
#include <stddef.h>
#include <string.h>

// === 3D Vector Functions (existing) ===

struct vector_3d vector_add(const vector_3d_t a, const vector_3d_t b)
{
    struct vector_3d v = {0};
    v.x = a->x + b->x;
    v.y = a->y + b->y;
    v.z = a->z + b->z;
    return v;
}

struct vector_3d vector_sub(const vector_3d_t a, const vector_3d_t b)
{
    struct vector_3d v = {0};
    v.x = a->x - b->x;
    v.y = a->y - b->y;
    v.z = a->z - b->z;
    return v;
}

struct vector_3d vector_cross(const vector_3d_t a, const vector_3d_t b)
{
    struct vector_3d v = {0};
    v.x = a->y * b->z - a->z * b->y;
    v.y = a->z * b->x - a->x * b->z;
    v.z = a->x * b->y - a->y * b->x;
    return v;
}

struct vector_3d vector_nabla(vector_time_row_t r)
{
    struct vector_3d v1 = {0};
    struct vector_3d v2 = {0};
    struct vector_3d w = {0};

    v2 = vector_sub(&r[2], &r[1]);
    v1 = vector_sub(&r[1], &r[0]);
    w = vector_sub(&v2, &v1);

    double dx = w.x, dy = w.y, dz = w.z;
    
    w.x = dz / (r[2].y - r[1].y) - dy / (r[2].z - r[1].z);
    w.y = dx / (r[2].z - r[1].z) - dz / (r[2].x - r[1].x);
    w.z = dy / (r[2].x - r[1].x) - dx / (r[2].y - r[1].y);

    return w;
}

struct vector_3d vector_rotation_x(const vector_3d_t r, cld phi_rad)
{
    struct vector_3d row1 = {1.0, 0.0, 0.0};
    struct vector_3d row2 = {0.0, cosl(phi_rad), -sinl(phi_rad)};
    struct vector_3d row3 = {0.0, sinl(phi_rad), cosl(phi_rad)};
    struct vector_3d v = {vector_dot(r, &row1), vector_dot(r, &row2), vector_dot(r, &row3)};
    return v;
}

struct vector_3d vector_rotation_y(const vector_3d_t r, cld phi_rad)
{
    struct vector_3d row1 = {cosl(phi_rad), 0.0, sinl(phi_rad)};
    struct vector_3d row2 = {0.0, 1.0, 0.0};
    struct vector_3d row3 = {-sinl(phi_rad), 0.0, cosl(phi_rad)};
    struct vector_3d v = {vector_dot(r, &row1), vector_dot(r, &row2), vector_dot(r, &row3)};
    return v;
}

struct vector_3d vector_rotation_z(const vector_3d_t r, cld phi_rad)
{
    struct vector_3d row1 = {cosl(phi_rad), -sinl(phi_rad), 0.0};
    struct vector_3d row2 = {sinl(phi_rad), cosl(phi_rad), 0.0};
    struct vector_3d row3 = {0.0, 0.0, 1.0};
    struct vector_3d v = {vector_dot(r, &row1), vector_dot(r, &row2), vector_dot(r, &row3)};
    return v;
}

struct vector_3d vector_multiply_scalar(const vector_3d_t a, cld s)
{
    struct vector_3d v = {0};
    v.x = a->x * s;
    v.y = a->y * s;
    v.z = a->z * s;
    return v;
}

struct vector_3d vector_divide_scalar(const vector_3d_t a, cld s)
{
    struct vector_3d v = {0};
    v.x = a->x / s;
    v.y = a->y / s;
    v.z = a->z / s;
    return v;
}

struct vector_astro vector_cartesian_to_astronomical(const vector_3d_t a)
{
    struct vector_astro p = {0};
    cld rho_sqr = a->x * a->x + a->y * a->y;
    cld rho = sqrtl(rho_sqr);
    p.r = sqrtl(rho_sqr + a->z * a->z);
    p.theta = ((a->z == 0.0) || (rho == 0.0)) ? 0.0 : atan2l(a->z, rho);
    p.phi = ((a->x == 0.0) || (a->y == 0.0)) ? 0.0 : atan2l(a->y, a->x);
    p.phi = (p.phi >= 0.0) ? p.phi : p.phi + 2.0 * acosl(-1.0);
    return p;
}

ld vector_dot(const vector_3d_t a, const vector_3d_t b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

ld vector_norm(const vector_3d_t a)
{
    return sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
}

struct vector_3d vector_clear(vector_3d_t a)
{
    struct vector_3d v = {0};
    v.x = v.y = v.z = 0.0L;

    if (a != NULL)
    {
        *a = v;
    }

    return v;
}

struct vector_3d vector_normalize(const vector_3d_t a)
{
    struct vector_3d v = {0};
    ld n = vector_norm(a);
    if (n < 1e-30L)
    {
        v.x = 0.0L;
        v.y = 0.0L;
        v.z = 0.0L;
        return v;
    }
    cld inv = 1.0L / n;
    v.x = a->x * inv;
    v.y = a->y * inv;
    v.z = a->z * inv;
    return v;
}

ld vector_distance(const vector_3d_t a, const vector_3d_t b)
{
    struct vector_3d d = vector_sub(a, b);
    return vector_norm(&d);
}

// === 2D Vector Functions ===

struct vector_2d vector_2d_add(const vector_2d_t a, const vector_2d_t b)
{
    struct vector_2d v = {a->x + b->x, a->y + b->y};
    return v;
}

struct vector_2d vector_2d_sub(const vector_2d_t a, const vector_2d_t b)
{
    struct vector_2d v = {a->x - b->x, a->y - b->y};
    return v;
}

// === 4x4 Matrix Functions (column-major) ===

struct matrix_4x4 matrix_4x4_identity(void)
{
    struct matrix_4x4 mat = {0};
    memset(mat.m, 0, sizeof(mat.m));
    mat.m[0] = 1.0f;
    mat.m[5] = 1.0f;
    mat.m[10] = 1.0f;
    mat.m[15] = 1.0f;
    return mat;
}

struct matrix_4x4 matrix_4x4_multiply(const matrix_4x4_t a, const matrix_4x4_t b)
{
    struct matrix_4x4 result = {0};
    memset(result.m, 0, sizeof(result.m));
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++) {
                sum += a->m[i + k * 4] * b->m[k + j * 4];
            }
            result.m[i + j * 4] = sum;
        }
    }
    
    return result;
}

struct matrix_4x4 matrix_4x4_ortho(float left, float right, float bottom, float top)
{
    struct matrix_4x4 mat = {0};
    memset(mat.m, 0, sizeof(mat.m));
    
    mat.m[0] = 2.0f / (right - left);
    mat.m[5] = 2.0f / (top - bottom);
    mat.m[10] = -1.0f;
    mat.m[12] = -(right + left) / (right - left);
    mat.m[13] = -(top + bottom) / (top - bottom);
    mat.m[14] = 0.0f;
    mat.m[15] = 1.0f;
    
    return mat;
}

struct matrix_4x4 matrix_4x4_translate_3d(float tx, float ty, float tz)
{
    struct matrix_4x4 mat = matrix_4x4_identity();
    mat.m[12] = tx;
    mat.m[13] = ty;
    mat.m[14] = tz;
    return mat;
}

struct matrix_4x4 matrix_4x4_scale_3d(float sx, float sy, float sz)
{
    struct matrix_4x4 mat = matrix_4x4_identity();
    mat.m[0] = sx;
    mat.m[5] = sy;
    mat.m[10] = sz;
    return mat;
}

struct matrix_4x4 matrix_4x4_rotate_x(float angle_rad)
{
    struct matrix_4x4 mat = matrix_4x4_identity();
    float c = cosf(angle_rad);
    float s = sinf(angle_rad);
    mat.m[5] = c;
    mat.m[6] = -s;
    mat.m[9] = s;
    mat.m[10] = c;
    return mat;
}

struct matrix_4x4 matrix_4x4_rotate_y(float angle_rad)
{
    struct matrix_4x4 mat = matrix_4x4_identity();
    float c = cosf(angle_rad);
    float s = sinf(angle_rad);
    mat.m[0] = c;
    mat.m[2] = s;
    mat.m[8] = -s;
    mat.m[10] = c;
    return mat;
}

struct matrix_4x4 matrix_4x4_rotate_z(float angle_rad)
{
    struct matrix_4x4 mat = matrix_4x4_identity();
    float c = cosf(angle_rad);
    float s = sinf(angle_rad);
    mat.m[0] = c;
    mat.m[1] = -s;
    mat.m[4] = s;
    mat.m[5] = c;
    return mat;
}

struct matrix_4x4 matrix_4x4_perspective(float fov_rad, float aspect, float near_plane, float far_plane)
{
    struct matrix_4x4 mat = {0};
    memset(mat.m, 0, sizeof(mat.m));

    float tan_half = tanf(fov_rad / 2.0f);
    mat.m[0] = 1.0f / (aspect * tan_half);
    mat.m[5] = -1.0f / tan_half;  // Vulkan Y-down: negate Y
    mat.m[10] = far_plane / (far_plane - near_plane);
    mat.m[11] = 1.0f;
    mat.m[14] = (near_plane * far_plane) / (near_plane - far_plane);
    mat.m[15] = 0.0f;

    return mat;
}

struct matrix_4x4 matrix_4x4_lookat(float eye_x, float eye_y, float eye_z,
                                     float center_x, float center_y, float center_z,
                                     float up_x, float up_y, float up_z)
{
    struct matrix_4x4 mat = {0};
    memset(mat.m, 0, sizeof(mat.m));

    // Forward vector (from eye to center, normalized)
    float fx = center_x - eye_x;
    float fy = center_y - eye_y;
    float fz = center_z - eye_z;
    float flen = sqrtf(fx * fx + fy * fy + fz * fz);
    if (flen > 0.0f) { fx /= flen; fy /= flen; fz /= flen; }

    // Right vector = forward x up
    float rx = fy * up_z - fz * up_y;
    float ry = fz * up_x - fx * up_z;
    float rz = fx * up_y - fy * up_x;
    float rlen = sqrtf(rx * rx + ry * ry + rz * rz);
    if (rlen > 0.0f) { rx /= rlen; ry /= rlen; rz /= rlen; }

    // True up vector = right x forward
    float ux = ry * fz - rz * fy;
    float uy = rz * fx - rx * fz;
    float uz = rx * fy - ry * fx;

    // Vulkan left-handed: forward is +Z (into screen)
    mat.m[0] = rx;   mat.m[4] = ux;   mat.m[8]  = fx;   mat.m[15] = 1.0f;
    mat.m[1] = ry;   mat.m[5] = uy;   mat.m[9]  = fy;
    mat.m[2] = rz;   mat.m[6] = uz;   mat.m[10] = fz;
    mat.m[12] = -(rx * eye_x + ry * eye_y + rz * eye_z);
    mat.m[13] = -(ux * eye_x + uy * eye_y + uz * eye_z);
    mat.m[14] = -(fx * eye_x + fy * eye_y + fz * eye_z);

    return mat;
}

struct vector_2d matrix_4x4_transform_point(const matrix_4x4_t mat, const vector_2d_t point)
{
    struct vector_2d result = {0};
    
    float x = point->x;
    float y = point->y;
    
    result.x = mat->m[0] * x + mat->m[4] * y + mat->m[12];
    result.y = mat->m[1] * x + mat->m[5] * y + mat->m[13];
    
    return result;
}

// === 2D Orthographic Projection (Pixel Space → Clip Space) ===

// Y-down: pixel (0,0) at top-left → Vulkan clip (-1,1) top-left, (1,-1) bottom-right
struct matrix_4x4 matrix_4x4_ortho_pixel_y_down(uint32_t width, uint32_t height)
{
    struct matrix_4x4 mat = {0};
    memset(mat.m, 0, sizeof(mat.m));
    
    float w = (float)width;
    float h = (float)height;
    
    // Column-major: maps pixel (0,0) → clip (-1,1), pixel (w,h) → clip (1,-1)
    mat.m[0]  = 2.0f / w;
    mat.m[5]  = -2.0f / h;
    mat.m[10] = 1.0f;
    mat.m[12] = -1.0f;
    mat.m[13] = 1.0f;
    mat.m[15] = 1.0f;
    
    return mat;
}

// Y-up: pixel (0,0) at bottom-left → Vulkan clip (-1,-1) bottom-left, (1,1) top-right
struct matrix_4x4 matrix_4x4_ortho_pixel_y_up(uint32_t width, uint32_t height)
{
    struct matrix_4x4 mat = {0};
    memset(mat.m, 0, sizeof(mat.m));
    
    float w = (float)width;
    float h = (float)height;
    
    mat.m[0]  = 2.0f / w;
    mat.m[5]  = 2.0f / h;
    mat.m[10] = 1.0f;
    mat.m[12] = -1.0f;
    mat.m[13] = -1.0f;
    mat.m[15] = 1.0f;
    
    return mat;
}
