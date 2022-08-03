MEDIA = /media/PANDORA/psp/game/CAT_Homebrews\ perso/
TARGET = gLib2DMod-sample01

OBJS = main.o ../../glib2d.o 
LIBS = -ljpeg -lpng -lz -lpspgum -lpspgu -lpsprtc -lm -lpspvram

CFLAGS = -O2 -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = gLib2DMod - Blend modes

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak 

lclean:
	rm *.o
