FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    gcc \
    libmysqlclient-dev \
    make \
    netcat

WORKDIR /app
COPY server.c Makefile ./

RUN make

EXPOSE 8080

CMD ["./server"]