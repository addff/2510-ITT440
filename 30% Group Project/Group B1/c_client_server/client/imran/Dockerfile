FROM gcc:latest
WORKDIR /app
COPY imran_client.c .
RUN gcc imran_client.c -o imran
CMD ["./imran"]