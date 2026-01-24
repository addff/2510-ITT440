CREATE TABLE IF NOT EXISTS user_points(
    id INT AUTO_INCREMENT PRIMARY KEY,
    user VARCHAR(50) NOT NULL,
    points INT DEFAULT 0,
    datetime_stamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    UNIQUE KEY unique_user (user)
);

INSERT INTO user_points (user, points) VALUES
('c_user', 0),
('c_user1', 0),
('c_user2', 0),
('python_user', 0),
('python_user1', 0),
('python_user2', 0)
ON DUPLICATE KEY UPDATE points = VALUES(points);