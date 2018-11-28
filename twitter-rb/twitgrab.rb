#! /usr/bin/env ruby

require "twitter"
require "pry"

require_relative "secrets"

client = Twitter::REST::Client.new do |config|
  config.consumer_key = CONSUMER_KEY
  config.consumer_secret = CONSUMER_SECRET
  config.access_token = ACCESS_TOKEN
  config.access_token_secret = ACCESS_TOKEN_SECRET
end

search = client.search("janet")

binding.pry
