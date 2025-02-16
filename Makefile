# Set your watched folder here
DIRECTORY_WATCHER = /your/target/watch/folder

# Variables
DOCKER := $(shell which docker)
IMAGE_NAME = folder_monitor_image
EXECUTABLE = file_monitor
SRC_DIR = /app/src
INCLUDE_DIR = /app/include
BIN_DIR = /app/bin
CONFIG_FILE = /app/config/config.json
CONTAINER_WATCHED_FOLDER = /app/bin/watched_folder

# Build Docker image
build:
	$(DOCKER) build -t $(IMAGE_NAME) .

# Compile C++ Code
compile:
	$(DOCKER) run --rm -v "$(PWD)":/app -v "$(DIRECTORY_WATCHER)":$(CONTAINER_WATCHED_FOLDER) $(IMAGE_NAME) bash -c "\
		mkdir -p $(BIN_DIR) && \
		g++ -std=gnu++23 -Wall -O2 -I./include -o $(BIN_DIR)/$(EXECUTABLE) $(SRC_DIR)/*.cpp $(INCLUDE_DIR)/*.hpp -lcurl"

# Run Program
run:
	$(DOCKER) run --rm -v "$(PWD)":/app -v "$(DIRECTORY_WATCHER)":$(CONTAINER_WATCHED_FOLDER) $(IMAGE_NAME) bash -c "\
		$(BIN_DIR)/$(EXECUTABLE) $(CONFIG_FILE)"

# Clean
clean:
	$(DOCKER) run --rm -v "$(PWD)":/app $(IMAGE_NAME) bash -c "rm -rf $(BIN_DIR)"
