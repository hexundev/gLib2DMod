## gLib2DExt

Some functions to extend gLib2D, lets you set a view matrix for scrolling and zooming.
See sample02.
Todo: Support perspective projection, better vertex handling and use different format for untextured.

Same license as gLib2D.

## Changes to gLib2D

- Added function to set blend modes
- Renamed color enum values with G2D_COL_ prefix
- Exposed a few functions
- Exposed object struct and functions to draw them directly
- Copied change from [joel16/gLib2D](https://github.com/joel16/gLib2D) to load a texture from a buffer instead of file
- Changed PNG load to use the added function

## Credits
- [joel16](https://github.com/joel16/gLib2D)
- [Geecko](https://github.com/libcg/gLib2D)
# Original Readme

## Introduction 

gLib2D by Geecko - A simple, fast, light-weight 2D graphics library.
This library has been designed to replace the old graphics.c library
and to simplify the use of pspgu.
The goals : keep it simple, keep it small, keep it fast.

### Known limitations 

- Draw & display buffers can't actually be used as real textures. Just a way
  to get the vram pointer.
- No support for multiples contexts (e.g. sharing coordinates between
  textures using some g2dBegin calls at a time).
- Manipulating textures (clear, get pixel info...) is not possible.
- When some 512*512 rotated, colorized and scaled textures are rendered
  at a time, the framerate *could* go under 60 fps.

### Installation 

- Simply put glib2d.c and glib2d.h in your source directory.
- Then add glib2d.o and link "-lpng -ljpeg -lz -lpspgu -lm -lpspvram"
  in your Makefile.
- You're done !

### License 

This work is licensed under the LGPLv3 License.
See the LICENSE file for more details.
You can support the library by marking your homebrew with
"Using gLib2D by Geecko".

### Contact 

Please report bugs or submit ideas at :
geecko.dev@free.fr

Get the full documentation on :
http://geecko.dev.free.fr

Also stay tuned on...
https://github.com/GeeckoDev (contributors would be a plus!)
http://twitter.com/GeeckoDev
