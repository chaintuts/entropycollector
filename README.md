## General
____________

### Author
* Josh McIntyre

### Website
* jmcintyre.net

### Overview
* EntropyCollector is an educational accelerometer-based password generation tool

## Development
________________

### Git Workflow
* master for releases (merge development)
* development for bugfixes and new features

### Building
* make build
Build the application
* make clean
Clean the build directory

### Features
* Collect entropy via an accelerometer to an SD card
* Use the collected entropy to generate pseudorandom passwords

### Requirements
* Requires Python 3.7
* Requires an arduino development environment
* Requires an Adafruit Feather M0 Adalogger with Lis3DH accelerometer
* Requires a FAT-formatted SD card

### Platforms
* Windows
* Linux
* MacOSX

## Usage
____________

### Command line usage
* Run the accelerometer entropy collector hardware - the more run-time and movement the better!
* Copy the entropy file to a PC and run `passwordgen.py`