USE pointsdb;

CREATE TABLE IF NOT EXISTS points_table (
    user VARCHAR(50) PRIMARY KEY,
    points INT DEFAULT 0,
    datetime_stamp DATETIME
);

INSERT INTO points_table (user, points, datetime_stamp)
VALUES
('python_user', 0, NOW()),
('c_user', 0, NOW()),
('nazrin_user', 0, NOW()),
('FATHU_C', 0, NOW()),
('mirul_py_user', 0, NOW()),
('wafiy_user', 0, NOW()),
('nabil_user', 0, NOW())
ON DUPLICATE KEY UPDATE user=user;




