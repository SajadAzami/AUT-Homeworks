%% Question 2: Approximation of an image using Sigular Value Decomposition
clear;
input_image = imread('image_test.jpg');
input_image = rgb2gray(input_image);
input_image_double = double(input_image);
fileinfo = dir('image_test.jpg');
original_size = fileinfo(1).bytes;
image(svd_approximator(input_image_double, original_size));
