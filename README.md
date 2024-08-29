#Introduction
##What even is this project?

Well, this is my take on the 6502 CPU. That's it


#Building
##Existing build script
That what I would suggest to use, it just build everything for you.

###available flags:
+ --alternative         - this one is used for building alternative solutions. It is used to get experimental results usually
+ --build               - this one is used for building (by default it only generate cmake stuff)
+ --test                - this one invokes tests
+ --verbose             - this one makes all the events in code beign printed to console
+ --output_dir=<name>   - this one takes argument (name of the folder) and build everything in this folder. By deafult it is set to "build" 

##using cmake directly
You can also use CMake directly and it should work just fine. If you want to use this option you probably know what you are doing
and need no help from me

#Dependencies
+ cmake 3.15+
+ perl  5       (only for build.pl script)
+ c++   20 
+ GTest (no clue, I use newest)

#Usage
Well... Use it however you want I guess, it's just a lib. How I use it is I include it into other project which use it somehow.
Some of more notible examples involve my other projects like ASM_6502 and VisualDebuger_6502(this one is not aired yet)

#Questions?
if so just ask me directly lol
