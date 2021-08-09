mkdir -p /tmp/libext/example/UI

clang++ -std=c++2a -framework Cocoa -lext-core -lext-ui $(dirname $0)/main.cpp -o /tmp/libext/example/UI/out.a

if [[ $@ == *"--run"* ]]; then
    /tmp/libext/example/UI/out.a
fi