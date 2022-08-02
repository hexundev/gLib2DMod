// This example shows an object that moves and a camera that follows it

#include <pspkernel.h>
#include <pspctrl.h>
#include "../../glib2dExt.h"
#include "../../sample/callbacks.h"

PSP_MODULE_INFO("App", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main()
{
	callbacks_setup();

	g2dInit();

	SceCtrlData pad;

	g2dTexture* tex = g2dTexLoadFile("tex.png", G2D_SWIZZLE);
	g2dTexture* bgTex = g2dTexLoadSwizzled("bg.bin");

	// g2dTexture* bgTex = g2dTexLoadFile("bg.png", G2D_SWIZZLE);
	// g2dTexSaveSwizzled("bg.bin", bgTex);	

	// Background images, can also do this with texture repeat
	// but this is just an example
	int numBg = 5;
	g2dObject bg[numBg];
	for (int i = 0; i < numBg; ++i)
	{
		g2dInitObjectTexture(&bg[i], bgTex);
		bg[i].x = i * bg[i].scale_w;
	}

	// Controllable object
	g2dObject object;
	g2dInitObjectTexture(&object, tex);
	object.x = G2D_SCR_W / 2.0f;
	object.y = G2D_SCR_H / 2.0f;
	object.center_x = object.center_y = 0.5f; // For rotation

	float zoom = 1.0f;
	while (1)
	{
		// Controls
		sceCtrlPeekBufferPositive(&pad, 1);
		if (pad.Buttons & PSP_CTRL_LEFT)     object.x -= 2, object.scale_w = -object.crop_w;
		if (pad.Buttons & PSP_CTRL_RIGHT)    object.x += 2, object.scale_w = object.crop_w;
		if (pad.Buttons & PSP_CTRL_UP)       zoom += 0.01f;
		if (pad.Buttons & PSP_CTRL_DOWN)     zoom -= 0.01f;
		if (pad.Buttons & PSP_CTRL_START) 	 zoom = 1.0f;
		if (pad.Buttons & PSP_CTRL_LTRIGGER) object.rot -= 0.05f;
		if (pad.Buttons & PSP_CTRL_RTRIGGER) object.rot += 0.05;

		// Display
		g2dClear(G2D_COL_GRAY);

		// Set states
		g2dSetBlendMode(G2D_BLEND_ALPHA);
		g2dSetTexLinear(true);
		g2dSetTexRepeat(false);

		g2dExtBegin();

		// View follows object
		float viewX = object.x * zoom - (G2D_SCR_W / 2.0f);
		float viewY = object.y * zoom - (G2D_SCR_H / 2.0f);
		g2dExtSetView(
			viewX, viewY, 0.0f,
			0.0f,
			zoom, zoom);

		// Background images
		g2dExtDrawObjects(bg, numBg, bgTex);

		// Object
		g2dExtDrawObject(&object, tex);

		g2dExtEnd();

		g2dFlip(G2D_VSYNC);
	}

	sceKernelExitGame();
	return 0;
}
