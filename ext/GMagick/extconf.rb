require "mkmf"

if gmconfig = ( with_config('gm-config') || with_config('gm_config') || find_executable('GraphicsMagick-config') )
  $stderr.puts "Using config values from %s" % [ gmconfig ]
  $CPPFLAGS << " " + `"#{gmconfig}" --cppflags`.chomp
  $LDFLAGS << " " + `"#{gmconfig}" --ldflags`.chomp
  $LOCAL_LIBS << " " + `"#{gmconfig}" --libs`.chomp
else
  $stderr.puts "No GraphicsMagick-config... trying anyway. If building fails, please try again with",
		" --with-gm-config=/path/to/GraphicsMagick-config"
end

create_makefile("Gmagick")

