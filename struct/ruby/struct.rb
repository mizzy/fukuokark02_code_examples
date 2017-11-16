#!/usr/bin/env ruby

require 'ffi'

class Point < FFI::Struct
  layout :x, :int,
         :y, :int

  def self.create(x, y)
    p = Point.new
    p[:x] = x
    p[:y] = y
    p
  end

  def add(other)
    add_point(self, other)
  end

  extend FFI::Library
  ffi_lib 'struct'
  attach_function :add_point, [Point.by_value, Point.by_value], Point.by_value
end

p1 = Point.create(1, 2)
p2 = Point.create(3, 4)
p = p1.add(p2)
puts p[:x]
