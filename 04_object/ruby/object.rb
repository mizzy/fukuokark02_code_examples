#!/usr/bin/env ruby

require 'ffi'

module Libspecinfra
  class File < FFI::AutoPointer
    def self.release(ptr)
      file_free(ptr)
    end

    def mode()
      file_mode(self)
    end

    extend FFI::Library
    ffi_lib 'object'
    attach_function :file_free, [File], :void
    attach_function :file_mode, [File], :int
  end

  class Specinfra < FFI::AutoPointer
    def self.release(ptr)
      Binding.free(ptr)
    end

    def file(name)
      Binding.file(self, name)
    end

    module Binding
      extend FFI::Library
      ffi_lib 'object'
      attach_function :new,  :specinfra_new,  [],          Specinfra
      attach_function :free, :specinfra_free, [Specinfra], :void
      attach_function :file, :specinfra_file, [Specinfra, :string], File
    end
  end
end

s = Libspecinfra::Specinfra::Binding.new
f = s.file("/etc/passwd")
printf("%#o\n", f.mode)
