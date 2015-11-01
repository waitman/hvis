
1) Introduction 

This program is intended as a means for quick field review of camera 
images. It was developed using Qt5. May work with Qt4 but not 
tested.

hvis displays JPEG images located in the current directory, 
allows the user to rotate 90 degrees left or right, save the image 
as a "select" in a directory "save" located in the current directory, 
and allows touchscreen navigation. When the selected image is "saved", 
a thumbnail is generated in the "save/th" directory created in the 
current directory.

The "save" and "rotate" functions depend on the user having the 
ImageMagick software installed.


2) Environment Variables

CONVERT 		default "/usr/bin/convert"
THUMBSIZE		default "1000x1000"
THUMBQUALITY 		default "90"
THUMBDENSITY		default "120"

example: specify alternate location for ImageMagick "convert"

# setenv CONVERT /usr/local/bin/convert
# export CONVERT=/usr/local/bin/convert


3) Key Commands

X		quit the program
Q		quit the program
SPACE	advance to the next frame
B		retract to the previous frame
+		advance 10 frames
-		retract 10 frames
S		save the frame as a select image and generate thumbnail
R		rotate 90 degrees clockwise
L		rotate 90 degrees counter-clockwise

User may also "swipe right" or "swipe left" on a touchscreen.


4) Building the program

GNU/Linux

# qmake
# make
# cp hvis /usr/bin

FreeBSD

# /usr/local/lib/qt5/bin/qmake
# make
# cp hvis /usr/local/bin


5) Running the program

# cd /path/to/images
# hvis

The program will launch full screen by default. 
To launch the program in "normal screen view", ie not fullscreen, use 
the command line parameter "S"

# hvis S


6) Caveats

1. Pinch / zoom gesture not currently implemented, perhaps in the future.

2. There are presently no plans to implement a grid view.

3. Raw file support is not implemented, could be modified but probably 
quicker to use dcraw, dcraw-m or multiraw to batch convert on 
command line.

4. The program strips meta information from the generated thumbnail.


7) License

Disposera GUI
 hvis - image viewer with touchscreen swipe
 
Copyright 2015 Waitman Gobble <ns@waitman.net>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
