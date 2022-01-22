FROM weckyy702/raychel_ci:latest

#Copy source files and set the working directory
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp

ARG COMPILER

#Configure step
RUN cmake -DCMAKE_CXX_COMPILER=${COMPILER} -DRAYCHELMATH_BUILD_TESTS=ON .
RUN cmake --build . --target all test

LABEL Name=raychelmath Version=0.0.1
