# Trivial Torrent Project: Pong Server

Before moving to the Trivial Torrent implementation itself. You need to do a very small project that it is not related to the main project, but that
will help you to familiarize yourself with the POSIX sockets API and the build environment.

Write a UDP server employing the POSIX sockets API that waits for datagrams to arrive and, for each one received, responds with another datagram addressed
to the original sender and the data contents of the original datagram. The server must reply to 3 datagrams and then quit.

Use the file `src/pong.c`. 

Use the logging API in `src/logger.h`.

Use the POSIX specification in https://pubs.opengroup.org/onlinepubs/9699919799/.

## Practical Details

### Building

Use `make` in a terminal to build your project.

~~~{.bash}
$ make
~~~

This will create the executable file `bin/pong`.

### Reference binary

For your convenience, a reference binary is provided in the `reference_binary` directory.

### Testing

The server can be tested by employing the command line tool `netcat` (see `man netcat`).

In one terminal run the pong server:

~~~{.bash}
$ bin/pong
~~~

In another terminal connect to the pong server with `netcat`:

~~~{.bash}
$ netcat -u 127.0.0.1 8080
~~~

You should be able to see that each line you write is repeated back to you. This should happen exactly three times.

Additional tests may be run with:

~~~{.bash}
$ make test
~~~

Note that gitlab runs `make test` for you every time you push something to this repository. You can see the results in the `Actions` tab.


