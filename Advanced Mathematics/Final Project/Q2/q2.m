%% Question 2: Approximation of an image using Sigular Value Decomposition
input_image = imread('image_test.jpg');
input_image = rgb2gray(input_image);
input_image_double = double(input_image);
image(svd_approximator(input_image_double));
