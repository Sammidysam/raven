#! /usr/bin/env ruby

require "json"
require "twitter"

require_relative "secrets"

# Make sure we have an argument.
if ARGV.length < 1
  puts "Usage: ./twitgrab.rb search-query"
  exit 1
end

# Configure Twitter client.
client = Twitter::REST::Client.new do |config|
  config.consumer_key = CONSUMER_KEY
  config.consumer_secret = CONSUMER_SECRET
  config.access_token = ACCESS_TOKEN
  config.access_token_secret = ACCESS_TOKEN_SECRET
end

tweets = client.search(ARGV[0]).attrs[:statuses]

# If needing to loop over each tweet, do
# tweets.each do |t|
# here

puts JSON.generate(tweets)
