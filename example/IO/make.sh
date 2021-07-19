mkdir -p /tmp/libext/example/IO

clang++ -std=c++2a $(dirname $0)/main.cpp -o /tmp/libext/example/IO/out.a

if [[ $@ == *"--run"* ]]; then
    /tmp/libext/example/IO/out.a
fi