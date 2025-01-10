# C.L.A.R.B.E.
###### Or: C Language Assistant for Running and Building Ecosystems.

### Community: https://discord.gg/Twhv4KU3qf

Is a compiler / cargo-like package and project manager for the C programming language.
I were tired of reading incredible C/C++ committee proposal papers which were not accepted in the language, so I created this manager for the lovers of C to try adding things they'd love to see in the language.

## Overview

the project's compromised of two parts, the compiler and project manager.
hence the compiler is not yet functional, the project manager will be a wrapper around other compilers such as clang or gcc

## Dependencies
 - curl
 - toml++
 - rapidjson

## Installation
Create a environment variable 'CLARBE_HOME' and add 'CLARBE_HOME/bin' to path.
Download the zipped source code, unzip and in the directory run in git bash terminal ```bash build.sh```.
This will create a dir 'build':
 - from 'build' drag 'clarbe.exe' to 'CLARBE_HOME/bin'
Inside 'CLARBE_HOME' create a file 'config.toml' and configure based on the wiki.
now run in terminal ```clarbe -v```
