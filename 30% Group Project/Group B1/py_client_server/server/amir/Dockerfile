FROM python:3.10.19-trixie
RUN pip install mysql-connector-python
WORKDIR /app
COPY amir_server.py .
EXPOSE 5001
CMD ["python3", "amir_server.py"]