TEST=$(dirname $0)/test
SRC=$(dirname $0)/src
OUT="/tmp/libext"
FLAGS="-std=c++2a -g -O0 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-misleading-indentation -Wwrite-strings -I$OUT/include"

[ ! -d $OUT ] 				      && mkdir -p $OUT
[ ! -d $OUT/obj ] 			      && mkdir -p $OUT/obj
[ ! -d $OUT/obj/core ] 			  && mkdir -p $OUT/obj/core
[ ! -d $OUT/obj/gfx ] 			  && mkdir -p $OUT/obj/gfx
[ ! -d $OUT/obj/dom ] 			  && mkdir -p $OUT/obj/dom
[ ! -d $OUT/obj/ui ] 			  && mkdir -p $OUT/obj/ui
[ ! -d $OUT/lib ] 			      && mkdir -p $OUT/lib
[ ! -d $OUT/include ] 		      && mkdir -p $OUT/include
[ ! -d $OUT/include/libext ]      && mkdir -p $OUT/include/libext
[ ! -d $OUT/include/libext/core ] && mkdir -p $OUT/include/libext/core
[ ! -d $OUT/include/libext/gfx ]  && mkdir -p $OUT/include/libext/gfx
[ ! -d $OUT/include/libext/dom ]  && mkdir -p $OUT/include/libext/dom
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

    if [[ "$OSTYPE" == "linux-gnu"* ]] || [[ "$OSTYPE" == "darwin"* ]]; then
        for path in $SRC/core/POSIX/*.cpp; do
            clang++ -c $FLAGS $(realpath $path) -o $OUT/obj/core/POSIX_$(basename $path .cpp).o
            if (( $? != 0 )); then
                exit
            fi
        done
    fi

    ar rc $OUT/lib/libext-core.a $OUT/obj/core/*.o
}

make_gfx() {
    cp $SRC/gfx.hpp $OUT/include/libext/gfx.hpp

    for path in $SRC/gfx/*.hpp; do
        cp $(realpath $path) $OUT/include/libext/gfx/$(basename $path)
    done

    # for path in $SRC/gfx/*.cpp; do
    #     clang++ -c $FLAGS $(realpath $path) -o $OUT/obj/gfx/$(basename $path .cpp).o
    #     if (( $? != 0 )); then
    #         exit
    #     fi
    # done

    # ar rc $OUT/lib/libext-gfx.a $OUT/obj/gfx/*.o
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

    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        for path in $SRC/ui/x11/*.cpp; do
            clang++ -c $FLAGS $(realpath $path) -o $OUT/obj/ui/x11_$(basename $path .cpp).o
            if (( $? != 0 )); then
                exit
            fi
        done
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        for path in $SRC/ui/apple/*.mm; do
            clang++ -c $FLAGS $(realpath $path) -o $OUT/obj/ui/apple_$(basename $path .mm).o
            if (( $? != 0 )); then
                exit
            fi
        done
    fi

    ar rc $OUT/lib/libext-ui.a $OUT/obj/ui/*.o
}

make_dom() {
    cp $SRC/dom.hpp $OUT/include/libext/dom.hpp

    for path in $SRC/dom/*.hpp; do
        cp $(realpath $path) $OUT/include/libext/dom/$(basename $path)
    done

    # for path in $SRC/dom/*.cpp; do
    #     clang++ -c $FLAGS $(realpath $path) -o $OUT/obj/dom/$(basename $path .cpp).o
    #     if (( $? != 0 )); then
    #         exit
    #     fi
    # done

    # ar rc $OUT/lib/libext-dom.a $OUT/obj/dom/*.o
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
make_gfx
# make_ui
make_dom
install
test_