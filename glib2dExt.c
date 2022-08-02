#include "glib2dExt.h"

#include <pspgu.h>
#include <pspgum.h>

const int COLOR_VERTEX_FORMAT = GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D;
const int TEXTURE_VERTEX_FORMAT = GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_3D;
const float PROJECTION_RATIO = 16.0f / 9.0f;

typedef struct g2dExtColorVertex
{
	unsigned int color;
	float x, y, z;

} g2dExtColorVertex;

typedef struct g2dExtTextureVertex
{
	float u, v;
	unsigned int color;
	float x, y, z;

} g2dExtTextureVertex;

typedef struct
{
	float x;
	float y;
	float fov;
	float width;
	float height;
	float zNear;
	float zFar;
}_g2dProjection;

typedef struct
{
	ScePspFVector3 pos;
	ScePspFVector3 scale;
	ScePspFVector3 rotation;
}_g2dView;

typedef struct
{
	_g2dProjection proj;
	_g2dView view;
}_g2dExtState;

static _g2dExtState state;


/* Public functions */

void g2dExtBegin()
{
	sceGumMatrixMode(GU_MODEL);
	sceGumLoadIdentity();

	g2dExtResetOrtho();
	g2dExtResetView();
}

void g2dExtEnd()
{
	g2dExtResetOrtho();
	g2dExtResetView();
}

void g2dExtSetPerspective(float fov, float zNear, float zFar)
{
	state.proj.fov = fov;
	state.proj.zNear = zNear;
	state.proj.zFar = zFar;

	sceGumMatrixMode(GU_PROJECTION);
	sceGumLoadIdentity();
	sceGumPerspective(fov, PROJECTION_RATIO, zNear, zFar);
}

void g2dExtSetOrtho(float x, float y, float width, float height, float zNear, float zFar)
{
	state.proj.x = x;
	state.proj.y = y;
	state.proj.width = width;
	state.proj.height = height;
	state.proj.zNear = zNear;
	state.proj.zFar = zFar;

	sceGumMatrixMode(GU_PROJECTION);
	sceGumLoadIdentity();
	sceGumOrtho(x, width, height, y, zNear, zFar);
}

void g2dExtResetOrtho()
{
	g2dExtSetOrtho(0.0f, 0.0f, (float)G2D_SCR_W, (float)G2D_SCR_H, -1.0f, 1.0f);
}

void g2dExtSetView(float x, float y, float z, float rotZ, float scaleX, float scaleY)
{
	state.view.pos.x = -x;
	state.view.pos.y = -y;
	state.view.pos.z = z;

	state.view.rotation.x = 0.0f;
	state.view.rotation.y = 0.0f;
	state.view.rotation.z = rotZ;

	state.view.scale.x = scaleX;
	state.view.scale.y = scaleY;
	state.view.scale.z = 1.0f;

	sceGumMatrixMode(GU_VIEW);
	sceGumLoadIdentity();
	sceGumTranslate(&state.view.pos);
	sceGumRotateXYZ(&state.view.rotation);
	sceGumScale(&state.view.scale);
}

void g2dExtResetView()
{
	g2dExtSetView(0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f);
}

#define obj objects[index]
#define vxRot(_x,_y) ((_x * cosAngle - _y * sinAngle) + obj.x);
#define vyRot(_x,_y) ((_x * sinAngle + _y * cosAngle) + obj.y);
static g2dExtTextureVertex* _setTextureQuad(g2dExtTextureVertex* verts, g2dObject* objects, int index, float texWidth, float texHeight)
{
	const float cx = obj.center_x * obj.scale_w;
	const float cy = obj.center_y * obj.scale_h;

	// UVs
	const float u1 = obj.crop_x * texWidth;
	const float v1 = obj.crop_y * texHeight;
	const float u2 = u1 + obj.crop_w * texWidth;
	const float v2 = v1 + obj.crop_h * texHeight;

	// Coordinates
	const float x1 = -cx;
	const float y1 = -cy;
	const float x2 = (obj.scale_w - cx);
	const float y2 = (obj.scale_h - cy);

	float cosAngle;
	float sinAngle;
	G2D_SINCOSF(obj.rot, &sinAngle, &cosAngle);

	/* Tri 1 */

	// 0, 0
	verts[0].color = obj.color;
	verts[0].u = u1;
	verts[0].v = v1;
	verts[0].x = vxRot(x1, y1);
	verts[0].y = vyRot(x1, y1);
	verts[0].z = obj.z;

	// 1, 0
	verts[1].color = obj.color;
	verts[1].u = u2;
	verts[1].v = v1;
	verts[1].x = vxRot(x2, y1);
	verts[1].y = vyRot(x2, y1);
	verts[1].z = obj.z;

	// 1, 1
	verts[2].color = obj.color;
	verts[2].u = u2;
	verts[2].v = v2;
	verts[2].x = vxRot(x2, y2);
	verts[2].y = vyRot(x2, y2);
	verts[2].z = obj.z;

	/* Tri 2 */

	// 0, 0
	verts[3].color = obj.color;
	verts[3].u = u1;
	verts[3].v = v1;
	verts[3].x = vxRot(x1, y1);
	verts[3].y = vyRot(x1, y1);
	verts[3].z = obj.z;

	// 1,1
	verts[4].color = obj.color;
	verts[4].u = u2;
	verts[4].v = v2;
	verts[4].x = vxRot(x2, y2);
	verts[4].y = vyRot(x2, y2);
	verts[4].z = obj.z;

	// 0,1
	verts[5].color = obj.color;
	verts[5].u = u1;
	verts[5].v = v2;
	verts[5].x = vxRot(x1, y2);
	verts[5].y = vyRot(x1, y2);
	verts[5].z = obj.z;

	return (g2dExtTextureVertex*)(verts + 6);
}


static void _drawTextureObject(g2dObject* objects, int count, g2dTexture* texture)
{
	if (objects == NULL || count == 0)
	{
		return;
	}

	int vertexCount = count * 6;

	g2dExtTextureVertex* verts = (g2dExtTextureVertex*)sceGuGetMemory(vertexCount * sizeof(g2dExtTextureVertex));
	if (verts == NULL)
	{
		return;
	}

	float texWidth = 0.0f;
	float texHeight = 0.0f;
	if (texture != NULL)
	{
		texWidth = 1.0f / (float)texture->tw;
		texHeight = 1.0f / (float)texture->th;
	}

	g2dExtTextureVertex* currentVerts = verts;
	for (int i = 0; i < count; ++i)
	{
		currentVerts = _setTextureQuad(currentVerts, objects, i, texWidth, texHeight);
	}

	sceGuColor(G2D_COL_WHITE);
	g2dSetTexture(texture, 0);

	sceGumDrawArray(
		GU_TRIANGLES,
		TEXTURE_VERTEX_FORMAT,
		vertexCount,
		NULL,
		verts);
}

void g2dExtDrawObjects(g2dObject* objects, int count, g2dTexture* texture)
{
	if (objects == NULL || count == 0 ||
		(texture != NULL && (texture->w == 0 || texture->h == 0)))
	{
		return;
	}

	_drawTextureObject(objects, count, texture);
}

void g2dExtDrawObject(g2dObject* object, g2dTexture* texture)
{
	g2dExtDrawObjects(object, 1, texture);
}