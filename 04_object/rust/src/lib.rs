#[derive(Debug, Copy, Clone)]
pub struct Point {
    x: i32,
    y: i32,
}

impl Point {
    fn new(x: i32, y: i32) -> Self {
        Point { x: x, y: y }
    }

    fn add(&mut self, other: &Point) -> &Self {
        self.x += other.x;
        self.y += other.y;
        self
    }
}

#[no_mangle]
pub extern "C" fn point_new(x: i32, y: i32) -> *const Point {
    let p = Point::new(x, y);
    Box::into_raw(Box::new(p))
}

#[no_mangle]
pub extern "C" fn point_add(ptr1: *mut Point, ptr2: *const Point) -> *mut Point {
    let p1 = unsafe {
        assert!(!ptr1.is_null());
        &mut *ptr1
    };
    let p2 = unsafe {
        assert!(!ptr2.is_null());
        &*ptr2
    };
    p1.add(&p2);
    Box::into_raw(Box::new(*p1))
}

#[no_mangle]
pub extern "C" fn point_free(ptr: *mut Point) {
    if ptr.is_null() {
        return;
    }
    unsafe {
        Box::from_raw(ptr);
    }
}

#[no_mangle]
pub extern "C" fn point_print(ptr: *mut Point) {
    let p = unsafe {
        assert!(!ptr.is_null());
        &*ptr
    };
    println!("{:?}", p);
}
