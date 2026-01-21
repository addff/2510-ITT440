FROM gcc:latest
RUN apt-get update && apt-get install -y default-libmysqlclient-dev
WORKDIR /app
COPY imran_server.c .
RUN gcc imran_server.c -o imran -lmysqlclient -lpthread
EXPOSE 5002
CMD ["./imran"]