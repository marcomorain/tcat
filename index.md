---
layout: index
---

# Time Cat
Time Cat is a program to add timestamps to text. It is useful for adding timestamps to the logs of long running operations, so that you can easily monitor the progress and time elapsed.

Time Cat is designed to be as simple as possible to use. It simple reads from `stdin` and echoes the input to `stdout` prepended with a timestamp and a single tab character.

Time Cat allocates no memory at time – it only uses stack allocation. This means that you can pipe very long running processes to it wihtout worrying about memory leaks or fragmentation, which might cause the process to slow down or crash.

The time is printed as a full [ISO 8601](http://en.wikipedia.org/wiki/ISO_8601) timestamp, including timezone offset. An example output is `2014-02-09T21:00:17+0000`. This ensures that there is no ambiguity in the printed time. There are no whitespace characters in the timestamp. It is is easy to parse and deal with in other tools. The time format can be overriden by user if desired, by using the `--format` option.

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

The format that the time is printed in can be overiden by the user in one of two ways. You can specify the format using the `-f` or `--format` command-line options. You can also set the format by setting the `TCAT_FORMAT` environmental variable. The format should be specified using the `strftime(3)` syntax. If the format is overridden using the command-line options, this will take precence over the environment variable.

Here are three examples showing the default usage, format passed as a command-line option, and through the environment variable.

```
$ echo default | tcat
2014-03-08T13:15:43+0000  default

$ echo command-line | tcat --format '%H:%M:%S'
13:17:03 command-line

$ echo environment | TCAT_FORMAT='%Y/%m/%d' tcat
2014/03/08  environment
```

The time is formatted in UTC by default. This can be changed to output in local
time using the `--local` or `-l` option.

```
$ echo "UTC Example" | tcat
2015-01-05T14:22:34+0000  UTC Example

$ TZ="/usr/share/zoneinfo/America/Los_Angeles"
$ echo "Local Example" | tcat --local
2015-01-05T14:23:00+0000  Local Example
```

## Building
Time Cat should build easily on any Unix-like system. It has been tested on Ubuntu and OSX using gcc and clang.

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
