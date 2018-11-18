# raven
A very judgmental bird

# Pre-compile

Before the program is even compiled, you must copy `twitter/secrets.h.sample` to `twitter/secrets.h` and then fill in the two variables with your Twitter app's keys.

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

# Running

To run, for now use `./run.sh`.
(This only applies to the Twitter grabber.)
In the future, better scripts will probably be made.
This is necessary because the library load path needs to be appended
in order for the Twitter library to be used.
