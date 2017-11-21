b = Direct.new
s = Specinfra.new(b)
f = s.file("/etc/passwd")
printf("%#o\n", f.mode)
