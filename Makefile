# Automatically determine the path to the docker executable
DOCKER := $(shell which docker)

# Variables
IMAGE_NAME = folder_monitor_image
EXECUTABLE = file_monitor
SRC_DIR = /app/src
BIN_DIR = /app/bin

# Common compile command (avoiding duplication)
COMPILE_CMD = "mkdir -p $(BIN_DIR) && g++ -std=gnu++23 -Wall -o $(BIN_DIR)/$(EXECUTABLE) $(SRC_DIR)/*.cpp"

# Build the Docker image
build:
	$(DOCKER) build -t $(IMAGE_NAME) .

# Compile the C++ code inside Docker
compile:
	$(DOCKER) run --rm -v "$(PWD)":/app $(IMAGE_NAME) bash -c $(COMPILE_CMD)

# Run the compiled program inside Docker
run:
	$(DOCKER) run --rm -v "$(PWD)":/app $(IMAGE_NAME) bash -c "$(BIN_DIR)/$(EXECUTABLE)"

# Watch for changes and rebuild automatically
watch:
	$(DOCKER) run --rm -v "$(PWD)":/app $(IMAGE_NAME) bash -c " \
		mkdir -p $(BIN_DIR) && \
		while inotifywait -e modify $(SRC_DIR)/*.cpp; do \
			echo 'Change detected. Recompiling...'; \
			g++ -std=gnu++23 -Wall -o $(BIN_DIR)/$(EXECUTABLE) $(SRC_DIR)/*.cpp && \
			$(BIN_DIR)/$(EXECUTABLE); \
		done"

# Clean build files inside the container
clean:
	$(DOCKER) run --rm -v "$(PWD)":/app $(IMAGE_NAME) bash -c "rm -rf $(BIN_DIR)"

# Rebuild everything
rebuild: clean build compile run
