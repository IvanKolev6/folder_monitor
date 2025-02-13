# Variables
DOCKER := $(shell which docker)
IMAGE_NAME = folder_monitor_image
EXECUTABLE = file_monitor
SRC_DIR = /app/src
BIN_DIR = /app/bin
CONFIG_FILE = /app/config/config.json

# Build Docker image
build:
	$(DOCKER) build -t $(IMAGE_NAME) .

# Compile C++ Code
compile:
	$(DOCKER) run --rm -v "$(PWD)":/app $(IMAGE_NAME) bash -c "\
		mkdir -p $(BIN_DIR) && \
		g++ -std=gnu++23 -Wall -o $(BIN_DIR)/$(EXECUTABLE) $(SRC_DIR)/*.cpp $(SRC_DIR)/*.hpp"

# Run Program
run:
	$(DOCKER) run --rm -v "$(PWD)":/app $(IMAGE_NAME) bash -c "\
		$(BIN_DIR)/$(EXECUTABLE) $(CONFIG_FILE)"

# Clean
clean:
	$(DOCKER) run --rm -v "$(PWD)":/app $(IMAGE_NAME) bash -c "rm -rf $(BIN_DIR)"
