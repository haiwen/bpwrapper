git clone https://chromium.googlesource.com/breakpad/breakpad
cd breakpad
mkdir -p src/third_party/lss/
mkdir -p third_party/lss/ && cd third_party/lss/
git clone https://chromium.googlesource.com/linux-syscall-support
cp linux-syscall-support/*.h .
cp linux-syscall-support/*.h ../../src/third_party/lss/
cd -
./configure --prefix=/tmp/usr
make -j4
make install
