#!/usr/bin/env ruby

require 'ffi'

module Libspecinfra
  class Backend
    class Direct < FFI::AutoPointer
      def self.release(ptr)
        Binding.free(ptr)
      end

      module Binding
        extend FFI::Library
        ffi_lib 'trait'
        attach_function :free, :direct_free, [Direct], :void
        attach_function :new, :direct_new, [], Direct
      end
    end
  end

  class File < FFI::AutoPointer
    def self.release(ptr)
      file_free(ptr)
    end

    def mode()
      file_mode(self)
    end

    extend FFI::Library
    ffi_lib 'trait'
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
      ffi_lib 'trait'
      attach_function :new,  :specinfra_new,  [:pointer],  Specinfra
      attach_function :free, :specinfra_free, [Specinfra], :void
      attach_function :file, :specinfra_file, [Specinfra, :string], File
    end
  end
end

b = Libspecinfra::Backend::Direct::Binding.new
s = Libspecinfra::Specinfra::Binding.new(b)
f = s.file("/etc/passwd")
printf("%#o\n", f.mode)
