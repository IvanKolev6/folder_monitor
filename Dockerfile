FROM gcc:latest

# Ensure system packages are updated before installing
RUN apt-get update && apt-get upgrade -y && apt-get install -y \
    make \
    build-essential \ 
    fswatch \
    inotify-tools \
    nlohmann-json3-dev \
    libcurl4-openssl-dev \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy project files
COPY . /app

# Default command (optional)
CMD ["/bin/bash"]
