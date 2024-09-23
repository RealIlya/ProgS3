CXXFLAGS = -Wall -Werror -Wextra

LEVEL0_PATH = level0
LEVEL1_PATH = level1
BUILD_PATH = build

DEBUG_FLAG = $(if $(findstring on, $(debug)),-DDEBUG,)
LEVEL_FLAG = -DLEVEL${level}

obj = share.o convert_str.o opers.o
opt = share.o $(if $(filter ${level},0),convert_str.o,opers.o)

.PHONY: debug run

all: release

release: ${obj} main.o
	g++ -O3 $(patsubst %.o,${BUILD_PATH}/%.o,$^) -o ${BUILD_PATH}/$@

debug: ${obj} main.o
	g++ $(patsubst %.o,${BUILD_PATH}/%.o,$^) -o ${BUILD_PATH}/$@

testl: $(opt) l_test.o
	g++ ${BUILD_PATH}/catch_amalgamated.o $(patsubst %.o,${BUILD_PATH}/%.o,$(opt)) ${BUILD_PATH}/l_test.o -o ${BUILD_PATH}/$@ -lm

run:
ifeq (${build},)
	$(error Please, set the build)
else
	@./${BUILD_PATH}/${build}
endif

run_testl:
	@./${BUILD_PATH}/testl

l_test.o: test.cpp
ifeq (${level},)
	$(error Please, set the level)
else
	g++ ${CXXFLAGS} -c $^ -o ${BUILD_PATH}/$@ ${LEVEL_FLAG}
endif

%.o: $(LEVEL1_PATH)/%.cpp
	g++ ${CXXFLAGS} -c $^ -o $(BUILD_PATH)/$@ ${DEBUG_FLAG}

catch_amalgamated.o: catch_amalgamated.cpp
	g++ ${CXXFLAGS} -c $^ -o ${BUILD_PATH}/$@ -DCATCH_AMALGAMATED_CUSTOM_MAIN

build_catch_amalgamated: catch_amalgamated.o

clean:
	find ${BUILD_PATH} -name '*.o' ! -name 'catch_amalgamated.o' -delete

clean_executables:
	rm -f ${BUILD_PATH}/release ${BUILD_PATH}/debug ${BUILD_PATH}/testl