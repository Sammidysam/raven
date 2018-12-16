# raven
A very judgmental bird

# Pre-compile

Before the program is even compiled, you must copy `twitter/secrets.h.sample` to `twitter/secrets.h` as well as `twitter-rb/secrets.rb.sample` to `twitter-rb/secrets.rb` and then fill in the two variables with your Twitter app's keys.

# Compiling

The C server and C analyzer can be compiled by running `make` in the root directory.
All compiled binaries will be outputted into the `out/` directory.

Be sure to run `bundle install` to make sure that the Twitter grabber works!

Note: The following paragraph applies to the failed attempt to write the Twitter grabber in C++.
If you seek to make this work using C++, follow the instruction below; otherwise, use the Ruby grabber.
To use the C++ Twitter grabber, you will also need to uncomment Makefile rules that were removed when these areas were abandoned.

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

To run, for use `./run.sh`.
This will run the server which is the mastermind that links every other file.

Note: If you seek to run the C++ Twitter grabber after compiling it, you will likely need to append the library load path to be able to run it.
An example of doing this is contained in the old `run.sh`, which you can find [here](https://raw.githubusercontent.com/Sammidysam/raven/738d057b33675ace3fafec37d8ffb740e3d0a5b2/run.sh).

To later view analysis results, you will likely want to use the `graph.html` page provided in the root directory.
This page will load JavaScript that will graph your analysis results into a total aggregate rating over time.

# Configuration

The main configuration file is `analyses.txt`.
This file contains each separate analysis to be run on a new line.
The corresponding `graph.html` file will graph each of them into a separate graph.

The server will grab new data from Twitter every six hours; this is not in a configuration file unfortunately, so the server would have to be recompiled to change this.
