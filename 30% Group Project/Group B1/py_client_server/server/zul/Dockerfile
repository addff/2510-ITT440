FROM python:3.10.19-trixie
RUN pip install mysql-connector-python
WORKDIR /app
COPY zul_server.py .
EXPOSE 5003
CMD ["python3", "zul_server.py"]