File.open("all.cpp").each do |line|
  if /\.cpp/ =~ line
    puts line
  end
end
