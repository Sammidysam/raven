#!/bin/sh

mongoimport --db raven --collection tweets <<< "$1"
