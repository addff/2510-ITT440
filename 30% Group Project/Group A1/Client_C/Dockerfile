FROM gcc:latest

# Set working directory
WORKDIR /app

# Copy C client files
COPY client1.c .
COPY client2.c .

# Compile both clients
RUN gcc -o client1 client1.c
RUN gcc -o client2 client2.c

# Default command (will be overridden by docker-compose)
CMD ["./client1"]
