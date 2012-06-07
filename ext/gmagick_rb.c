#include <stdio.h>
#include <ruby.h>
#include <magick/api.h>

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
  rb_define_method(cImage, "initialize", init, 0);
}

