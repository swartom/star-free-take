##
# Star-free Take
#
# @file
# @version 0.1

run:
	gcc -Ofast star_free.c -o star_free
	./star_free 1 0.5

PHONY: run

# end
