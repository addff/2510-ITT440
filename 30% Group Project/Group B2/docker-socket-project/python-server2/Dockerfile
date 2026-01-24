FROM python:3.9-slim

WORKDIR /app

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY server2.py .

EXPOSE 8085

CMD ["python", "server2.py"]
