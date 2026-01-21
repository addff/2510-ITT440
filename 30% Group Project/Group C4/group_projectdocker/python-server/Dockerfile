#FROM python:3.10
#WORKDIR /app
#COPY server.py .
#RUN pip install mysql-connector-python
#CMD ["python", "server.py"]

FROM python:3.11-slim

WORKDIR /app
COPY server.py .

# Install system dependencies required for building Python packages
RUN apt-get update && apt-get install -y \
    gcc \
    python3-dev \
    default-libmysqlclient-dev \
    && rm -rf /var/lib/apt/lists/*

# Upgrade pip to latest
RUN pip install --upgrade pip setuptools wheel

# Install MySQL connector
RUN pip install mysql-connector-python

CMD ["python", "server.py"]
