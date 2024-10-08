#!/bin/bash
SOURCE_DIR=$1
TARGET_DIR=$2

rsync -avz $SOURCE_DIR $TARGET_DIR
fswatch -o $SOURCE_DIR | while read; do
    rsync -avz $SOURCE_DIR $TARGET_DIR
done
