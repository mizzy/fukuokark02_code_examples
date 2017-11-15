#!/bin/sh

rustc --crate-type cdylib hello.rs
cc hello.c -L. -lhello
LD_LIBRARY_PATH=. ./a.out

