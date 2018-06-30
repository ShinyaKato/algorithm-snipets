files = []

Dir.glob("**/*").each do |file|
  if /\.cpp\Z/ =~ file
    s = ""
    s += "/**" + ("*" * file.length) + "**/\n"
    s += "/* #{file} */\n"
    s += "/**" + ("*" * file.length) + "**/\n"
    s += "\n"
    s += File.open(file).read
    files << s
  end
end

puts files.join("\n")
