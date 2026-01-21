FROM gcc:latest
WORKDIR /app
COPY meerul_client.c .
RUN gcc meerul_client.c -o meerul
CMD ["./meerul"]