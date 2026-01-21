-- Create database and table
CREATE DATABASE IF NOT EXISTS itt440_db;
USE itt440_db;

-- Create table exactly as required
CREATE TABLE IF NOT EXISTS user_points (
    user VARCHAR(50) PRIMARY KEY,
    points INT DEFAULT 0,
    datetime_stamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- Insert data for all 5 users
INSERT INTO user_points (user, points) VALUES 
('ahmad', 0),
('faris', 0),
('fitri', 0),
('lubawi', 0)
ON DUPLICATE KEY UPDATE points = VALUES(points);