# C.L.A.R.B.E.
###### Or: C Language Assistant for Running and Building Ecosystems.

### Community: https://discord.gg/Twhv4KU3qf

Is a cargo-like package manager and compiler for the C programming language.
I were tired of reading incredible C/C++ committee proposal papers which were not accepted in the language, so I created this manager for the lovers of C to try adding things they'd love to see in the language.

## Overview

the project's compromised of two parts, the compiler and file manager.

## Information

Of course this compiler doesn't follow the full C standard, since it's made by a single dev ;-;

## Dependencies
 - curl
 - toml++
 - rapidjson

## Installation
Create a environment variable 'CLARBE_HOME' and add 'CLARBE_HOME/bin' to path.
Download the zipped source code, unzip and in the directory run in git bash terminal ```bash build.sh```.
This will create a dir 'build' with three inside:
 - from 'build/compiler' drag 'compiler.exe' to 'CLARBE_HOME/bin'
 - from 'build/release/Release' drag 'clarbe.exe' to 'CLARBE_HOME/bin'
now run in terminal ```clarbe -v```