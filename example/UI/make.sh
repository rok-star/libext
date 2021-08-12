if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    LIBS="-lX11"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    LIBS="-framework Cocoa"
fi

mkdir -p /tmp/libext/example/UI

clang++ -std=c++2a $LIBS -lext-core -lext-ui $(dirname $0)/main.cpp -o /tmp/libext/example/UI/out.a

if [[ $@ == *"--run"* ]]; then
    /tmp/libext/example/UI/out.a
fi