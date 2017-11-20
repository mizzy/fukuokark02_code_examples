MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gembox 'default'
  conf.gem File.expand_path(File.dirname(__FILE__))
  conf.linker do |linker|
    linker.libraries = %w(trait m)
    linker.library_paths = %w(../../rust/target/debug)
  end
end
