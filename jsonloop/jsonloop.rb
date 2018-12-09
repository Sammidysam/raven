#! /usr/bin/env ruby

require "json"

# Loops over a JSON list given as stdin, running the argument provided.
if ARGV.length < 1
	puts "Usage: ./jsonloop.rb command (stdin of JSON to loop over)"
	exit 1
end

input = ARGF.read
json = JSON.parse(input)

json.each do |j|
	system(ARGV[0])
end
