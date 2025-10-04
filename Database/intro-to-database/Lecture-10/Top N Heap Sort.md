Used to retrieve top N record for a given dataset based on some ordering criteria. used in SQL queries such as
ORDER BY column_name DESC LIMIT N;

This algorithm scans the dataset once and then finds the top N things without having to shuffle and merge data back and forth in multiple rounds 