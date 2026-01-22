FROM python:3.9

ARG SERVER_FILE

RUN pip install mysql-connector-python

WORKDIR /app

# Use the build argument
COPY ${SERVER_FILE} server.py

CMD ["python", "-u", "server.py"]
# CMD ["tail", "-f", "/dev/null"]