%% Question 3 (Bonus): Face Recognition With Singular Value Decomposition
clear;
% Load Dataset
input_image = image_read(strcat('data_set/train/', '1.jpg'));

% Size of each image
M  = size(input_image(), 1) * size(input_image, 2);

% Number of individuals
N = 19; 

% Creating the train data matrix
S = zeros(M, N); 
for i = 1:N
temp = image_read(sprintf('data_set/train/%d.jpg', i));
S(:, i) = temp(:);
end

% Computing the mean image of train data
train_mean = mean(S, 2);

% Normalizing images by subtracting mean
S = S - train_mean(:, ones(1, N));

% Performing the Singular Value Decomposition over A
[u, s, v] = svd(S);
rank = size(s, 2);

% Computing coorinate vector xi for each known individual
xi = u(:, 1:N)' * A;

% Choosing thresholds
epsilon_0 = 180; % Maximum allowable distance from any known face in the training set S
epsilon_1 = 9; % Maximum allowable distance from face space

% Classification
epsilon_i = zeros(N, 1);
test_image = image_read('data_set/2/9338535.19.jpg');
test_image = test_image(:) - train_mean; % Normalizing test image
x = u(:, 1:N)' * test_image; % Calculating coordinate vector x
tmp = test_image - u(:, 1:N) * x;
epsilon_f = (tmp' * tmp) ^ .5;

if epsilon_f < epsilon_1
    for j = 1:N
        tmp = xi(:, j) - x;
        epsilons(j, 1) = tmp' * tmp;
    end
    if min(epsilons(:, 1)) < epsilon_0
        disp('');
    end
else
    disp('Input image is not a face');
end