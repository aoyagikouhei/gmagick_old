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
  ImageInfo *info;

  GetExceptionInfo(&ex);
  info = CloneImageInfo((ImageInfo *) NULL);
  //printf("argc=%d", argc);
  //printf("filename = %s", RSTRING_PTR(argv[0]));
  (void) strcpy(info->filename, RSTRING_PTR(argv[0]));
  img = ReadImage(info, &ex);
  //printf(" %lu frames\n", GetImageListLength(img));
  if (ex.severity != UndefinedException)
    CatchException(&ex);
  //printf("%d,%d", img->columns, img->rows);

  DestroyImageInfo(info);
  DestroyExceptionInfo(&ex);
  Check_Type(self, T_DATA);
	DATA_PTR(self) = img;

  return self;
}

static VALUE
Image_width(VALUE self)
{
  Image *img;
  Data_Get_Struct(self, Image, img);
  return INT2NUM(img->columns);
}

static VALUE
Image_height(VALUE self)
{
  Image *img;
  Data_Get_Struct(self, Image, img);
  return INT2NUM(img->rows);
}

static VALUE
Image_format(VALUE self)
{
  Image *img;
  Data_Get_Struct(self, Image, img);
  return rb_str_new2(img->magick);
}

static VALUE
Image_blog(VALUE self)
{
  Image *img;
  Data_Get_Struct(self, Image, img);

}

Init_Gmagick(){
  VALUE mGmagick;
  VALUE cImage;
  InitializeMagick(NULL);
  mGmagick = rb_define_module("Gmagick");
  cImage = rb_define_class_under(mGmagick, "Image", rb_cObject);
  rb_define_alloc_func(cImage, Image_alloc);
  rb_define_private_method(cImage, "initialize", Image_init, -1);
  rb_define_method(cImage, "width", Image_width, 0);
  rb_define_method(cImage, "height", Image_height, 0);
  rb_define_method(cImage, "format", Image_format, 0);
  rb_define_method(cImage, "blob", Image_blob, 0);
}

