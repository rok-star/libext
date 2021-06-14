TEST=$(dirname $0)/test
SRC=$(dirname $0)/src
OUT="/tmp/libext"
FLAGS="-std=c++2a -g -O0 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-misleading-indentation -Wwrite-strings"

[ ! -d $OUT ] 				 && mkdir -p $OUT
[ ! -d $OUT/obj ] 			 && mkdir -p $OUT/obj
[ ! -d $OUT/lib ] 			 && mkdir -p $OUT/lib
[ ! -d $OUT/include ] 		 && mkdir -p $OUT/include
[ ! -d $OUT/include/libext ] && mkdir -p $OUT/include/libext

make() {
    for path in $SRC/*.hpp; do
        cp $(realpath $path) $OUT/include/libext/$(basename $path)
    done

    for path in $SRC/*.cpp; do
        clang++ -c $FLAGS -I$OUT/include $(realpath $path) -o $OUT/obj/$(basename $path .cpp).o
        if (( $? != 0 )); then
            exit
        fi
    done

    ar rc $OUT/lib/libext.a $OUT/obj/*.o
}

install() {
	cp -r $OUT/include/libext /usr/local/include
	cp $OUT/lib/libext.a /usr/local/lib/libext.a
}

test_() {
	clang++ $FLAGS -fsanitize=address $TEST/main.cpp -o $OUT/test.a
	$OUT/test.a
}

make
install
test_