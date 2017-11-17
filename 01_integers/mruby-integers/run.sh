#!/bin/bash

# Get mruby source
if [ ! -d ./mruby ]; then
  git clone --depth=1 git://github.com/mruby/mruby.git
fi

# Compile
pushd mruby
MRUBY_CONFIG=../build_config.rb rake all
popd

# Run integers.rb
LD_LIBRARY_PATH=../rust/target/debug ./mruby/bin/mruby integers.rb
