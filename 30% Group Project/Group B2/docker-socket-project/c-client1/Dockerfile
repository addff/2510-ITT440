FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    gcc \
    make \
    netcat

WORKDIR /app
COPY client1.c Makefile ./

RUN make

#CMD ["sleep", "10"]  # Wait for servers to start
#CMD ["sh", "-c", "while true; do sleep 3600; done"]
#ENTRYPOINT ["./client"]
CMD ["tail", "-f", "/dev/null"]
