USE MusicShop;

# Queries
# 1. show classic genre musics in an increasingly sorted by cost
SELECT Album.*
FROM Album
  NATURAL JOIN AlbumGenres
  NATURAL JOIN Genre
WHERE 'Classic' = genre_name
ORDER BY price;

# 2. show rock genre musics decreasingly sorted by their rank
SELECT
  Track.*,
  AVG(rate)
FROM Comment
  NATURAL JOIN Track
  NATURAL JOIN TrackGenres
  NATURAL JOIN Genre
WHERE genre_name = 'Classic'
ORDER BY track_id;

# 3. show all tracks that have been rated more than 9 in all ratings
SELECT User.*
FROM Comment
  NATURAL JOIN Track
  NATURAL JOIN User
WHERE track_id IN (SELECT Track.track_id
                   FROM Track
                     NATURAL JOIN Comment
                   WHERE rate > 9);

# 4. show sorted list of artists by how many genres they have worked
SELECT Artist.*
FROM Artist
  NATURAL JOIN ArtistGenres
ORDER BY genre_id;

# 5. show artists that haven't composed track without album
SELECT DISTINCT Artist.*
FROM Artist
  NATURAL JOIN Composes
  NATURAL JOIN Track
WHERE NOT EXISTS(SELECT *
                 FROM Album
                 WHERE album_id IS NULL);

# 6. show artists that haven't composed track without album
SELECT DISTINCT Artist.*
FROM Artist
  NATURAL JOIN Composes
  NATURAL JOIN Track
WHERE EXISTS(SELECT *
             FROM Composes, (SELECT
                               count(artist_id) AS cnt,
                               artist_id
                             FROM Composes
                             GROUP BY artist_id) AS tmp
             WHERE cnt > 3);

# 7. show genres and count of all the orders from that genre
SELECT
  Genre.genre_name,
  count(genre_id)
FROM Track
  NATURAL JOIN TrackGenres
  NATURAL JOIN Genre
  NATURAL JOIN `Order`
GROUP BY genre_id;

