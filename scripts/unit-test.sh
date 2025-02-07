CXX="/d/msys64/mingw64/bin/clang++.exe"
CXXFLAGS="-std=c++26 -stdlib=libc++ -O0 -g -v -Wall -Wextra -fpermissive"
LIBS="-lcurl"
INC="-I ../../include -I ../../third-party/Catch2/src -I ../../third-party/tomlplusplus -I ../../third-party/rapidjson/include -I ../../third-party/curl/include"

mkdir -p third-party
cd third-party

git clone "https://github.com/catchorg/Catch2.git" && git -C curl pull "https://github.com/catchorg/Catch2.git"

cd ..
cd tests
mkdir -p build
cd build

for src in ../*.cpp; do
  base=$(basename "$src" .cpp)
  $CXX -c "$src" -o "${base}.o" $INC $LIBS $CXXFLAGS
done
$CXX -c "../../src/args.cpp" -o "args.o" $INC $LIBS $CXXFLAGS

$CXX -o tests.exe *.o $INC $LIBS $CXXFLAGS
