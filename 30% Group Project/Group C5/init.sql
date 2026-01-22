CREATE TABLE IF NOT EXISTS Star_point (
    user VARCHAR(50) PRIMARY KEY,
    points INT DEFAULT 0,
    datetime_stamp DATETIME DEFAULT CURRENT_TIMESTAMP
);

INSERT IGNORE INTO Star_point (user, points, datetime_stamp)
VALUES 
('c_Insyi', 0, NOW()),
('c_nadhrah_2', 0, NOW()),
('py_amni', 0, NOW()),
('py_ayu_1', 0, NOW());

