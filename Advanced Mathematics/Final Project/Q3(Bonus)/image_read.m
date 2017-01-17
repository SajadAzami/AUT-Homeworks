function [ image ] = image_read( address )
%IMAGE_READ reads image from address
image = imread(address);
image = rgb2gray(image);
image = im2double(image);
end
