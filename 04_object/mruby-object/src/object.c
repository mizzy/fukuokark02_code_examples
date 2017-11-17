#include <stdint.h>
#include "mruby.h"
#include "mruby/data.h"

typedef int point;

extern point *point_new(int, int);
extern point *point_add(point *, point *);
extern point *point_print(point *);

struct mrb_data_type mrb_point_type = { "Point", mrb_free };

mrb_value new(mrb_state *mrb, mrb_value self)
{
    mrb_int x, y;
    point *p;

    mrb_get_args(mrb, "ii", &x, &y);
    p = point_new(x, y);

    DATA_TYPE(self) = &mrb_point_type;
    DATA_PTR(self) = p;
    return self;
}

mrb_value add(mrb_state *mrb, mrb_value self)
{
    point *p1, *p2;
    mrb_value other;

    mrb_get_args(mrb, "o", &other);
    p1 = DATA_PTR(self);
    p2 = DATA_PTR(other);

    point_add(p1, p2);

    return self;
}

mrb_value point_print_(mrb_state *mrb, mrb_value self)
{
    point *p;
    p = DATA_PTR(self);
    point_print(p);
    return self;
}

void mrb_mruby_object_gem_init(mrb_state *mrb)
{   
    struct RClass *p =
        mrb_define_class(mrb, "Point", mrb->object_class);
    mrb_define_method(mrb, p, "initialize", new, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, p, "add", add, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, p, "print", point_print_, MRB_ARGS_NONE());
}

void mrb_mruby_object_gem_final(mrb_state *mrb)
{
}
