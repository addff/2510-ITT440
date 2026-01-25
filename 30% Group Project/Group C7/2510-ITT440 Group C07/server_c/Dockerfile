FROM debian:stable-slim


RUN apt-get update && apt-get install -y gcc libmariadb-dev libmariadb-dev-compat

WORKDIR /app

COPY server.c .

RUN gcc server.c -o c_server -lmysqlclient -lpthread

CMD ["./c_server"]
