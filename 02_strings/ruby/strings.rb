#!/usr/bin/env ruby

require 'ffi'

module Strings
  extend FFI::Library
  ffi_lib 'strings'
  attach_function :echo, [:string], :string
end

puts Strings.echo("Hello")
