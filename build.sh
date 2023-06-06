#!/bin/bash
if [ $1 == "main" ]
then
    g++ -o  ./bin/main main.cpp -std=c++11
    ./bin/main

elif [ $1 == "path" ]
then
    g++ -o  ./bin/out $2 -std=c++11
    ./bin/out
elif [ $1 == "clr" ]
then
    rm ./bin/*
else
    echo "Not file selected !"
fi