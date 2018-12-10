#! /bin/bash

while read p
do
	name="$p"
	file="$p.json"

	twitter-rb/twitgrab.rb $name > $file
	dbimport-sh/dbimport.sh $file
	jsonhandler/jsonhandler.rb $name < $file
	rm $file
done < analyses.txt
