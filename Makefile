# Project: Arbitrary Precision Calculator (APC)
PROJECT_NAME = ArbitraryPrecisionCalculator

SHELL := /bin/sh
SOURCES= main.c $(wildcard sources/*.c)
HEADERS= -I./headers
OBJECTS:=$(addprefix make-build/objects/,$(notdir $(SOURCES:%.c=%.o)))
COMPILER = gcc
FLAGS = -Wall -g -lm $(HEADERS)

all: files-discovered create-directory $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJECTS)
	$(COMPILER) $(OBJECTS) -o make-build/$(PROJECT_NAME)

make-build/objects/%.o: sources/%.c
	$(COMPILER) $(FLAGS) -c $< -o $@

make-build/objects/%.o: %.c
	$(COMPILER) $(FLAGS) -c $< -o $@

files-discovered:
	@echo "Headers to be compiled : "
	@for file in $(HEADERS); do echo "	$$file"; done
	@echo "Sources to be compiled : "
	@for file in $(SOURCES); do echo "	$$file"; done
	@echo "Objects to be generated : "
	@for file in $(OBJECTS); do echo "	$$file"; done

create-directory:
	@echo "Creating output folders in $(CURDIR)"
	mkdir -p make-build
	mkdir -p make-build/objects

clean:
	rm -rf make-build