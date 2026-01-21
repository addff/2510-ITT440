# Use a Python base image
FROM python:3.11-slim

# Install system dependencies for MySQL connectors
RUN apt-get update && apt-get install -y \
    gcc \
    python3-dev \
    default-libmysqlclient-dev \
    && rm -rf /var/lib/apt/lists/*

# Upgrade pip
RUN pip install --upgrade pip setuptools wheel

# Install MySQL connector (pure Python)
RUN pip install mysql-connector-python

COPY client.py /app/client.py
WORKDIR /app

CMD ["python", "client.py"]

# Or if you prefer the C-based driver
# RUN pip install mysqlclient