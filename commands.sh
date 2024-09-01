#!/bin/bash

# I have prepared some g++ commands for you in case you don't get CMake to work.
alias a1='g++ -std=c++20 -I./include -static -o bin/Assignment1 Assignment1/*.cpp'
alias a2='g++ -std=c++20 -I./include -static -o bin/Assignment2 Assignment2/*.cpp'
alias a3='g++ -std=c++20 -I./include -static -o bin/Assignment3 Assignment3/*.cpp'
alias a4='g++ -std=c++20 -I./include -static -o bin/Assignment4 Assignment4/*.cpp'
alias build='a1; a2; a3; a4'

# You can ignore this, it's just a convenience for me.
function push() {
	if [ -z "$1" ]; then
		echo "Error: Commit message is required"
		return
	fi
	git add .
	git commit -m "$1"
	git push origin main
}