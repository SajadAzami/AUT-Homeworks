%% Question 3 (Bonus): Face Recognition With Singular Value Decomposition
% Load one of images to work with sizes
input_image = image_read(strcat('data_set/train/', '1.jpg'));

% Number of individuals
N = 19; 
% Size of each image
M  = size(input_image(), 1) * size(input_image, 2);


% Creating the train data matrix
S = zeros(M, N); 
for i = 1:N
    temp = image_read(sprintf('data_set/train/%d.jpg', i));
    S(:, i) = temp(:);
end

% Computing the mean image of train data
train_mean = mean(S, 2);

% Normalizing images by subtracting mean
A = S - train_mean(:, ones(1, N));

% Performing the Singular Value Decomposition over A
[u, s, v] = svd(A);

% Computing coordinate vector xi for each known individual
rank = size(A, 2); 
xi = u(:, 1:rank)' * A;

% Defining thresholds, these values were defined by trial and error
epsilon_0 = 50; % Maximum allowable distance from any known face in the training set S
epsilon_1 = 15; % Maximum allowable distance from face space

% Classification
images = ['1' '2' '7' '13' '16' 'not_a_face' 'unknown1' 'unknown2' 'unknown3' ]; % Test Images Available
epsilons = zeros(N, 1);
test_image = image_read('data_set/test/not_a_face.jpg');
test_image = test_image(:) - train_mean; % Normalizing test image
x = u(:, 1:rank)' * test_image; % Calculating coordinate vector x of test image
epsilon_f = ((test_image - u(:, 1:rank) * x)' * (test_image - u(:, 1:rank) * x)) ^ 0.5;

% Checks if it is in face space
if epsilon_f < epsilon_1
    % Computing distance epsilon_i to the face space
    for i = 1:N
        epsilons(i, 1) = (xi(:, i) - x)' * (xi(:, i) - x);
    end
    [val idx] = min(epsilons(:, 1));
    if val < epsilon_0
        disp(sprintf('The face belongs to %d', idx));
    else
        disp('Unknown face');
    end
else
    disp('Input image is not a face');
end
