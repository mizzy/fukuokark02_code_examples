#[repr(C)]
pub struct Point {
    x: i32,
    y: i32,
}

impl Point {
    fn add(self, other: Point) -> Point {
        Point {
            x: self.x + other.x,
            y: self.y + other.y,
        }
    }
}

#[no_mangle]
pub extern "C" fn add_point(p1: Point, p2: Point) -> Point {
    p1.add(p2)
}
