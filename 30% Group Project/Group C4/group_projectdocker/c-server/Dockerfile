FROM ubuntu:22.04

# Install compiler and MySQL client development library
RUN apt-get update && \
    apt-get install -y gcc libmysqlclient-dev && \
    apt-get clean

# Copy server source code
COPY server.c /server.c

# Compile the server
RUN gcc /server.c -o /server -I/usr/include/mysql -L/usr/lib/x86_64-linux-gnu -lmysqlclient

# Run the server
CMD ["/server"]
