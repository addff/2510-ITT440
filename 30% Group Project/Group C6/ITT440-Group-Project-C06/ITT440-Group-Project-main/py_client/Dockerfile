FROM python:3.10-slim

WORKDIR /app

COPY client.py .

RUN pip install mysql-connector-python

CMD ["python", "client.py"]
