# event listeners

This project involves creating UDP servers from scratch using socket programming, that listen and receive network packets from senders via UDP protocol.

## Compile and run

Compile project by running the shell script `compile.sh` in the CLI. It will output two executables: `listener_main.exe` for the UDP servers and `udp_sender.exe` for the UDP client.

Run the server with command `./listener_main.exe`. The UDP server will listen on ports `:3000` and `:3001`

```bash
Listening on UDP port no 3000
Listening on UDP port no 3001
```

Run the client and with the following arguments:

```bash
./udp_sender.exe <destination-ip-address> <destination-port> <message>
```

For example, running the following client side code:

```bash
./udp_sender.exe 127.0.0.1 3000 "Hello there"
```

Gives output:

```bash
# client side output

Dest = [127.0.0.1:3000]
---

#server side output

pkt_recv_fn() : pkt recvd = Hello there, pkt size = 11
```

