A workspace similar to cargo, but for C, other features would be:
- User defined macros through a top-layer C file named "macros", with the concordant file extension(.c, .cc, etc...), the macros will be used with '@';
- User defined compile steps and order through a top-layer C file named "build", with the concordant file extension(.c, .cc, etc...);
- a packages and project file named "clarbe.toml"
- Support for multi-line strings with ´content´ or `content`