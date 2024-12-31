mkdir -p build
cd build

mkdir -p debug
cd debug

echo "building debug package:"
time cmake -DCMAKE_BUILD_TYPE=Debug ../..
echo "building debug binary:"
time cmake --build .
echo "ended debug build procedure"


cd ..
mkdir -p release
cd release

echo "building release package:"
time cmake -DCMAKE_BUILD_TYPE=Release ../..
echo "building release binary:"
time cmake --build .
echo "ended release build procedure"

cd ../..
