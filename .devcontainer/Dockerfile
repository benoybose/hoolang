FROM ubuntu:kinetic
RUN apt update
RUN apt install --yes llvm-15 llvm-15-dev cmake clang-15 \
    libclang-15-dev antlr4 libantlr4-runtime-dev default-jre \
    ninja-build git
RUN apt install --yes uuid uuid-dev zlib1g-dev gdb gdbserver
COPY ./antlr-4.7.2-complete.jar /usr/share/java/antlr-4.7.2-complete.jar
ENV CC=/usr/bin/clang-15
ENV CXX=/usr/bin/clang++-15
ENV CMAKE_BUILD_TYPE=Debug
ENV CMAKE_GENERATOR=Ninja
