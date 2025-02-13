# Use the GCC base image
FROM gcc:latest

# Install additional libraries
RUN apt-get update && apt-get install -y make fswatch inotify-tools

# Set the working directory
WORKDIR /app

# Copy the local source code to the container
COPY . /app

# Default command (can be overridden by Makefile)
CMD ["make"]
