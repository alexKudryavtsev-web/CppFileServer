# C++ File Server.

Server for sharing static files written on C++. Made by Alexander Kudryavtsev as coursework.

### Workflow

Build app:

```bash
docker build -t cppfileserver .
```

Run app:

```bash
docker run -p 8080:8080 cppfileserver
```