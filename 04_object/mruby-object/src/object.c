#include <stdint.h>
#include "mruby.h"
#include "mruby/data.h"

typedef struct point_S point_t;
extern point_t *point_new(int, int);
extern point_t *point_add(point_t *, point_t *);
extern point_t *point_print(point_t *);

const static struct mrb_data_type mrb_point_type = { "Point", mrb_free };

static mrb_value point_new_(mrb_state *mrb, mrb_value self)
{
    mrb_int x, y;
    point_t *p;

    mrb_get_args(mrb, "ii", &x, &y);
    p = point_new(x, y);

    DATA_TYPE(self) = &mrb_point_type;
    DATA_PTR(self) = p;
    return self;
}

static mrb_value point_add_(mrb_state *mrb, mrb_value self)
{
    point_t *p1, *p2;
    mrb_value other;

    mrb_get_args(mrb, "o", &other);
    p1 = DATA_PTR(self);
    p2 = DATA_PTR(other);

    point_add(p1, p2);

    return self;
}

static mrb_value point_print_(mrb_state *mrb, mrb_value self)
{
    point_t *p;
    p = DATA_PTR(self);
    point_print(p);
    return self;
}

void mrb_mruby_object_gem_init(mrb_state *mrb)
{   
    struct RClass *p = mrb_define_class(mrb, "Point", mrb->object_class);
    mrb_define_method(mrb, p, "initialize", point_new_, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, p, "add", point_add_, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, p, "print", point_print_, MRB_ARGS_NONE());
}

void mrb_mruby_object_gem_final(mrb_state *mrb)
{
}
