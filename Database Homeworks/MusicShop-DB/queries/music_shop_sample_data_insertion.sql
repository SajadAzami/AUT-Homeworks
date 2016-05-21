USE MusicShop;

INSERT INTO `Album` VALUES (1, 'Album1', 3000, 20121010);
INSERT INTO `Album` VALUES (2, 'Album2', 5000, 20130810);


INSERT INTO `User` VALUES (1, 'User1', 'password1');
INSERT INTO `User` VALUES (2, 'User2', 'password2');


INSERT INTO `Track` VALUES (1, 1, 'Track1FromAlbum1');
INSERT INTO `Track` VALUES (2, 1, 'Track2FromAlbum1');
INSERT INTO `Track` VALUES (3, 2, 'Track1FromAlbum2');
INSERT INTO `Track` VALUES (4, 2, 'Track2FromAlbum2');


INSERT INTO `Artist` VALUES (1, 'Artist1', 'Artist Description 1');
INSERT INTO `Artist` VALUES (2, 'Artist2', 'Artist Description 2');


INSERT INTO `Composes` VALUES (1, 1);
INSERT INTO `Composes` VALUES (2, 1);
INSERT INTO `Composes` VALUES (3, 2);
INSERT INTO `Composes` VALUES (4, 2);


INSERT INTO `Orders` VALUES (1, 1);


INSERT INTO `Order` VALUES (1, 1, 1);
INSERT INTO `Order` VALUES (2, 1, 1);
INSERT INTO `Order` VALUES (3, 1, 1);


INSERT INTO `Genre` VALUES (1, 'Classic');
INSERT INTO `Genre` VALUES (2, 'Rock');
INSERT INTO `Genre` VALUES (3, 'Rap');


INSERT INTO `TrackGenres` VALUES (1, 1);
INSERT INTO `TrackGenres` VALUES (2, 3);
INSERT INTO `TrackGenres` VALUES (3, 2);
INSERT INTO `TrackGenres` VALUES (4, 1);


INSERT INTO `AlbumGenres` VALUES (1, 1);
INSERT INTO `AlbumGenres` VALUES (2, 1);


INSERT INTO `ArtistGenres` VALUES (1, 1);
INSERT INTO `ArtistGenres` VALUES (2, 3);


INSERT INTO `Comment` VALUES (1, 1, 8, 'This is comment description 1', 1);
INSERT INTO `Comment` VALUES (1, 1, 7, 'This is comment description 2', 2);
