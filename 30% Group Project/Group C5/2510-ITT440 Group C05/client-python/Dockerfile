FROM python:3.9

ARG CLIENT_FILE

WORKDIR /app

# Use the build argument
COPY ${CLIENT_FILE} client.py

CMD ["python", "-u", "client.py"]
