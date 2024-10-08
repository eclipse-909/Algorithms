#!/bin/bash

alias build_a1='g++ -std=c++20 -I./include -static -o bin/Assignment1 Assignment1/*.cpp'
alias build_a2='g++ -std=c++20 -I./include -static -o bin/Assignment2 Assignment2/*.cpp'
alias build_a3='g++ -std=c++20 -I./include -static -o bin/Assignment3 Assignment3/*.cpp'
alias build_a4='g++ -std=c++20 -I./include -static -o bin/Assignment4 Assignment4/*.cpp'
alias build_test='g++ -std=c++20 -I./include -static -o bin/Tests Tests/*.cpp'

# Use this command to build the binaries.
# 'build' will build all assignments.
# Use --a1 --a2 --a3 --a4 to build specific assignments.
# Use -t to also build the test program, but you don't need this one.
build() {
  mkdir -p bin
  a1=false
  a2=false
  a3=false
  a4=false
  run_tests=false
  while [ $# -gt 0 ]; do
    case "$1" in
      --a1)
        a1=true
        ;;
      --a2)
        a2=true
        ;;
      --a3)
        a3=true
        ;;
      --a4)
        a4=true
        ;;
      -t)
        run_tests=true
        ;;
      *)
        echo "Invalid option: $1" >&2
        return 1
        ;;
    esac
    shift
  done
  echo "Building project..."
  if [ "$a1" = false ] && [ "$a2" = false ] && [ "$a3" = false ] && [ "$a4" = false ] && [ "$run_tests" = false ]; then
    build_a1 && build_a2 && build_a3 && build_a4 && echo "Build complete!"
    return
  fi
  if [ "$a1" = true ]; then
    build_a1 || return
  fi
  if [ "$a2" = true ]; then
    build_a2 || return
  fi
  if [ "$a3" = true ]; then
    build_a3 || return
  fi
  if [ "$a4" = true ]; then
    build_a4 || return
  fi
  if [ "$run_tests" = true ]; then
    build_test || return
  fi
  echo "Build complete!"
}

# You can ignore this, it's just a convenience for me.
push() {
	if [ -z "$1" ]; then
		echo "Error: Commit message is required"
		return
	fi
	git add .
	git commit -m "$1"
	git push origin main
}