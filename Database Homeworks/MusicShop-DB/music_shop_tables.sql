CREATE DATABASE MusicShop;

USE MusicShop;


############### Includes information about tracks ###############
CREATE TABLE `Track` (
  `track_id`   INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
  `album_id`   INT             NOT NULL,
  `track_name` VARCHAR(32)     NOT NULL
);
ALTER TABLE `Track`
  COMMENT = 'Includes information about tracks';

############### Includes information about albums ###############
CREATE TABLE `Album`
(
  `album_id`   INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
  `album_name` VARCHAR(32)     NOT NULL,
  `price`      INT             NOT NULL,
  `year`       DATE            NOT NULL
);
ALTER TABLE `Album`
  COMMENT = 'Includes information about albums';

############### Includes information about artists ###############
CREATE TABLE `Artist`
(
  `artist_id`   INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
  `artist_name` VARCHAR(32)     NOT NULL,
  `description` VARCHAR(32)     NOT NULL
);
ALTER TABLE `Artist`
  COMMENT = 'Includes information about artists';

############### Includes information about comments ###############
CREATE TABLE `Comment`
(
  `comment_id` INT         NOT NULL AUTO_INCREMENT,
  `user_id`    VARCHAR(32) NOT NULL,
  `rate`       INT(1)      NOT NULL,
  `comment`    VARCHAR(32) NOT NULL,
  `track_id`   INT         NOT NULL,
  PRIMARY KEY (comment_id, track_id)
);
ALTER TABLE `Comment`
  COMMENT = 'Includes information about comments';

############### Includes information about composes ###############
CREATE TABLE `Composes`
(
  `track_id`  INT NOT NULL,
  `artist_id` INT NOT NULL,
  PRIMARY KEY (track_id, artist_id)
);
ALTER TABLE `Composes`
  COMMENT = 'Includes information about composer';

############### Includes information about order ###############
CREATE TABLE `Order`
(
  `track_id` INT NOT NULL,
  `user_id`  INT NOT NULL,
  `order_id` INT NOT NULL,
  PRIMARY KEY (track_id, user_id, order_id)
);
ALTER TABLE `Order`
  COMMENT = 'Includes information about order';

############### Includes information about order ###############
CREATE TABLE `Orders`
(
  `user_id`  INT NOT NULL,
  `order_id` INT NOT NULL,
  PRIMARY KEY (user_id, order_id)
);
ALTER TABLE `Orders`
  COMMENT = 'Includes information about orders';

############### Includes information about genres ###############
CREATE TABLE `Genre`
(
  `genre_id`   INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
  `genre_name` VARCHAR(32)     NOT NULL
);
ALTER TABLE `Genre`
  COMMENT = 'Includes information about genres';

############### Includes information about which track is in which genre ###############
CREATE TABLE `TrackGenres`
(
  `track_id` INT         NOT NULL,
  `genre_id` VARCHAR(32) NOT NULL,
  PRIMARY KEY (track_id, genre_id)
);
ALTER TABLE `TrackGenres`
  COMMENT = 'Includes information about which track is in which genre';

############### Includes information about which album is in which genre ###############
CREATE TABLE `AlbumGenres`
(
  `album_id` INT         NOT NULL,
  `genre_id` VARCHAR(32) NOT NULL,
  PRIMARY KEY (album_id, genre_id)
);
ALTER TABLE `AlbumGenres`
  COMMENT = 'Includes information about which album is in which genre';

############### Includes information about which artist is in which genre ###############
CREATE TABLE `ArtistGenres`
(
  `artist_id` INT         NOT NULL,
  `genre_id`  VARCHAR(32) NOT NULL,
  PRIMARY KEY (artist_id, genre_id)
);
ALTER TABLE `ArtistGenres`
  COMMENT = 'Includes information about which artist is in which genre';

############### Includes information about users ###############
CREATE TABLE `User`
(
  `user_id`   INT PRIMARY KEY NOT NULL,
  `user_name` VARCHAR(32)     NOT NULL,
  `password`  VARCHAR(32)     NOT NULL
);
ALTER TABLE `User`
  COMMENT = 'Includes information about users';

