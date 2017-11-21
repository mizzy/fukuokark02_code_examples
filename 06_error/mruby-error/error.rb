b = Direct.new
s = Specinfra.new(b)
f = s.file("/etc/passwd")
begin
  printf("%#o\n", f.mode)
rescue => e
  puts e.message
end
