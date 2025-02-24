git clone https://github.com/catchorg/Catch2 ../Catch2
cmake -S ../Catch2 -B ../build/Catch2 \
    -DCMAKE_INSTALL_PREFIX=../build-Catch2/install/
cmake --build ../build/Catch2 -j$(nproc) --target install

export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:../build-Catch2/install
cmake -S ./examples -B ./examples/build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_COMPILER=g++
cmake --build ./examples/build -j$(nproc)