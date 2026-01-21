FROM ubuntu:20.04

# Set timezone to Kuala Lumpur
ENV TZ=Asia/Kuala_Lumpur
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install dependencies including timezone data
RUN apt-get update && apt-get install -y \
    gcc \
    libc6-dev \
    tzdata \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY client.c .

# Compile
RUN gcc -Wall -Wextra -g -o client client.c

# Run client
CMD ["./client"]