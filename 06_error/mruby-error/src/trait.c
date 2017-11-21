#include "mruby.h"
#include "mruby/data.h"
#include "mruby/string.h"

typedef int specinfra;
typedef int file;
typedef int backend;

extern specinfra *specinfra_new(backend *);
extern file *specinfra_file(specinfra *, char *);
extern void specinfra_free(specinfra *);

extern backend *direct_new(void);

extern int file_mode(file *);
extern void file_free(file *);

static void mrb_specinfra_free(mrb_state *mrb, void *ptr);
static void mrb_file_free(mrb_state *mrb, void *ptr);

struct mrb_data_type mrb_specinfra_type = { "Specinfra", mrb_specinfra_free };

struct mrb_data_type mrb_file_type = { "File", mrb_file_free };

struct mrb_data_type mrb_backend_type = { "Direct", mrb_free };

mrb_value direct_new_(mrb_state *mrb, mrb_value self)
{
    backend *b;
    b = direct_new();
    DATA_TYPE(self) = &mrb_backend_type;
    DATA_PTR(self) = b;
    return self;
}

mrb_value new(mrb_state *mrb, mrb_value self)
{
    mrb_value b;
    specinfra *s;

    mrb_get_args(mrb, "o", &b);
    s = specinfra_new(DATA_PTR(b));
    DATA_TYPE(self) = &mrb_specinfra_type;
    DATA_PTR(self) = s;
    return self;
}

mrb_value get_file(mrb_state *mrb, mrb_value self)
{
    mrb_value v;
    char *name;
    file *f;
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
    file *f;
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

void mrb_mruby_error_gem_init(mrb_state *mrb)
{   
    struct RClass *s;
    struct RClass *f;
    struct RClass *d;

    s = mrb_define_class(mrb, "Specinfra", mrb->object_class);
    mrb_define_method(mrb, s, "initialize", new, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, s, "file", get_file, MRB_ARGS_REQ(1));

    f = mrb_define_class(mrb, "File", mrb->object_class);
    mrb_define_method(mrb, f, "mode", mode, MRB_ARGS_NONE());

    d = mrb_define_class(mrb, "Direct", mrb->object_class);
    mrb_define_method(mrb, d, "initialize", direct_new_, MRB_ARGS_NONE());
}

void mrb_mruby_error_gem_final(mrb_state *mrb)
{
}
