CXX="/d/msys64/mingw64/bin/clang++.exe"
CXXFLAGS="--std=c++2a -O0 -g -fpermissive -v -Wall -Wextra"

mkdir -p build
cd build

echo "Building compiler objects:"

# Compile each .cpp file into an object file
for src in ../src/*.cpp; do
  # Get the base name of the source file (without path and extension)
  base=$(basename "$src" .cpp)
  # Compile the source file into an object file
  $CXX -c "$src" -o "${base}.o" -I "../include" -I "../third-party" $CXXFLAGS
done

echo "Building compiler binary:"

# Link all object files to create the final binary
$CXX -o "clarbe.exe" *.o $CXXFLAGS

# Send binary to the clarbe binaries dir
cp "clarbe.exe" "$CLARBE_HOME/bin"

echo "Ended compiler build procedure"

cd ..