FROM gcc:latest

# Install MySQL client library
RUN apt-get update && \
    apt-get install -y default-libmysqlclient-dev && \
    rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy C server files
COPY server1.c .
COPY server2.c .

# Compile both servers
RUN gcc -o server1 server1.c -lmysqlclient -lpthread
RUN gcc -o server2 server2.c -lmysqlclient -lpthread

# Default command (will be overridden by docker-compose)
CMD ["./server1"]
