#Updates

1.All the files in KORE app format
2.Adding xml parse data to DB:needs correction of UserProperties 
3.Parse payload data to JSON

________________________________________________________________________

# Introduction

This project involves developing an Enterprise Service Bus (ESB) in C. It is assumed that you are comfortable programming in C on a *NIX type of operating system. We will be using `git` to version control our source code artefacts. All code will be checked-in to GitHub repositories of your respective teams.

## Setting up the development environment

Following instructions assume that you are working on an Ubuntu machine, and are in the sudoers group (or have root access).

### Required tools

1. An IDE. You should use either [Visual Studio Code](https://code.visualstudio.com/) or [JetBrains CLion](https://www.jetbrains.com/clion/) IDE for writing and debugging your code.
1. [Postman](https://www.postman.com/downloads/) for easily testing the HTTP endpoints.
1. `git` for working with version control repositories. You can install the `git` client by running `sudo apt install git` in a shell.

### Installing essential libraries that you will need

1. Open a shell and run `sudo apt update`
1. Ensure that you have installed the essential headers and libraries: `sudo apt install build-essential`
1. You will be writing unit tests for all your C code using [munit](https://nemequ.github.io/munit/#getting-started).
1. Install Kore Web framework as [described here](https://docs.kore.io/3.3.1/install.html). You will use it to write an HTTP endpoint for receiving the requests for the ESB.
NOTE: A skeleton is provided to get you started. However, you are strongly encouraged to go through the [Kore's simple guide](https://docs.kore.io/3.3.1/).

### Source code layout

To make it easy working with Kore build, you can use the following suggested layout for your code in the repository.

```bash
someuser@OX:~/temp/esb_proj/esb_app$ tree
.
├── build_tests.sh
├── cert
│   ├── key.pem
│   └── server.pem
├── conf
│   ├── build.conf
│   └── esb_app.conf <---- Name of this file must match its grandparent folder name
├── dh2048.pem
├── esb.code-workspace
├── esb_app.so
├── output
│   └── test_runner
└── src    <--------------- Your code lives under here
    ├── adapter
    │   ├── email.c
    │   └── email.h
    │   └── (Other adapters)
    ├── esb
    │   ├── esb.c
    │   ├── esb.h
    │   └── test_esb.c  <-------- Contains the uni tests for esb.c
    ├── esb_app.c
    └── test  <--------- We have kept the munit files in a common folder.
        ├── munit.c
        └── munit.h
```

The above structure was generated by running `kodev create esb_app` in the directory `~/temp/esb_proj`. Some of the default files were suitably edited to create the skeleton code which is provided to you here. You can compare the generated files to see what we have changed and added.

## Creating a workspace with the sample code

You can execute the following steps on a shell (on Ubuntu):
```bash
# Install required libraries
sudo apt update
sudo apt install build-essential
sudo apt install libssl-dev
sudo apt install wget
sudo apt install curl

# Download the kodev sources
wget https://kore.io/releases/kore-3.2.0.tar.gz
tar -xf kore-3.2.0.tar.gz
cd kore-3.2.0/

# Build and install kodev
make
sudo make install

# Change directories into a working folder
cd /path/to/where/you/want/to/work

# Name 'esb_endpoint' is important, because we will be copying the files from this repo
kodev create esb_endpoint

# Fetch the code from this repositiry
git clone https://github.com/nho2020/esb_proj.git

# Copy only the relevant files from cloned repo into your kodev created one
cp -r esb_proj/esb_app/src/* esb_endpoint/src/
cp -r esb_proj/esb_app/conf/* esb_endpoint/conf/

# Build and run the kodev application
cd esb_endpoint/
kodev build
kodev run
```

Open another shell window and run:
`curl --insecure -F "bmd_file=@/some/file/path/dummy_data.txt" https://localhost:8888/bmd`

Check the logs in first shell; it should show that the file was successfully received.

