USE MusicShop;

# Queries
# 1. show classic genre musics in an increasingly sorted by cost
SELECT Album.*
FROM Album
  NATURAL JOIN AlbumGenres
  NATURAL JOIN Genre
WHERE 'Classic' = genre_name
GROUP BY price;

# 2. show rock genre musics decreasingly sorted by their rank
SELECT
  Track.*
FROM Comment
  NATURAL JOIN Track
WHERE avg(rate)

