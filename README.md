# NES Emulator Study
- Learning a bit of how the 6502 Chip works by implementing a NES emulator.
Thanks OneLoneCoder for the lecture.

# How to run it (Linux only):
Clone the repository and cd into it.
```
$ git clone git@github.com:martuscellifaria/NESEmulator.git
$ cd NESEmulator
```

Create a build folder and cd into it:
```
$ mkdir build && cd build
```

Make sure you have CMake installed and execute the following:
```
$ cmake -DCMAKE_BUILD_TYPE=Release ..
```

After a few seconds, you will get a pretty Makefile and the project will be ready to compile with make:
```
$ make
```

Now it is done and you can execute it:
```
$ ./NESBound
```

The emulator is just a project for strict learning purposes, and shall not be comercialized.
If you're a retro gaming enthusiast and into some advanced C++, make yourself at home.

## Credits to David aka. Javidx9 (or OneLoneCoder) and his license follows:

License (OLC-3)
Copyright 2018, 2019, 2020, 2021 OneLoneCoder.com

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions or derivations of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

Redistributions or derivative works in binary form must reproduce the above copyright notice. This list of conditions and the following disclaimer must be reproduced in the documentation and/or other materials provided with the distribution.

Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.