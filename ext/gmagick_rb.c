#include <stdio.h>
#include <ruby.h>
#include <magick/api.h>

static void 
gm_image_destroy(void *src)
{
  Image *img = (Image *)src;
  if (NULL != img)
  {
    DestroyImage(img);
  }
}

static VALUE
Image_alloc(VALUE klass)
{
  volatile VALUE val;
  val = Data_Wrap_Struct(klass, NULL, gm_image_destroy, NULL);
  return val;
}

static VALUE
Image_init(int argc, VALUE *argv, VALUE self)
{
  ExceptionInfo ex;
  Image *img;
  ImageIfno *info;

  GetExceptionInfo(&ex);
  info = CloneImageInfo((ImageInfo *) NULL);
  img = ReadImage(info, &ex);

  DestroyImageInfo(info);
  DestroyExceptionInfo(&ex);
  Check_Type(self, T_DATA);
	DATA_PTR(self) = conn;

  return self;
}



Init_Gmagick(){
  VALUE mGmagick;
  VALUE cImage;
  InitializeMagick(NULL);
  mGmagick = rb_define_module("Gmagick");
  cImage = rb_define_class_under(mGmagick, "Image", rb_cObject);
  rb_define_alloc_func(cImage, Image_alloc);
  rb_define_privete_method(cImage, "initialize", Image_init, 0);
}

