@page installation Installation

<center>
	<H1>**Installation**</H1>
	- - -
</center>

# Compiling from source

First install the latest source distribution from <a href="https://github.com/kvbc/ofp" target="_blank">github</a>, if you haven't already
<a href="https://github.com/kvbc/ofp" target="_blank"><img src="github.png"></img></a>

1. Unpack the archive

  - **on Linux**
  > `gunzip ofp-VERSION_src.tar.gz`  
  > `tar xf ofp-VERSION_src.tar`

  - **on Windows**
  > `tar zxvf ofp-VERSION_src.tar.gz`

2. Configure the `makefile` to suit your needs and run `make` to compile a

  - **Static library**
  > `make o`  
  > `make slib`

  - **Dynamic library**
  > `make o`  
  > `make dlib`

3. Clean the directory
> `make clean`

# Installing the binaries

Download the latest distribution of pre-compiled OFP libraries and executables from <a href="https://sourceforge.net/projects/ofpbin/files" target="_blank">sourceforge</a>
<a href="https://sourceforge.net/projects/ofpbin" target="_blank"><img src="sourceforge.png"></img></a>