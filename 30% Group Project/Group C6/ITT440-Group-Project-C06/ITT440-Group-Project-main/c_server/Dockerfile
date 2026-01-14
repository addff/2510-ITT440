FROM ubuntu:22.04

WORKDIR /app

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    default-libmysqlclient-dev \
    libmysqlclient-dev \
    && rm -rf /var/lib/apt/lists/*

# Copy C server source
COPY server.c .

# Compile
RUN gcc server.c -o server -lmysqlclient

# Expose port for client connections
EXPOSE 5003

# Run server
CMD ["./server"]
