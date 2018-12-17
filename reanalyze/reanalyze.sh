#! /bin/bash
# This is effectively a fork of linking.sh.
# Here, we need to move the old analysis to a new spot,
# edit the exported database to a format that can be read
# by jsonhandler,
# then feed it into jsonhandler to analyze it all.

while read p
do
	name="$p"
	underscored="${p// /_}"
	file="$underscored.json"
	analysis="$name.out"
	backup="$name$RANDOM.out"
	db="tweets_${underscored}.json"

	# Create our backup.
	# There is a 1/32767 chance this will override a previous
	# backup. This should be 0, and fixed later
	# (probably backup using the date as a title).
	echo "Backing up $analysis to backup/$backup..."
	mv "$analysis" "backup/$backup"

	# Now run the analysis on the database, similar
	# to the main linking paragraph.
	jsonhandler/jsonhandler.rb "$name" < "$db"
done < analyses.txt
