FROM ubuntu:20.04

# Set timezone to Kuala Lumpur
ENV TZ=Asia/Kuala_Lumpur
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install dependencies
RUN apt-get update && apt-get install -y \
    gcc \
    libmysqlclient-dev \
    default-libmysqlclient-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY server.c .

# Compile server
RUN gcc -o server server.c -lmysqlclient

CMD ["./server"]