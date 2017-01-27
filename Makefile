CXX = clang

CXXWARNINGS = -Wall -Wextra -Wpedantic -Wsign-conversion \
	  -Wold-style-cast -Wsign-promo -Wsign-promo -Wswitch-enum \
	  -Weffc++ -Wshadow -Wno-missing-braces

CXXFLAGS = --std=c++14 ${CXXWARNINGS} -g
LDFLAGS = -lthrift -lstdc++ --std=c++14

THRIFT_HEADERS = target/gen-cpp/RTDB.h \
								 target/gen-cpp/rtdb_constants.h \
								 target/gen-cpp/rtdb_types.h

build: target/rtdb-server.exe 

target/rtdb-server.exe: target/server.o target/RTDB-thrift.a
	${CXX} ${LDFLAGS} -o $@ $^

target/%.o: src/%.cc  target/rtdb.thrift.touch
	${CXX} ${CXXFLAGS} -c -o $@ $(filter-out %.touch,$^) 

target/gen-cpp/%.o: target/rtdb.thrift.touch target/gen-cpp/%.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $(filter-out %.h,$^)

target/RTDB-thrift.a: target/gen-cpp/RTDB.o target/gen-cpp/rtdb_constants.o target/gen-cpp/rtdb_types.o
	ar cr $@ $?

target/gen-cpp/%.cpp: target/rtdb.thrift.touch

target/gen-cpp/%.h: target/rtdb.thrift.touch

target/rtdb.thrift.touch: rtdb.thrift
	thrift --gen cpp -o target $^
	touch $@


clean:
	rm -r target
	mkdir -p target/gen-cpp

