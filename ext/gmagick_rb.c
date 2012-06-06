#include <stdio.h>
#include <ruby.h>
#include <magick/api.h>

VALUE test(void);

Init_Gmagick(){
  VALUE module;
  InitializeMagick(NULL);
  module = rb_define_module("Gmagick");
  rb_define_module_function(module, "test", test, 0);
}

VALUE test(void){
  printf("Hello, Ruby World.\n");
  return Qnil;
}
