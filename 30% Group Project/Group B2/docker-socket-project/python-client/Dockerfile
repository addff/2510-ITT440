FROM python:3.9-slim

WORKDIR /app

COPY client.py .
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

#CMD ["sleep", "15"]  # Wait for servers to start
#ENTRYPOINT ["python", "client.py"]
CMD ["tail", "-f", "/dev/null"]
