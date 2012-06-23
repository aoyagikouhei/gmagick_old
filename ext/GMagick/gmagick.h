#ifndef _GMAGICK_H_
#define _GMAGICK_H_

#include <stdio.h>
#include <ruby.h>
#include <magick/api.h>

EXTERN VALUE Module_Gmagick;
EXTERN VALUE Class_Image;

EXTERN ID gm_ID_trace_proc;
EXTERN ID gm_ID_call;

extern VALUE Image_allocc(VALUE);
extern VALUE Image_initialize(int, VALUE*, VALUE);

extern void gm_image_destroy(void *);
extern void gm_trace_creation(Image *);

#endif
