#include <stdio.h>
#include <ruby.h>
#include <magick/api.h>

void 
gm_image_destroy(void *src)
{
  Image *img = (Image *)src;
  if (NULL != img)
  {
    DestroyImage(img);
  }
}

VALUE
Image_alloc(VALUE klass)
{
  volatile VALUE val;
  val = Data_Wrap_Struct(klass, NULL, gm_image_destroy, NULL);
  return val;
}

VALUE test(void){
  printf("Hello, Ruby World.\n");
  return Qnil;
}

VALUE init(VALUE self) {

  return self;
}

Init_Gmagick(){
  VALUE mGmagick;
  VALUE cImage;
  InitializeMagick(NULL);
  mGmagick = rb_define_module("Gmagick");
  cImage = rb_define_class_under(mGmagick, "Image", rb_cObject);
  rb_define_module_function(mGmagick, "test", test, 0);
  rb_define_alloc_func(cImage, Image_alloc);
  rb_define_method(cImage, "initialize", init, 0);
}

