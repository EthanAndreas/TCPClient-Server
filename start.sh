#!/bin/bash

#Compilation
make
echo ""

#Display
echo "$(tput setaf 4)Program's launching\n===================\n$(tput setaf 7)"

#Program's launching with read and write files

if [ $# -ne 2 ]; then
    echo "usage : ./start.sh server unique"
    echo "                   client       "
    echo "usage : ./start.sh server multi "
    echo "                   client       "
fi
 
if [ $1 = "server" -o $1 = "-s" ]; then
    if [ $2 = "unique" -o $2 = "-u" ]; then
        ./bin/receiver-unique
    elif [ $2 = "multi" -o $2 = "-m" ]; then
        ./bin/receiver-multi
    else
        echo "usage : ./start.sh server unique"
        echo "                   client       "
        echo "usage : ./start.sh server multi "
        echo "                   client       "
    fi
elif [ "$1" = "client" -o $1 = "-c" ]; then
    if [ "$2" = "unique" -o $2 = "-u" ]; then
        ./bin/sender-unique
    elif [ "$2" == "multi" -o $2 = "-m" ]; then
        ./bin/sender-multi
    else
        echo "usage : ./start.sh server unique"
        echo "                   client       "
        echo "usage : ./start.sh server multi "
        echo "                   client       "
    fi
else
    echo "usage : ./start.sh server unique"
    echo "                   client       "
    echo "usage : ./start.sh server multi "
    echo "                   client       "
fi

#Display
echo "$(tput setaf 4)\n===================\n  End of programm  \n$(tput setaf 7)"