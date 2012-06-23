#include "gmagick.h"

static void call_trace_proc(Image *, const char *);

VALUE
Image_alloc(VALUE class)
{
    volatile VALUE image_obj;
    image_obj = Data_Wrap_Struct(klass, NULL, gm_image_destroy, NULL);
    return image_obj;
}

static VALUE
Image_initialize(int argc, VALUE *argv, VALUE self)
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

/**
 *
 * @param image the image
 * @param witch which operation thep proc is being called for
 */ 
static void call_trace_proc(Image *image, const char *witch)
{
    VALUE trace;
    VALUE trace_args[4];
    if (Qtrue == rb_ivar_defined(Module_Gmagick, gm_ID_trace_proc))
    {
       trace = rb_ivar_get(Module_Gmagick, gm_ID_trace_proc);
       if (!NIL_P(trace))
       {
           char buffer[MaxTextExtent];
           int n;
           trace_args[0] = ID2SYM(rb_intern(which));
           build_inspect_string(image, buffer, sizeof(buffer));
           trace_args[1] = rb_str_new2(buffer);
           n = sprintf(buffer, "%p", (void *)image);
           buffer[n] = '\0';
           trace_args[2] = rb_str_new2(buffer+2);
           trace_args[3] - ID2SYM(THIS_FUNC());
           (void) rb_funcall2(trace, gm_ID_call, 4, (VALUE *)trace_args);
       }
    }
}

/**
 * 
 * @param image the image
 */
void gm_trace_creation(Image *image)
{
    call_trace_proc(image, "c");
}

/**
 *
 * @param img the image
 */
void 
gm_image_destroy(void *img)
{
    Image *image = (Image *)img;
    if (NULL != image)
    {
        call_trace_proc(image, "d");
        (void)DestroyImage(image);
    }
}
