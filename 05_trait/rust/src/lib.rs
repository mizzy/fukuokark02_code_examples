extern crate libc;

use std::ffi::CStr;
use libc::{c_char, int32_t};

#[derive(Copy, Clone)]
pub struct Specinfra;

#[derive(Copy, Clone)]
pub struct File<'a> {
    name: &'a str,
}

impl Specinfra {
    pub fn new() -> Specinfra {
        Specinfra
    }

    pub fn file(self, name: &str) -> File {
        File { name: name }
    }
}

impl<'a> File<'a> {
    pub fn mode(self) -> i32 {
        // パーミッションを取得して返す処理を入れる
        0o644
    }
}

#[no_mangle]
pub extern "C" fn specinfra_new() -> *const Specinfra {
    let s = Specinfra::new();
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
pub extern "C" fn file_mode(ptr: *const File) -> int32_t {
    let f = unsafe {
        assert!(!ptr.is_null());
        &*ptr
    };

    f.mode()
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
