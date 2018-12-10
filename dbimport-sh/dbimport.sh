#!/bin/sh

mongoimport --db raven --collection tweets --file "$1" --jsonArray
