FROM gcc:10.3

RUN apt-get update && apt-get install -y cmake

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY ./src /usr/src/Starship-Takeoff

# Specify the working directory
WORKDIR /usr/src/Starship-Takeoff

RUN set -ex ; \
    mkdir -p build ; \
    cmake -S . -B ./build ; \
    make -C ./build ;

# Run the output program from the previous step
CMD ["./build/Test"]
