# Time Cat
Time Cat is a program to add timestamps to text. It is useful for adding timestamps to the logs of long running operations, so that you can easily monitor the progress and time elapsed.

Time Cat has no options or configuration. It simple reads from `stdin` and echoes the input to `stdout` prepended with a timestamp and a single tab character.

```
$ echo "Hello world" | tcat
2014-02-06T21:12:13UTC  Hello world
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
2014-02-06T21:11:37UTC  PING github.com (192.30.252.131): 56 data bytes
2014-02-06T21:11:37UTC  64 bytes from 192.30.252.131: icmp_seq=0 ttl=53 time=242.162 ms
2014-02-06T21:11:38UTC  64 bytes from 192.30.252.131: icmp_seq=1 ttl=53 time=238.695 ms
2014-02-06T21:11:39UTC  64 bytes from 192.30.252.131: icmp_seq=2 ttl=53 time=231.438 ms
2014-02-06T21:11:39UTC
2014-02-06T21:11:39UTC  --- github.com ping statistics ---
2014-02-06T21:11:39UTC  3 packets transmitted, 3 packets received, 0.0% packet loss
2014-02-06T21:11:39UTC  round-trip min/avg/max/stddev = 231.438/237.432/242.162/4.468 ms
```

## Advanced Usage
Time Cat prepends each line of input with a timestamp followed by a single tab character. This means that it is very easy to remove the timestamps again. You can use `cut -f 2`, for example.
```
$ echo foo
foo
$ echo foo | tcat
2014-02-06T21:14:16UTC  foo
$ echo foo | tcat | cut -f 2
foo
```

## Contibuting
If you'd like to contribute to `tcat`, that's awesome. Feel free to open a pull request or log an issue. For recent changes see the [changelog](https://github.com/marcomorain/tcat/blob/master/CHANGELOG.md).

[![Build Status](https://travis-ci.org/marcomorain/tcat.png?branch=master)](https://travis-ci.org/marcomorain/tcat)

## License
Time Cat is released under the [MIT License](http://www.opensource.org/licenses/MIT).
