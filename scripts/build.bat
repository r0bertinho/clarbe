@echo off

setlocal

:: Set compiler and flags
set CXX="D:\msys64\mingw64\bin\clang++.exe"
set CXXFLAGS=-std=c++26 -stdlib=libc++ -O0 -g -v -Wall -Wextra -fpermissive -pedantic-errors
set LIBS=-lcurl
set INC=-I ../include -I ../third-party/tomlplusplus -I ../third-party/rapidjson/include -I ../third-party/curl/include

:: Create directories
mkdir third-party
cd third-party

:: Clone or update repositories
git clone "https://github.com/marzer/tomlplusplus.git" && git -C tomlplusplus pull "https://github.com/marzer/tomlplusplus.git"
git clone "https://github.com/Tencent/rapidjson.git" && git -C rapidjson pull "https://github.com/Tencent/rapidjson.git"
git clone "https://github.com/curl/curl.git" && git -C curl pull "https://github.com/curl/curl.git"

cd ..
mkdir build
cd build

echo Building compiler objects:

:: Compile each .cpp file into an object file
for %%f in (../src/*.cpp) do (
  set "src=%%f"
  set "base=%%~nf"
  %CXX% -c "%%f" -o "%%~nf.o" %INC% %LIBS% %CXXFLAGS%
)

:: Link all object files to create the final binary
%CXX% -o clarbe.exe *.o %INC% %LIBS% %CXXFLAGS%

:: Send binary to the clarbe binaries dir
copy "clarbe.exe" "%CLARBE_HOME%\bin"

cd ..
endlocal
