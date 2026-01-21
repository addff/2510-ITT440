
FROM ubuntu:22.04

# Install GCC and MySQL client libraries
RUN apt-get update && \
    apt-get install -y gcc libmysqlclient-dev && \
    apt-get clean

# Copy source code
COPY client.c /client.c

# Compile with MySQL client library
RUN gcc /client.c -o /client -lmysqlclient

# Run the C client
CMD ["/client"]