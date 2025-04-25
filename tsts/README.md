# README

This repository contains the sources for testing the libft library sources.

By default we expect the directory structure to look something like this: 

``` bash
root
	|
	| srcs
	|	|
	|	+- libft
	|
	| tsts
	|	|
	|	+- libft
			|
			+ lib --> ../../srcs/libft 
```

make all will create the symlink if it does not exist.
To specify another target than ../../srcs/libft run make like this: 

``` bash
make all LIB_SRC=/path/to/libft_folder
```


