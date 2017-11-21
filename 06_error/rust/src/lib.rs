extern crate libc;

use std::ffi::{CStr, CString};
use std::result::Result;
use libc::{c_char, int32_t};

#[derive(Copy, Clone)]
pub struct Specinfra<'a> {
    backend: &'a Backend,
}

#[derive(Copy, Clone)]
pub struct File<'a> {
    name: &'a str,
    error: &'a str,
}

impl<'a> Specinfra<'a> {
    pub fn new(b: &Backend) -> Specinfra {
        b.detect_platform();
        Specinfra { backend: b }
    }

    pub fn file(self, name: &str) -> File {
        File {
            name: name,
            error: "",
        }
    }
}

impl<'a> File<'a> {
    pub fn mode(self) -> Result<i32, &'a str> {
        // パーミッションを取得して返す処理を入れる
        // Ok(0o644)
        Err("error")
    }
}

pub trait Backend {
    fn detect_platform(&self) -> &str;
}

pub struct Direct;

impl Backend for Direct {
    fn detect_platform(&self) -> &str {
        "Linux"
    }
}

impl Direct {
    pub fn new() -> Direct {
        Direct
    }
}

pub struct BackendWrapper(pub Box<Backend>);

#[no_mangle]
pub extern "C" fn specinfra_new<'a>(ptr: *const BackendWrapper) -> *const Specinfra<'a> {
    let b = unsafe {
        assert!(!ptr.is_null());
        &*ptr
    };
    let s = Specinfra::new(&*b.0);
    Box::into_raw(Box::new(s))
}

#[no_mangle]
pub extern "C" fn specinfra_free(ptr: *mut Specinfra) {
    if ptr.is_null() {
        return;
    }
    unsafe {
        Box::from_raw(ptr);
    }
}

#[no_mangle]
pub extern "C" fn specinfra_file<'a>(ptr: *const Specinfra,
                                     name: *const c_char)
                                     -> *const File<'a> {
    let s = unsafe {
        assert!(!ptr.is_null());
        &*ptr
    };

    let name = unsafe {
        assert!(!name.is_null());
        CStr::from_ptr(name)
    };

    let f = s.file(name.to_str().unwrap());
    Box::into_raw(Box::new(f))
}

#[no_mangle]
pub extern "C" fn file_mode(ptr: *mut File) -> int32_t {
    let f = unsafe {
        assert!(!ptr.is_null());
        &mut *ptr
    };

    match f.mode() {
        Ok(mode) => mode,
        Err(e) => {
            f.error = e;
            -1
        }
    }
}

#[no_mangle]
pub extern "C" fn file_error(ptr: *const File) -> *const c_char {
    let f = unsafe {
        assert!(!ptr.is_null());
        &*ptr
    };

    CString::new(f.error).unwrap().into_raw()
}

#[no_mangle]
pub extern "C" fn file_free(ptr: *mut File) {
    if ptr.is_null() {
        return;
    }
    unsafe {
        Box::from_raw(ptr);
    }
}

#[no_mangle]
pub extern "C" fn direct_new() -> *mut BackendWrapper {
    let d = Direct::new();
    let b = BackendWrapper(Box::new(d));
    Box::into_raw(Box::new(b))
}


#[no_mangle]
pub extern "C" fn direct_free(ptr: *mut Direct) {
    if ptr.is_null() {
        return;
    }
    unsafe {
        Box::from_raw(ptr);
    }
}
