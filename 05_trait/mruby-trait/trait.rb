s = Specinfra.new
f = s.file("/etc/passwd")
printf("%#o\n", f.mode)

