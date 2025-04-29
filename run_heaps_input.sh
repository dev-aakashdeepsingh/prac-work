#!/bin/bash

# Prompt user for inputs
read -p "Enter value for -m: " m_value
read -p "Enter value for -d: " d_value
read -p "Enter value for -exp: " exp_value

# Fixed values
i_value=50
e_value=50

# Temporary individual log files
log1="log1_tmp.txt"
log2="log2_tmp.txt"
log3="log3_tmp.txt"

# Clear old temporary logs if they exist
> "$log1"
> "$log2"
> "$log3"

# Commands to run
cmd1="./prac -o -t 8 0 heap -m $m_value -d $d_value -i $i_value -e $e_value -opt 0 -s 1 -exp $exp_value"
cmd2="./prac -o -t 8 1 localhost heap -m $m_value -d $d_value -i $i_value -e $e_value -opt 0 -s 1 -exp $exp_value"
cmd3="./prac -o -t 8 2 localhost localhost heap -m $m_value -d $d_value -i $i_value -e $e_value -opt 0 -s 1 -exp $exp_value"

# Run each in background and wait later
gnome-terminal -- bash -c "echo 'Running Node 0'; $cmd1 | tee $log1; exec bash" &
sleep 2
gnome-terminal -- bash -c "echo 'Running Node 1'; $cmd2 | tee $log2; exec bash" &
sleep 2
gnome-terminal -- bash -c "echo 'Running Node 2'; $cmd3 | tee $log3; exec bash" &



