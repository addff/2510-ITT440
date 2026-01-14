FROM ubuntu:22.04

WORKDIR /app

RUN apt-get update && apt-get install -y build-essential && rm -rf /var/lib/apt/lists/*

COPY client.c .

RUN gcc client.c -o client

CMD ["./client"]
