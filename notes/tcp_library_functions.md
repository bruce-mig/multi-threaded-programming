# TCP library functions

---

### 1. `htons()` (Host-to-Network Short)
- **Purpose**: Converts a 16-bit integer (short) from host byte order (endianness of the machine) to network byte order (big-endian).
- **Why?**: Network protocols like TCP/IP expect data in **network byte order**. `htons()` ensures compatibility between systems with different endianness.

#### Syntax:
```cpp
#include <arpa/inet.h>

uint16_t htons(uint16_t hostshort);
```

#### Example:
```cpp
#include <arpa/inet.h>
#include <iostream>

int main() {
    uint16_t port = 8080;
    uint16_t network_port = htons(port);

    std::cout << "Host byte order: " << port << "\n";
    std::cout << "Network byte order: " << network_port << "\n";

    return 0;
}
```

---

### 2. `inet_ntoa()` (Internet Address to ASCII)
- **Purpose**: Converts an IPv4 address from **binary form** (e.g., `struct in_addr`) to a **human-readable string** in dotted-decimal notation.
- **Limitation**: Only works for IPv4 addresses and is not thread-safe (it uses a static buffer).

#### Syntax:
```cpp
#include <arpa/inet.h>

char *inet_ntoa(struct in_addr in);
```

#### Example:
```cpp
#include <arpa/inet.h>
#include <iostream>

int main() {
    struct in_addr addr;
    addr.s_addr = htonl(0x7F000001); // 127.0.0.1 in network byte order

    char *ip_str = inet_ntoa(addr);
    std::cout << "IP Address: " << ip_str << "\n";

    return 0;
}
```

---

### 3. `inet_pton()` (Presentation to Numeric)
- **Purpose**: Converts an IP address from a **human-readable string** (presentation format) to **binary form** (numeric format) used by the OS (e.g., `struct in_addr` or `struct in6_addr` for IPv4/IPv6).
- **"pton"**: Presentation-to-Numeric.
- **Supports**: Both IPv4 and IPv6.

#### Syntax:
```cpp
#include <arpa/inet.h>

int inet_pton(int af, const char *src, void *dst);
```
- `af`: Address family (e.g., `AF_INET` for IPv4 or `AF_INET6` for IPv6).
- `src`: The IP address in human-readable form (e.g., `"127.0.0.1"`).
- `dst`: A pointer to the structure where the binary address is stored.

#### Returns:
- `1` if the conversion is successful.
- `0` if the input is invalid.
- `-1` if there’s an error (e.g., invalid address family).

#### Example:
```cpp
#include <arpa/inet.h>
#include <iostream>

int main() {
    const char *ip_str = "127.0.0.1";
    struct in_addr addr;

    if (inet_pton(AF_INET, ip_str, &addr) == 1) {
        std::cout << "IP Address converted to binary form.\n";
    } else {
        std::cerr << "Failed to convert IP Address.\n";
    }

    return 0;
}
```

---

### 4. `inet_ntop()` (Numeric to Presentation)
- **Purpose**: Converts an IP address from **binary form** (numeric format) to **human-readable string** (presentation format).
- **"ntop"**: Numeric-to-Presentation.
- **Supports**: Both IPv4 and IPv6.

#### Syntax:
```cpp
#include <arpa/inet.h>

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
```
- `af`: Address family (e.g., `AF_INET` or `AF_INET6`).
- `src`: Pointer to the binary address.
- `dst`: Buffer to store the converted IP address string.
- `size`: Size of the buffer.

#### Example:
```cpp
#include <arpa/inet.h>
#include <iostream>

int main() {
    struct in_addr addr;
    addr.s_addr = htonl(0x7F000001); // 127.0.0.1 in binary form

    char ip_str[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &addr, ip_str, sizeof(ip_str))) {
        std::cout << "IP Address: " << ip_str << "\n";
    } else {
        perror("inet_ntop");
    }

    return 0;
}
```

---

### Summary of Functions:
| Function       | Purpose                                             | Usage                         | Thread-Safe |
|----------------|-----------------------------------------------------|-------------------------------|-------------|
| `htons()`      | Converts 16-bit short to network byte order         | Host-to-network byte order    | Yes         |
| `inet_ntoa()`  | Converts binary IPv4 to dotted-decimal string       | Numeric-to-string for IPv4    | No          |
| `inet_pton()`  | Converts dotted-decimal (IPv4/IPv6) to binary       | String-to-numeric (IPv4/6)    | Yes         |
| `inet_ntop()`  | Converts binary (IPv4/IPv6) to dotted-decimal       | Numeric-to-string (IPv4/6)    | Yes         |

For modern applications, prefer `inet_pton()` and `inet_ntop()` over `inet_ntoa()` for IPv4 and IPv6 compatibility.