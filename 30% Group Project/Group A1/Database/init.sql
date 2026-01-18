-- Create database
CREATE DATABASE IF NOT EXISTS network_project;
USE network_project;

-- Create user tracking table
CREATE TABLE IF NOT EXISTS user_tracking (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user VARCHAR(100) NOT NULL UNIQUE,
    points INT DEFAULT 0,
    datetime_stamp DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- Insert initial user records
INSERT INTO user_tracking (user, points, datetime_stamp) 
VALUES 
    ('Afif', 0, NOW()),
    ('Syahmi', 0, NOW()),
    ('Irfan', 0, NOW()),
    ('Hairiel', 0, NOW()),
    ('Faiz', 0, NOW())
    ('Sir', 0, NOW())
ON DUPLICATE KEY UPDATE user=user;
