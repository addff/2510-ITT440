FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    gcc \
    libmysqlclient-dev \
    make \
    netcat

WORKDIR /app
COPY server2.c Makefile ./

RUN make

EXPOSE 8084

CMD ["./server"]
