# This file contains a simple make script for the EntropyCollector application
#
# Author: Josh McIntyre
#

# This block defines makefile variables
SRC_FILES=src/python/*.py src/arduino/*.ino
RES_FILE=res/ENTROPY.TXT.sample
RES_FILE_DST=bin/entropycollector/ENTROPY.TXT

BUILD_DIR=bin/entropycollector

# This rule builds the application
# This copies the password generator Python file and sample ENTROPY.TXT to the bin dir
# You'll need an Arduino dev environment to fully build the entropy collector .ino file for your own hardware
# See Adafruit tutorials for your board and accelerometer
build: $(SRC_FILES)
	mkdir -p $(BUILD_DIR)
	cp $(SRC_FILES) $(BUILD_DIR)
	cp $(RES_FILE) $(RES_FILE_DST)

# This rule cleans the build directory
clean: $(BUILD_DIR)
	rm $(BUILD_DIR)/*
	rmdir $(BUILD_DIR)
