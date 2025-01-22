CXX="/d/msys64/mingw64/bin/clang++.exe"
CXXFLAGS="-std=c++26 -stdlib=libc++ -O0 -g -v -Wall -Wextra -fpermissive -pedantic-errors"
LIBS="-lcurl"
INC="-I ../include -I ../third-party/tomlplusplus -I ../third-party/rapidjson/include -I ../third-party/curl/include"

mkdir -p third-party
cd third-party

git clone "https://github.com/marzer/tomlplusplus.git" && git -C tomlplusplus pull "https://github.com/marzer/tomlplusplus.git"
git clone "https://github.com/Tencent/rapidjson.git" && git -C rapidjson pull "https://github.com/Tencent/rapidjson.git"
git clone "https://github.com/curl/curl.git" && git -C curl pull "https://github.com/curl/curl.git"

cd ..
mkdir -p build
cd build

echo "Building compiler objects:"

# Compile each .cpp file into an object file
for src in ../src/*.cpp; do
  # Get the base name of the source file (without path and extension)
  base=$(basename "$src" .cpp)
  # Compile the source file into an object file
  $CXX -c "$src" -o "${base}.o" $INC $LIBS $CXXFLAGS
done

echo "Building compiler binary:"

# Link all object files to create the final binary
$CXX -o clarbe.exe *.o $INC $LIBS $CXXFLAGS

# Send binary to the clarbe binaries dir
cp "clarbe.exe" "$CLARBE_HOME/bin"

echo "Ended compiler build procedure"

cd ..