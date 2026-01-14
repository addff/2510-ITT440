FROM ubuntu:22.04

RUN apt-get update && apt-get install -y build-essential && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY client.c .

# Compile the client
RUN gcc client.c -o client

# Run the client
CMD ["./client"]
