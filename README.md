#Bold

###Phase 1

IF IT'S MISSING A LIBRARY, THEN RE-COMPILE. If there's error in making, your computer in not a linux 14.04 or 16.04. Get those.

Here's some important bits. To compile cmake in clang++, do "sudo update-alternatives --config c++"

and select clang++.

ALSO REMEMBER TO COMPILE ON LINUX AND WINDOWS. WE NEED TO ALWAYS VERIFY THAT IT IS CROSS-PLATFORM FOR OUR CROSS-PLATFORMING NEEDS.

Because I still haven't done that.

-----------------------------------------------------------------------

To compile: Learn how to use Cmake.

Lazy instructions: "sudo apt-get install cmake"

Install, then: "cmake ."

then you make your makefile.

then, "make". You now compiled.

---------------------------------------------------------------------

Game Instructions:

Arrow keys to move up left down right.

Press m to toggle big map mode. Like a big zoom.

Press q to toggle checkAll mode. See viewline func for details

Press s to toggle seeAboveInvisible mode. Distinguishes what you can't see.

Press e to toggle map debug.

Press f to toggle fly mode.

Press z to toggle memory mode. So you can see what you saw.

+  and - modifies view distance.

[  and ] modifies playerHeight (an offset for accuracy)

,  and . modifies playerZ (you're actual height.) Workable only with fly mode. Allows you to fly.

Remember to have the "MAP MOVE" window selected when doing this, and to press X on the window when done.

To run, "./build/maptest"



