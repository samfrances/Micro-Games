FROM gcc:10.3 AS builder

RUN apt-get update && apt-get install -y cmake

RUN set -ex ; \
    wget -q -O /root/googletest.tar.gz https://github.com/google/googletest/archive/release-1.10.0.tar.gz ; \
    mkdir -p /root/googletest/build ; \
    tar -xzC /root/googletest --strip-components=1 -f /root/googletest.tar.gz ; \
    cmake -S /root/googletest -B /root/googletest/build ; \
    make -C /root/googletest/build install ; \
    rm -rf /root/googletest /root/googletest.tar.gz

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY ./src /usr/src/Starship-Takeoff

# Specify the working directory
WORKDIR /usr/src/Starship-Takeoff

RUN mkdir -p build
WORKDIR /usr/src/Starship-Takeoff/build
RUN cmake ..
RUN cmake --build .

FROM ubuntu:latest

WORKDIR /opt/Starship-Takeoff

COPY --from=builder /usr/src/Starship-Takeoff/build/Test .
COPY --from=builder /usr/src/Starship-Takeoff/build/hello_test .

# Run the output program from the previous step
CMD ["./Test"]
