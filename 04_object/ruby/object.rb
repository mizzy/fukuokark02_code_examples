#!/usr/bin/env ruby

require 'ffi'

class Point < FFI::AutoPointer
  def self.release(ptr)
    Binding.free(ptr)
  end

  def add(other)
    Binding.add(self, other)
    self
  end

  def print
    Binding.print(self)
  end

  module Binding
    extend FFI::Library
    ffi_lib 'object'
    attach_function :new,  :point_new,  [:int, :int],   Point
    attach_function :add,  :point_add,  [Point, Point], Point
    attach_function :free, :point_free, [Point],        :void
    attach_function :print, :point_print, [Point], :void
    def initialize(x, y)
      point_new(x, y)
    end
  end
end

p1 = Point::Binding.new(1, 2)
p2 = Point::Binding.new(3, 4)
p1.add(p2).add(p2)
p1.print

