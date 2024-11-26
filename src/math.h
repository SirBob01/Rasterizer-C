#ifndef MATH_H
#define MATH_H

/**
 * @brief Cartesian position in 2 dimensional space.
 *
 */
typedef struct {
    float x;
    float y;
} vec2_t;

/**
 * @brief Cartesian position in 3-dimensional space.
 *
 */
typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

/**
 * @brief Cartesian position in 4-dimensional space.
 *
 */
typedef struct {
    float x;
    float y;
    float z;
    float w;
} vec4_t;

/**
 * @brief Quaternion.
 *
 */
typedef struct {
    float x;
    float y;
    float z;
    float w;
} quat_t;

/**
 * @brief 4x4 matrix.
 *
 */
typedef struct {
    float elements[16];
} mat4_t;

/**
 * @brief Compute the dot product of 2D vectors.
 *
 * @param a
 * @param b
 * @return float
 */
float dot_vec2(const vec2_t *a, const vec2_t *b);

/**
 * @brief Compute the dot product of 3D vectors.
 *
 * @param a
 * @param b
 * @return float
 */
float dot_vec3(const vec3_t *a, const vec3_t *b);

/**
 * @brief Compute the cross product of 3D vectors.
 *
 * @param a
 * @param b
 * @param c
 */
void cross_vec3(const vec3_t *a, const vec3_t *b, vec3_t *c);

/**
 * @brief Negate a 3D vector.
 *
 * @param a
 */
void negate_vec3(vec3_t *a);

/**
 * @brief Normalize a 3D vector.
 *
 * @param a
 */
void normalize_vec3(vec3_t *a);

/**
 * @brief Compute barycentric coordinates of a 2D triangle
 *
 * @param a
 * @param b
 * @param c
 * @param point
 * @param result
 */
void compute_barycentric(const vec2_t *a,
                         const vec2_t *b,
                         const vec2_t *c,
                         const vec2_t *point,
                         vec3_t *result);

/**
 * @brief Make an axis-angle (radians) quaternion.
 *
 * @param quat
 * @param axis
 * @param angle
 */
void make_axis_angle_quat(quat_t *quat, const vec3_t *axis, float angle);

/**
 * @brief Make the identity matrix.
 *
 * @param mat
 */
void make_identity_mat4(mat4_t *mat);

/**
 * @brief Create a transformation matrix.
 *
 * @param mat
 * @param translate
 * @param rotation
 * @param scale
 */
void make_transform_mat4(mat4_t *mat,
                         vec3_t *translate,
                         quat_t *rotation,
                         vec3_t *scale);

/**
 * @brief Make a view matrix.
 *
 * @param mat
 * @param position
 * @param forward
 * @param up
 */
void make_view_mat4(mat4_t *mat, vec3_t *position, vec3_t *forward, vec3_t *up);
/**
 * @brief Make a perspective projection matrix.
 *
 * @param mat
 * @param aspect
 * @param fovy
 * @param znear
 * @param zfar
 */
void make_perspective_mat4(mat4_t *mat,
                           float aspect,
                           float fovy,
                           float znear,
                           float zfar);

/**
 * @brief c = a * b
 *
 * @param a
 * @param b
 * @param c
 */
void mul_mat4(mat4_t *a, mat4_t *b, mat4_t *c);

/**
 * @brief Apply a 4x4 matrix to a 4D vector.
 *
 * @param point
 * @param transform
 * @param result
 */
void apply_mat4(vec4_t *point, mat4_t *transform, vec4_t *result);

/**
 * @brief Convert a 3D local vertex position to clip space.
 *
 * @param position
 * @param mvp
 * @param result
 */
void local_to_clip(vec3_t *position, mat4_t *mvp, vec3_t *result);

/**
 * @brief Convert a 3D clip position to screen space.
 *
 * @param clip
 * @param width
 * @param height
 * @param result
 */
void clip_to_screen(vec3_t *clip,
                    unsigned width,
                    unsigned height,
                    vec2_t *result);

/**
 * @brief Convert degrees to radians.
 *
 * @param v
 * @return float
 */
float degrees_to_radians(float v);

#endif