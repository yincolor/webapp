# gcc `pkg-config --cflags gtk4 webkitgtk-6.0` test.c core/linux/api.c core/linux/icon.c -o learn04.run `pkg-config --libs gtk4 webkitgtk-6.0`

cd core/linux/
mkdir build
cd build
cmake ..
make
cd ../../../
cp ./core/linux/build/libwebapp.so ./
gcc  `pkg-config --cflags gtk4 webkitgtk-6.0`  test.c -o test.run libwebapp.so
