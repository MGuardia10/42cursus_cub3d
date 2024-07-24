#!/bin/bash

# Directory with all maps
DIR="maps/invalid"

# Starting map number
NBR=1

# Iterate through every file in directory
for file in "$DIR"/*; do
    # New name
    new_name="map_error_${NBR}.cub"


    # Rename file with new name
    mv "$file" "$DIR/$new_name"

    # increment nbr
    NBR=$((NBR + 1))
done

echo "All files renamed successfully."