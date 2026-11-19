CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Ilab3/include
COVFLAGS = --coverage -O0 -g
SRCS = $(wildcard lab3/src/*.cpp)

.PHONY: all cpp cpp-boost cpp-catch2 go test bench coverage lint clean

all: cpp go

cpp:
	mkdir -p lab3/build
	$(CXX) $(CXXFLAGS) $(COVFLAGS) $(SRCS) lab3/tests/tests_google.cpp -o lab3/build/run_google -lgtest -lgtest_main -lpthread
	$(CXX) $(CXXFLAGS) -O2 $(SRCS) lab3/bench/bench_main.cpp -o lab3/build/run_bench -lbenchmark -lpthread

cpp-boost:
	mkdir -p lab3/build
	$(CXX) $(CXXFLAGS) $(SRCS) lab3/tests/tests_boost.cpp -o lab3/build/run_boost

cpp-catch2:
	mkdir -p lab3/build
	$(CXX) $(CXXFLAGS) $(SRCS) lab3/tests/tests_catch2.cpp -o lab3/build/run_catch2 -lCatch2Main -lCatch2

go:
	cd lab3-go && go build ./...

test: cpp
	./lab3/build/run_google
	cd lab3-go && go test -v -count=1 ./...

bench: cpp
	./lab3/build/run_bench
	cd lab3-go && go test -bench=. -run=^$$ ./...

coverage: cpp
	./lab3/build/run_google
	geninfo lab3/build --output-filename lab3/build/coverage.info --ignore-errors mismatch,gcov
	lcov --extract lab3/build/coverage.info '*/lab3/src/*' '*/lab3/include/*' --output-file lab3/build/coverage_filtered.info --ignore-errors unused
	genhtml lab3/build/coverage_filtered.info --output-directory lab3/build/coverage_html
	cd lab3-go && go test ./... -coverprofile=coverage.out && go tool cover -html=coverage.out -o coverage.html

lint:
	cppcheck --enable=warning,style,performance,portability --std=c++17 -I lab3/include lab3/src lab3/include
	cd lab3-go && go vet ./...

clean:
	rm -rf lab3/build lab3-go/coverage.out lab3-go/coverage.html
