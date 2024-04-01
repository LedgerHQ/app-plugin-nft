rm -rf build
cmake -DBOLOS_SDK=../BOLOS_SDK -DCMAKE_C_COMPILER=clang -Bbuild -H. || exit
make -C build