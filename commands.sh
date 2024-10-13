#!/bin/bash

push() {
	if [ -z "$1" ]; then
		echo "Error: Commit message is required"
		return
	fi
	git add .
	git commit -m "$1"
	git push origin main
}

alias debug="gdb ./Assignment2.exe --command=debug.txt"