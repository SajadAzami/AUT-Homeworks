function [ image ] = image_read( address )
%IMAGE_READ reads image from address
image = imread(address);
image = imresize(image, 0.5); % Reduce to 0.25 if needed
image = rgb2gray(image);
image = im2double(image);
end
