FROM gcc:latest
RUN apt-get update && apt-get install -y default-libmysqlclient-dev
WORKDIR /app
COPY meerul_server.c .
RUN gcc meerul_server.c -o meerul -lmysqlclient -lpthread
EXPOSE 5004
CMD ["./meerul"]