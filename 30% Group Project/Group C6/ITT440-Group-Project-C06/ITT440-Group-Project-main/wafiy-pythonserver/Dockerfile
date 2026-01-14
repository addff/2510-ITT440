FROM python:3.10-slim

WORKDIR /app

COPY wafiyserver.py .

RUN apt-get update && apt-get install -y \
    build-essential \
    libssl-dev \
    libffi-dev \
    python3-dev \
 && rm -rf /var/lib/apt/lists/*

RUN pip install --no-cache-dir mysql-connector-python

EXPOSE 8080

CMD ["python", "-u", "wafiyserver.py"]
