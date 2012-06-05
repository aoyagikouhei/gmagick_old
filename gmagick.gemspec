# -*- encoding: utf-8 -*-
require File.expand_path('../lib/gmagick/version', __FILE__)

Gem::Specification.new do |gem|
  gem.authors       = ["aoyagikouhei"]
  gem.description   = "GraphicsMagick"
  gem.summary       = "GraphicsMagick"
  gem.homepage      = ""

  gem.files         = `git ls-files`.split($\)
  gem.executables   = gem.files.grep(%r{^bin/}).map{ |f| File.basename(f) }
  gem.test_files    = gem.files.grep(%r{^(test|spec|features)/})
  gem.name          = "gmagick"
  gem.require_paths = ["lib"]
  gem.version       = Gmagick::VERSION
end
