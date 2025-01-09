CXX="clang++"
FLAGS="-fpermissive -v"
FINAL="compiler"

mkdir -p build
cd build

mkdir -p $FINAL
cd $FINAL

echo "Building compiler objects:"

# Compile each .cpp file into an object file
for src in ../../compiler/*.cpp; do
  # Get the base name of the source file (without path and extension)
  base=$(basename "$src" .cpp)
  # Compile the source file into an object file
  $CXX -c "$src" -o "${base}.o" -I "../../compiler_include" $FLAGS
done

echo "Building compiler binary:"

# Link all object files to create the final binary
$CXX -o "$FINAL.exe" *.o $FLAGS

echo "Ended compiler build procedure"

cd ..
mkdir -p debug
cd debug

echo "building debug package:"
time cmake -DCMAKE_BUILD_TYPE=Debug ../..
echo "building debug binary:"
time cmake --build . --config Debug
echo "ended debug build procedure"

cd ..
mkdir -p release
cd release

echo "building release package:"
time cmake -DCMAKE_BUILD_TYPE=Release ../..
echo "building release binary:"
time cmake --build . --config Release
echo "ended release build procedure"

cd ../..