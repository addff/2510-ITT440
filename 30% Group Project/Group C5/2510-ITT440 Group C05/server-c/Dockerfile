FROM ubuntu:22.04

ARG SERVER_FILE

RUN apt-get update && apt-get install -y \
    gcc \
    libmysqlclient-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Use the build argument
COPY ${SERVER_FILE} server.c

RUN gcc -o server server.c -lmysqlclient -lpthread

CMD ["./server"]
# CMD ["tail", "-f", "/dev/null"]