
USE assignmentdb;

CREATE TABLE IF NOT EXISTS points_table (
  user VARCHAR(50) PRIMARY KEY,
  points INT DEFAULT 0,
  last_update TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

INSERT INTO points_table (user, points, last_update)
VALUES ('user_py', 0, NOW())
ON DUPLICATE KEY UPDATE user=user;

INSERT INTO points_table (user, points, last_update)
VALUES ('user_c', 0, NOW())
ON DUPLICATE KEY UPDATE user=user;

CREATE USER IF NOT EXISTS 'py_server'@'%' IDENTIFIED BY 'pypass';
GRANT CREATE, INSERT, UPDATE, SELECT, DELETE ON assignmentdb.* TO 'py_server'@'%';

CREATE USER IF NOT EXISTS 'c_server'@'%' IDENTIFIED BY 'cpass';
GRANT CREATE, INSERT, UPDATE, SELECT, DELETE ON assignmentdb.* TO 'c_server'@'%';

FLUSH PRIVILEGES;