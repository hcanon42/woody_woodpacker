# woody-woodpacker
Welcome to the first 42 project of the security branch !

## Table of Content

* [Technologies](#technologies)
* [Description](#description)
* [Installation](#installation)
* [Usage](#usage)
* [Utility](#utility)
* [Contributing](#contributing)

## Technologies

Project is created with:
* nasm 2.14.02
* ld 2.34
* gcc 9.3.0

## Description

* The first aim of this project is to create a simple packer.\
\
A packer is a program which opens, encrypts and usually compresses a binary file (ELF64 for only supported for now).\
Althought on this project the compression is optional and not done for the moment. I'll keep this project maintained and up, and perhaps will include an assembly compressor in the future.\
\
* The second goal to achieved in this project is to inject "malicious" code in the binary (for educational purposes only: the malicious program here is a simple "Hello, World!" printer).\
What for ?\
Antiviruses usually analyze a binary when they open it and load it up. So if you manage to encrypt a binary, the antiviruses won't be able to correctly assume the risks linked to executing the file.\
\
* Finally, for the program to still executes after being encrypted, you must be able to change the binary to be self-extracting so it won't cause any errors at run time.

## Installation

Just pull the project !\
\
There is a "tests" folder in which you have several binaries which you can modify. You also can change the tests/malicious.asm file used to inject specific code into the binaries.\
\
*Pro tip if you change ./tests/malicious.asm*: The bigger the code is, the bigger the injected shellcode will be, and so the less likely the packer will found a place to inject the code !

## Usage

Classic 42 Makefile:
````sh
make		#compiles everything and create woody_woodpacker binary
make clean	#removes all the .o files
make fclean	#removes all the .o files and the "woody_woodpacker" binary
make re		#cleans everything in the project and compiles everything again
````

Specific to the project:
````sh
./woody_woodpacker [ELF64_file]	#creates "woody", a copy of the original binary with injected code in it
./woody				#decryts itself, writes "....WOODY....\n", and then does the same thing as the binary from which it has been created
````

## Utility

Educational purposes only !\
I Learned a lot about ELF files and binaries in general working on this project.\
One of my favorite 42 project for now.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.