# Time Cat
Time Cat is a program to add timestamps to text. It is useful for adding timestamps to the logs of long running operations, so that you can easily monitor the progress and time elapsed.

Time Cat has no options or configuration. It simple reads from `stdin` and echoes the input to `stdout` prepended with a timestamp and a single tab character.

Time Cat allocated no memory at time – it only uses stack allocator. This means that you can pipe very long running processes to it wihtout worrying about memory leaks or memory fragmentation causing the process to slow down or crash.

The time is printed as a full [ISO 8601](http://en.wikipedia.org/wiki/ISO_8601) timestamp, including timezone offset. An example output is `2014-02-09T21:00:17+0000`. This ensures that there is no ambiguity in the printed time. There are no whitespace characters in the timestamp. It is is easy to parse and deal with in other tools.

```
$ echo "Hello world" | tcat
2014-02-09T21:00:17+0000  Hello world
```

## Usage
The following is the ouput from the `ping` command: 
```
$ ping -c 3 github.com
PING github.com (192.30.252.131): 56 data bytes
64 bytes from 192.30.252.131: icmp_seq=0 ttl=49 time=104.271 ms
64 bytes from 192.30.252.131: icmp_seq=1 ttl=49 time=111.290 ms
64 bytes from 192.30.252.131: icmp_seq=2 ttl=49 time=117.178 ms

--- github.com ping statistics ---
3 packets transmitted, 3 packets received, 0.0% packet loss
round-trip min/avg/max/stddev = 104.271/110.913/117.178/5.276 ms
```
The following is the same command, but this time the output has been piped through `tcat` to add a timestamp to each line.
```
$ ping -c 3 github.com | tcat
2014-02-09T20:58:42+0000  PING github.com (192.30.252.131): 56 data bytes
2014-02-09T20:58:42+0000  64 bytes from 192.30.252.131: icmp_seq=0 ttl=53 time=109.236 ms
2014-02-09T20:58:43+0000  64 bytes from 192.30.252.131: icmp_seq=1 ttl=53 time=116.658 ms
2014-02-09T20:58:44+0000  64 bytes from 192.30.252.131: icmp_seq=2 ttl=53 time=106.783 ms
2014-02-09T20:58:44+0000
2014-02-09T20:58:44+0000  --- github.com ping statistics ---
2014-02-09T20:58:44+0000  3 packets transmitted, 3 packets received, 0.0% packet loss
2014-02-09T20:58:44+0000  round-trip min/avg/max/stddev = 106.783/110.892/116.658/4.198 ms
```

Time Cat prepends each line of input with a timestamp followed by a single tab character. This will be the first whitespace character on the live. This means that it is very easy to remove the timestamps again. You can use `cut -f 2`, for example.
```
$ echo foo
foo
$ echo foo | tcat
2014-02-09T21:00:33+0000  foo
$ echo foo | tcat | cut -f 2
foo
```

## Building
Time Cat should build easily on any Unix. It has been tested on Ubuntu and OSX using gcc and clang. 

To build Time Cat just navigate to where you have cloned the respository and run `make`.

```
make
make install
```

If you have any issues building it please open a bug-report including the compiler and platform that you are building on (the output from `cc -v` and `uname -a` is ideal).

## Contibuting
If you'd like to contribute to `tcat`, that's awesome. Feel free to open a pull request or log an issue. For recent changes see the [changelog](https://github.com/marcomorain/tcat/blob/master/CHANGELOG.md).

[![Build Status](https://travis-ci.org/marcomorain/tcat.png?branch=master)](https://travis-ci.org/marcomorain/tcat)

## License
Time Cat is released under the [MIT License](http://www.opensource.org/licenses/MIT).
