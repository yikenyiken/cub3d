#!/bin/bash

# Directory containing the files (use '.' for current directory)
DIR="."

# Counter to generate sequential numbers
count=0

# Loop through all .png files in the directory
for file in "$DIR"/*.png; do
  # Check if file exists
  if [ -e "$file" ]; then
    # Rename the file to the new sequential name (1.png, 2.png, ...)
    mv "$file" "$DIR/$count.png"
    # Increment the counter
    count=$((count + 1))
  fi
done

echo "Renaming completed!"
