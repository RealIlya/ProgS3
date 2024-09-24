CXXFLAGS = -Wall -Werror -Wextra

EXEC = release debug test

INCLUDE_PATH = include
SRC_PATH = src
TESTS_PATH = tests
BUILD_PATH = build

OBJ = share.o convert_str.o converter.o
MAIN_OBJ = ${OBJ} main.o
TEST_OBJ = ${OBJ} test.o

DEBUG_FLAG = $(if $(findstring on, $(debug)),-DDEBUG,)

define build_target
    g++ $(1) $(5) $(patsubst %.o,${BUILD_PATH}/%.o,$(2)) -o ${BUILD_PATH}/$(3) $(4)
endef

all: release

release: ${MAIN_OBJ}
	$(call build_target,${CXXFLAGS} -O3,$^,$@)

debug: ${MAIN_OBJ}
	$(call build_target,${CXXFLAGS},$^,$@)

test: ${TEST_OBJ}
	$(call build_target,${CXXFLAGS},$^,$@,-lm,${BUILD_PATH}/catch_amalgamated.o)

run:
ifeq (${build},)
	$(error Please, set the build (${EXEC}))
else
	@./${BUILD_PATH}/${build}
endif

catch_amalgamated.o: ${INCLUDE_PATH}/catch_amalgamated.cpp
	g++ ${CXXFLAGS} -c $^ -o ${BUILD_PATH}/$@ -DCATCH_AMALGAMATED_CUSTOM_MAIN

%.o: ${SRC_PATH}/%.cpp
	g++ ${CXXFLAGS} -c $^ -o ${BUILD_PATH}/$@ ${DEBUG_FLAG}

%.o: ${TESTS_PATH}/%.cpp
	g++ ${CXXFLAGS} -c $^ -o ${BUILD_PATH}/$@ ${DEBUG_FLAG}

build_catch_amalgamated: catch_amalgamated.o

clean:
	find ${BUILD_PATH} -name '*.o' ! -name 'catch_amalgamated.o' -delete

clean_executables:
	rm -f $(patsubst %.exe,${BUILD_PATH}/%.exe,${EXEC})