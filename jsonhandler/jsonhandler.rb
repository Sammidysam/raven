#! /usr/bin/env ruby

require "json"

# Loops over a JSON list given as stdin, running the argument provided.
if ARGV.length < 1
	puts "Usage: ./jsonloop.rb name (stdin of JSON to loop over)"
	exit 1
end

input = STDIN.read
json = JSON.parse(input)

json.each do |j|
	name = ARGV[0]
	likes = j["favorite_count"]
	retweets = j["retweet_count"]
	id = j["id"]
	text = j["text"].gsub('"', '\\"')
	date = j["created_at"]

	system("out/analyzer -n \"#{name}\" -l \"#{likes}\" -r \"#{retweets}\" -i \"#{id}\" -t \"#{text}\" -d \"#{date}\" >> #{name}.out")
end
