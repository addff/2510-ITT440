FROM python:3.9-slim

# Set working directory
WORKDIR /app

# Copy requirements file
COPY requirements.txt .

# Install dependencies
RUN pip install --no-cache-dir -r requirements.txt

# Copy server scripts
COPY server1.py .
COPY server2.py .
COPY server3.py .

# Expose ports (will be overridden by docker-compose)
EXPOSE 5001 5002 5003

# Default command (will be overridden by docker-compose)
CMD ["python", "server1.py"]
