FROM ubuntu:22.04

ARG CLIENT_FILE

RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Use the build argument
COPY ${CLIENT_FILE} client.c

RUN gcc -o client client.c

CMD ["./client"]
