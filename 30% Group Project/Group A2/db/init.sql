CREATE DATABASE IF NOT EXISTS attendance_db;
USE attendance_db;

CREATE TABLE IF NOT EXISTS attendance (
  user VARCHAR(50) PRIMARY KEY,
  points INT NOT NULL DEFAULT 0,
  datetime_stamp DATETIME NOT NULL
);

INSERT IGNORE INTO attendance (user, points, datetime_stamp) VALUES
('student_c', 0, NOW()),
('student_py', 0, NOW());
