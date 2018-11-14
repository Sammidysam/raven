# raven
A very judgmental bird

# Compiling

The Twitter handler aspect of this code is dependent on [twitcurl](https://github.com/swatkat/twitcurl).
As a result, to build this program, it is necessary to build this library.
To do so, clone the repository, change directory into `libtwitcurl`, and make
the library into a subdirectory of your choice (you should set the staging
directory in the Makefile of that project).
Then, take the compiled library files (the files that end up in `lib`), and
move them into the `lib/` subdirectory here.
Then, when you compile this project and run using the helper script, it will use those
libraries.
