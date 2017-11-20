#include "mruby.h"
#include "mruby/data.h"
#include "mruby/string.h"

typedef int specinfra;
typedef int file_resource;

extern specinfra *specinfra_new(void);
extern file_resource *specinfra_file(specinfra *, char *);
extern void specinfra_free(specinfra *);


extern int file_mode(file_resource *);
extern void file_free(file_resource *);

static void mrb_specinfra_free(mrb_state *mrb, void *ptr);
static void mrb_file_free(mrb_state *mrb, void *ptr);

struct mrb_data_type mrb_specinfra_type = { "Specinfra", mrb_specinfra_free };

struct mrb_data_type mrb_file_type = { "File", mrb_file_free };

mrb_value new(mrb_state *mrb, mrb_value self)
{
    specinfra *s;
    s = specinfra_new();
    DATA_TYPE(self) = &mrb_specinfra_type;
    DATA_PTR(self) = s;
    return self;
}

mrb_value file(mrb_state *mrb, mrb_value self)
{
    mrb_value v;
    char *name;
    file_resource *f;
    struct RClass *file_class;
    mrb_value file_object;

    mrb_get_args(mrb, "S", &v);
    name = mrb_str_to_cstr(mrb, v);

    file_class = mrb_class_get(mrb, "File");
    file_object = mrb_obj_new(mrb, file_class, 0, NULL);
    f = specinfra_file(DATA_PTR(self), name);

    DATA_TYPE(file_object) = &mrb_file_type;
    DATA_PTR(file_object) = f;
    return file_object;
}

mrb_value mode(mrb_state *mrb, mrb_value self)
{
    file_resource *f;
    int m;

    f = DATA_PTR(self);
    m = file_mode(f);
    return mrb_fixnum_value(m);
}

static void mrb_specinfra_free(mrb_state *mrb, void *ptr)
{
    specinfra_free(ptr);
}

static void mrb_file_free(mrb_state *mrb, void *ptr)
{
    file_free(ptr);
}

void mrb_mruby_object_gem_init(mrb_state *mrb)
{   
    struct RClass *s;
    struct RClass *f;

    s = mrb_define_class(mrb, "Specinfra", mrb->object_class);
    mrb_define_method(mrb, s, "initialize", new, MRB_ARGS_NONE());
    mrb_define_method(mrb, s, "file", file, MRB_ARGS_REQ(1));

    f = mrb_define_class(mrb, "File", mrb->object_class);
    mrb_define_method(mrb, f, "mode", mode, MRB_ARGS_NONE());
}

void mrb_mruby_object_gem_final(mrb_state *mrb)
{
}
