FROM gcc:10.3

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY ./src /usr/src/Starship-Takeoff

# Specify the working directory
WORKDIR /usr/src/Starship-Takeoff

# Use GCC to compile the Test.cpp source file
RUN g++ -o Test Test.cpp

# Run the output program from the previous step
CMD ["./Test"]
