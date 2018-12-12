#!/bin/bash

DB=$1
COLLECTIONS=$(mongo localhost:27017/$DB --quiet --eval "db.getCollectionNames()" | sed 's/,/ /g')

for collection in $COLLECTIONS; do
    echo "Exporting $DB/$collection ..."
    mongoexport -d $DB -c $collection -o $collection.json
done
