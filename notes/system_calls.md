## System Calls

- Interface to the operating system's kernel.
- Perform operations like file handling, process control, or network communication.
- Examples: `socket()`, `connect()`, `send()`, `recv()`, `close()`.

---

### 1. `accept()`
- **Purpose**: Accepts a new connection on a listening socket.
- **Usage**: Used by a server to accept an incoming connection from a client.
- **Returns**: A new file descriptor for the accepted connection or `-1` on error.

```cpp
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    
    bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    sockaddr_in client_addr = {0};
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);

    if (client_fd >= 0) {
        std::cout << "Connection accepted!\n";
    } else {
        perror("accept");
    }
    close(server_fd);
    return 0;
}
```

---

### 2. `select()` / `epoll()`
- **Purpose**: Monitors multiple file descriptors for readiness to perform I/O (e.g., read/write).
- **Usage**:
  - `select()`: Monitors a fixed number of file descriptors.
  - `epoll()`: More efficient for a large number of file descriptors.

#### Example using `select()`:
```cpp
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <iostream>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    
    bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(server_fd, &read_fds);

    timeval timeout = {5, 0}; // 5 seconds
    int activity = select(server_fd + 1, &read_fds, NULL, NULL, &timeout);

    if (activity > 0 && FD_ISSET(server_fd, &read_fds)) {
        std::cout << "New connection is ready to accept.\n";
    } else if (activity == 0) {
        std::cout << "Timeout occurred.\n";
    } else {
        perror("select");
    }
    close(server_fd);
    return 0;
}
```

---

### 3. `connect()`
- **Purpose**: Initiates a connection to a server.
- **Usage**: Used by a client to connect to a server.
- **Returns**: `0` on success or `-1` on error.

```cpp
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(client_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == 0) {
        std::cout << "Connected to the server.\n";
    } else {
        perror("connect");
    }
    close(client_fd);
    return 0;
}
```

---

### 4. `send()`
- **Purpose**: Sends data over a connected socket.
- **Usage**: Sends data to the peer socket.
- **Returns**: Number of bytes sent or `-1` on error.

```cpp
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

int send_data(int socket_fd, const std::string& message) {
    return send(socket_fd, message.c_str(), message.size(), 0);
}
```

---

### 5. `recv()`
- **Purpose**: Receives data from a connected socket.
- **Usage**: Reads data from the peer socket.
- **Returns**: Number of bytes received, `0` if the connection is closed, or `-1` on error.

```cpp
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>

void receive_data(int socket_fd) {
    char buffer[1024] = {0};
    int bytes_received = recv(socket_fd, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        std::cout << "Received: " << buffer << "\n";
    } else if (bytes_received == 0) {
        std::cout << "Connection closed.\n";
    } else {
        perror("recv");
    }
}
```

---

### 6. `close()`
- **Purpose**: Closes a socket.
- **Usage**: Frees the file descriptor associated with the socket.

```cpp
#include <unistd.h>
#include <iostream>

void close_socket(int socket_fd) {
    if (close(socket_fd) == 0) {
        std::cout << "Socket closed successfully.\n";
    } else {
        perror("close");
    }
}
```

These system calls are the foundation of socket programming and are commonly used for building network applications.