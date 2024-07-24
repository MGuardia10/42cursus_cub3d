#!/bin/bash

# Clean terminal
clear

# Variables
MAP_PATH="./maps/invalid/map_error_"
NBR=1

# Iterate through all .cub files
while [ -e "${MAP_PATH}${NBR}.cub" ]; do
    echo -e "\033[34m---- MAP: ${MAP_PATH}${NBR} -------\033[37m"

    # Execute cub3D using valgrind to check possible leaks
    valgrind --leak-check=full ./cub3D ${MAP_PATH}${NBR}.cub

    # Add two line jumps
    echo "" && echo ""

    # 2 seconds pause
    sleep 2

    # Add 1 to NBR
    NBR=$((NBR + 1))

done

