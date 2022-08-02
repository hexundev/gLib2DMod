#include "glib2d.h"

/**
 * Extension functions to use matrices.
 * 
 * Not compatible with regular g2d draw code, these use vertices with GU_TRANSFORM_3D.
 * Draws untextured/textured objects with 2 triangles.
 * 
 */

// Call before drawing
void g2dExtBegin();

// Call after drawing
void g2dExtEnd();

// Set the projection matrix.
void g2dExtSetPerspective(float fov, float zNear, float zFar);

// Set the projection matrix.
void g2dExtSetOrtho(float x, float y, float width, float height, float zNear, float zFar);

// Resets the projection: g2dExtSetOrtho(0, 0, G2D_SCR_W, G2D_SCR_H, -1, 1);
void g2dExtResetOrtho();

// Set the view matrix in 2D
void g2dExtSetView(float x, float y, float z, float rotZ, float scaleX, float scaleY);

// Todo: for perspective projection
//void g2dExtSetView3D(...);

// Resets the view matrix: g2dExtSetView2D(0, 0, 0, 0, -1, 1);
void g2dExtResetView();

// Draw objects using 3d vertex mode, texture optional
void g2dExtDrawObjects(g2dObject* objects, int count, g2dTexture* texture);

void g2dExtDrawObject(g2dObject* object, g2dTexture* texture);
