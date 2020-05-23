CC_EXEC = g++
CC_FLAGS = -std=c++11

CC = ${CC_EXEC} ${CC_FLAGS}

BUILD_DIR = build

all: executable.out

executable.out:  ${BUILD_DIR}/main.o  ${BUILD_DIR}/UTrelloInterface.o  ${BUILD_DIR}/User.o  ${BUILD_DIR}/List.o  ${BUILD_DIR}/Task.o
	g++  ${BUILD_DIR}/main.o ${BUILD_DIR}/UTrelloInterface.o ${BUILD_DIR}/User.o ${BUILD_DIR}/List.o ${BUILD_DIR}/Task.o -o ${BUILD_DIR}/executable.out


${BUILD_DIR}/main.o: main.cpp UTrelloInterface.hpp User.hpp List.hpp Task.hpp
	${CC} -c main.cpp -o ${BUILD_DIR}/main.o

${BUILD_DIR}/User.o: User.cpp User.hpp
	${CC} -c User.cpp -o ${BUILD_DIR}/User.o

${BUILD_DIR}/List.o: List.cpp List.hpp
	${CC} -c List.cpp -o ${BUILD_DIR}/List.o

${BUILD_DIR}/Task.o: Task.cpp Task.hpp
	${CC} -c Task.cpp -o ${BUILD_DIR}/Task.o
${BUILD_DIR}/UTrelloInterface.o: UTrelloInterface.cpp UTrelloInterface.hpp Task.hpp List.hpp User.hpp
	${CC} -c UTrelloInterface.cpp -o ${BUILD_DIR}/UTrelloInterface.o

.PHONY: clean
clean:
	rm -rf build/ && mkdir -p build