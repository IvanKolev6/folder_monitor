# Folder Monitor

This application monitors a specified folder for new files and uploads them to a server automatically.


## Prerequisites

Ensure you have the following tools installed on your system:
- Docker
- Make

## Installation

### Clone the Repository

Start by cloning the repository and navigating into the project folder:
```sh
git clone https://github.com/IvanKolev6/folder_monitor.git
cd folder_monitor
```

### Configuration

To configure the application, you need to set your values in the `config.json` file, located in the config directory.

```json
{
    "api_base_url": "https://your-api-server",
    "username": "your-username",
    "password": "your-password",
}
```
-`api_base_url`: The base URL for the server to which files will be uploaded.

-`username`: Your account's username for authentication.

-`password`: Your account's password for authentication.

Next, specify the folder you want to monitor by editing the `Makefile`:

```sh
# Set your watched folder here
DIRECTORY_WATCHER = /your/target/watch/folder
```
-`DIRECTORY_WATCHER`: Path to the folder where the application will watch for new files.

## Running the Application

### Build and Run Using Makefile
Once you have configured the application, you can build, compile, and run it using the provided `Makefile`. Here are the commands:

Build the application (this installs dependencies and sets up the environment):
```sh
make build
```

Compile the application:
```sh
make compile
```

Run the application:
```sh
make run
```

### Note

Testing File Upload
Known Issue: Authorization Denied

Currently, the file upload functionality is not fully tested. When attempting to upload files, the following error is encountered:
```sh
Authorization has been denied for this request.
```
I have tried to upload files using different methods:

-Web App

-Swagger UI

-cURL

Despite using the correct credentials, the upload still fails. With a generated token, I can see my information, home folder ID, etc., but the upload procedure doesn't work.

