FROM gcc:latest

# Ensure system packages are updated before installing
RUN apt-get update && apt-get upgrade -y && apt-get install -y \
    make \
    fswatch \
    inotify-tools \
    nlohmann-json3-dev \
    wget \
    cmake \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Download and install httplib (header-only)
RUN wget -O /usr/local/include/httplib.h https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h

# Set working directory
WORKDIR /app

# Copy project files
COPY . /app

# Default command (optional)
CMD ["/bin/bash"]
