#include "gmagick.h"

void
Init_GMagick(void)
{
  gm_ID_trace_proc = rb_intern("@trace_proc");
  gm_ID_ID_call = rb_intern("call");

  Module_Gmagick = rb_define_module("Gmagick");
  Class_Image = rb_define_class_under(Module_GMagick, "Image", rb_cObject);
  
  rb_define_alloc_func(Class_Image, Image_alloc);
  rb_define_privete_method(Class_Image, "initialize", Image_Initialize, -1);

}

