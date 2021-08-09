TEST=$(dirname $0)/test
SRC=$(dirname $0)/src
OUT="/tmp/libext"
FLAGS="-std=c++2a -g -O0 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-misleading-indentation -Wwrite-strings -I$OUT/include"

[ ! -d $OUT ] 				      && mkdir -p $OUT
[ ! -d $OUT/obj ] 			      && mkdir -p $OUT/obj
[ ! -d $OUT/obj/core ] 			  && mkdir -p $OUT/obj/core
[ ! -d $OUT/obj/gfx ] 			  && mkdir -p $OUT/obj/gfx
[ ! -d $OUT/obj/ui ] 			  && mkdir -p $OUT/obj/ui
[ ! -d $OUT/obj/ui/apple ] 	      && mkdir -p $OUT/obj/ui/apple
[ ! -d $OUT/lib ] 			      && mkdir -p $OUT/lib
[ ! -d $OUT/include ] 		      && mkdir -p $OUT/include
[ ! -d $OUT/include/libext ]      && mkdir -p $OUT/include/libext
[ ! -d $OUT/include/libext/core ] && mkdir -p $OUT/include/libext/core
[ ! -d $OUT/include/libext/gfx ]  && mkdir -p $OUT/include/libext/gfx
[ ! -d $OUT/include/libext/ui ]   && mkdir -p $OUT/include/libext/ui

make_core() {
    cp $SRC/core.hpp $OUT/include/libext/core.hpp

    for path in $SRC/core/*.hpp; do
        cp $(realpath $path) $OUT/include/libext/core/$(basename $path)
    done

    for path in $SRC/core/*.cpp; do
        clang++ -c $FLAGS $(realpath $path) -o $OUT/obj/core/$(basename $path .cpp).o
        if (( $? != 0 )); then
            exit
        fi
    done

    ar rc $OUT/lib/libext-core.a $OUT/obj/core/*.o
}

make_ui() {
    cp $SRC/ui.hpp $OUT/include/libext/ui.hpp

    for path in $SRC/ui/*.hpp; do
        cp $(realpath $path) $OUT/include/libext/ui/$(basename $path)
    done

    for path in $SRC/ui/*.cpp; do
        clang++ -c $FLAGS $(realpath $path) -o $OUT/obj/ui/$(basename $path .cpp).o
        if (( $? != 0 )); then
            exit
        fi
    done

    for path in $SRC/ui/apple/*.mm; do
        clang++ -c $FLAGS $(realpath $path) -o $OUT/obj/ui/apple/$(basename $path .mm).o
        if (( $? != 0 )); then
            exit
        fi
    done

    ar rc $OUT/lib/libext-ui.a $OUT/obj/ui/*.o $OUT/obj/ui/apple/*.o
}

install() {
	cp -r $OUT/include/libext /usr/local/include
	cp $OUT/lib/libext-core.a /usr/local/lib/libext-core.a
    cp $OUT/lib/libext-ui.a /usr/local/lib/libext-ui.a
}

test_() {
	clang++ $FLAGS -fsanitize=address $TEST/main.cpp -o $OUT/test.a
	$OUT/test.a
}

make_core
make_ui
install
test_