#include <stdint.h>
#include "mruby.h"

extern uint32_t addition(uint32_t, uint32_t);

static mrb_value addition_(mrb_state *mrb, mrb_value self)
{
    mrb_int a, b;
    mrb_get_args(mrb, "ii", &a, &b);
    return mrb_fixnum_value(addition(a, b));
}

void mrb_mruby_integers_gem_init(mrb_state *mrb)
{   
    struct RClass *i = mrb_define_module(mrb, "Integers");
    mrb_define_class_method(mrb, i, "addition", addition_, MRB_ARGS_REQ(2));
}

void mrb_mruby_integers_gem_final(mrb_state *mrb)
{
}
