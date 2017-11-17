#!/usr/bin/env ruby

require 'ffi'

module Strings
  extend FFI::Library
  ffi_lib 'strings'
  attach_function :emphasize, [:string], :string
end

puts Strings.emphasize("Hello")
