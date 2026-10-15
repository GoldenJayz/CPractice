# Project: In-Memory Key-Value Store with a Command Parser (mini-Redis)

A REPL that supports `SET`, `GET`, `DEL`, `EXISTS`, `INCR`, and `EXPIRE`/`TTL`, with optional transactions. A good one-hour C++ build: it touches the core things C++ is good for without needing any external libraries.

**Difficulty:** Moderate
**Time budget:** ~1 hour

## What You'll Build

```
> SET name jaden
OK
> GET name
"jaden"
> INCR visits
(integer) 1
> EXPIRE name 10
(integer) 1
> TTL name
(integer) 9
> BEGIN
> SET a 1
> ROLLBACK
> GET a
(nil)
```

## Suggested Structure

1. **Tokenizer (10 min):** Split input into tokens, handling quoted strings like `SET msg "hello world"`.
2. **Store class (15 min):** Wrap `std::unordered_map<std::string, Entry>` where `Entry` holds a value and an optional `std::chrono::steady_clock::time_point` expiry.
3. **Command dispatch (15 min):** A `std::unordered_map<std::string, std::function<std::string(const Args&)>>` mapping command names to handlers. Cleaner than a giant if/else chain.
4. **Lazy expiration (10 min):** Check expiry on every `GET`/`EXISTS`/`TTL` and erase the key if expired. No background thread needed.
5. **Transactions (10 min, stretch):** Keep a stack of "undo logs" (a map of key to previous value or absence). `BEGIN` pushes a frame, `ROLLBACK` pops and restores, `COMMIT` discards the frame.

## Concepts You'll Practice

- RAII and class design
- STL containers, `std::optional`, `std::function`
- `<chrono>` for time handling
- Error handling for malformed commands (wrong arg counts, `INCR` on a non-integer)

## Stretch Goals

- Persist to disk with a simple append-only log and replay it on startup
- Add `LPUSH`/`LRANGE` list types using `std::variant<std::string, std::deque<std::string>>`
- Wrap it in a TCP server with POSIX sockets so you can connect with `nc`

## Alternatives at Similar Difficulty

- **LRU cache + benchmark:** A doubly linked list plus hash map, with a timing harness to compare against a naive version
- **Text-adventure engine:** Parse data-driven rooms and items from a file, with a verb/noun parser
- **Bank/ledger simulator:** Accounts, transfers, and an audit log with invariant checks
