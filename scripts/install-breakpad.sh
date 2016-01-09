git clone https://chromium.googlesource.com/breakpad/breakpad
cd breakpad
git checkout -b before-require-cpp11 7cc0d8562bf8b20b88cc941ba72593cb7230ecf6
mkdir -p src/third_party/lss/
mkdir -p third_party/lss/ && cd third_party/lss/
git clone https://chromium.googlesource.com/linux-syscall-support
cp linux-syscall-support/*.h .
cp linux-syscall-support/*.h ../../src/third_party/lss/
cd -
./configure --prefix=/tmp/usr
make -j4
make install
