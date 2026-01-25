FROM debian:stable-slim

RUN apt-get update && apt-get install -y gcc

WORKDIR /app

COPY client.c .

RUN gcc client.c -o c_client

CMD ["./c_client"]
