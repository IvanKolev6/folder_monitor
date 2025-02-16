# Folder Monitor

This application monitors a specified folder for new files and uploads them to a server.

## Prerequisites

- Docker
- Make

## Installation

### Clone the Repository

```sh
git clone https://github.com/IvanKolev6/folder_monitor.git
cd folder_monitor
```

### Configuration

Add your configuration in `config.json` which is in the `config` directory with the following content:

```json
{
    "api_base_url": "https://your-api-server",
    "username": "your-username",
    "password": "your-password",
}
```

Set the wanted directory wantcher in `Makefile`:

```sh
# Set your watched folder here
DIRECTORY_WATCHER = /your/target/watch/folder
```

## Running the Application

### Using Makefile

You can use the provided Makefile to build, compile, and run the application.

```sh
make build
make compile
make run
```

### Note

The upload file functionality is not tested because I don't have permissions to upload files to my home folder with the given username and password.