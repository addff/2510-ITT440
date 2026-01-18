FROM python:3.9-slim

# Set working directory
WORKDIR /app

# Copy requirements file
COPY requirements.txt .

# Install dependencies (if any)
RUN pip install --no-cache-dir -r requirements.txt

# Copy client scripts
COPY client1.py .
COPY client2.py .
COPY client3.py .

# Default command (will be overridden by docker-compose)
CMD ["python", "client1.py"]
