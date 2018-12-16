#!/bin/bash
mongoimport --db raven --collection tweets_${1%.*} --file "$1" --jsonArray
