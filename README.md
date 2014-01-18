# Time Cat
Time Cat is a program to add timestamps to text. It is useful for adding timestamps to the logs of long running operations, so that you can easily monitor the progress and time elapsed.

Time Cat has no options or configuration. It simple reads from `stdin` and echoes the input to `stdout` prepended with a timestamp and a single tab character.

```
$ echo "Hello world" | tcat
2014-01-18T13:18:39Z	Hello world
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
2014-01-18T13:19:18Z	PING github.com (192.30.252.130): 56 data bytes
2014-01-18T13:19:18Z	64 bytes from 192.30.252.130: icmp_seq=0 ttl=52 time=99.402 ms
2014-01-18T13:19:19Z	64 bytes from 192.30.252.130: icmp_seq=1 ttl=52 time=100.499 ms
2014-01-18T13:19:20Z	64 bytes from 192.30.252.130: icmp_seq=2 ttl=52 time=102.812 ms
2014-01-18T13:19:20Z
2014-01-18T13:19:20Z	--- github.com ping statistics ---
2014-01-18T13:19:20Z	3 packets transmitted, 3 packets received, 0.0% packet loss
2014-01-18T13:19:20Z	round-trip min/avg/max/stddev = 99.402/100.904/102.812/1.421 ms
```

## Advanced Usage
Time Cat prepends each line of input with a timestamp followed by a single tab character. This means that it is very easy to remove the timestamps again. You can use `cut -f 2`, for example.
```
$ echo foo
foo
$ echo foo | tcat
2014:01:16 17:55:19	foo
$ echo foo | tcat | cut -f 2
foo
```

## License
Time Cat is released under the MIT License.
