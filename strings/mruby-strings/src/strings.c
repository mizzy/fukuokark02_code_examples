#include <stdint.h>
#include "mruby.h"
#include "mruby/string.h"

extern char *echo(char *);

static mrb_value echo_(mrb_state *mrb, mrb_value self)
{
    char *arg, *ret;
    mrb_int len;
    mrb_value str;
    mrb_get_args(mrb, "s", &arg, &len);
    ret = echo(arg);
    str = mrb_str_buf_new(mrb, sizeof(ret));
    return mrb_str_cat_cstr(mrb, str, ret);
}

void mrb_mruby_strings_gem_init(mrb_state *mrb)
{   
    struct RClass *s = mrb_define_module(mrb, "Strings");
    mrb_define_class_method(mrb, s, "echo", echo_, MRB_ARGS_REQ(1));
}

void mrb_mruby_strings_gem_final(mrb_state *mrb)
{
}
