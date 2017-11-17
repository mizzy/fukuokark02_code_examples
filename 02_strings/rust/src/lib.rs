extern crate libc;

use libc::*;
use std::ffi::{CStr, CString};

#[no_mangle]
pub extern "C" fn emphasize(ptr: *const c_char) -> *const c_char {
    let s = unsafe {
            assert!(!ptr.is_null());
            CStr::from_ptr(ptr)
        }
        .to_str()
        .unwrap();
    let str = s.to_owned() + "!!!";
    CString::new(str).unwrap().into_raw()
}
