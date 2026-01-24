FROM mysql:8.0
COPY init.sql /docker-entrypoint-initdb.d/
ENV MYSQL_ROOT_PASSWORD=rootpassword
ENV MYSQL_DATABASE=socket_db
EXPOSE 3306