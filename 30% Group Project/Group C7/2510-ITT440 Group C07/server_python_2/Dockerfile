FROM python:3.9-slim
RUN pip install mysql-connector-python
WORKDIR /app
COPY server.py .
CMD ["python", "server.py"]
