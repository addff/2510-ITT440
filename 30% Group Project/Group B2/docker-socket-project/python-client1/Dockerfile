FROM python:3.9-slim

WORKDIR /app

COPY client1.py .
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

#CMD ["sleep", "15"]  # Wait for servers to start
#CMD ["sh", "-c", "while true; do sleep 3600; done"]
#ENTRYPOINT ["python", "client1.py"]
CMD ["tail", "-f", "/dev/null"]
