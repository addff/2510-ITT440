FROM python:3.9-slim

# Set timezone to Kuala Lumpur
ENV TZ=Asia/Kuala_Lumpur
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

WORKDIR /app

COPY client.py .

CMD ["python", "client.py"]