function [ approximated_image ] = svd_approximator( input_image, original_size )
%SVD_APPROXIMATOR Approximates an Image by given rank using SVD
[U,S,V]=svd( input_image );
ranks_to_be_tested = [ 5 10 20 50 100 ];
compression_ratios = [];
errors = [];

for rank = ranks_to_be_tested
    % Fill other diagonal values with zeros
    C = S;
    C(rank + 1:end, :) = 0;
    C(:, rank + 1:end) = 0;
    
    % Reconstruct Image
    approximated_image = U*C*V';
    
    % Write the compressed image to file
    file_name = strcat(num2str(rank), '_approximation.jpg');
    imwrite(uint8( approximated_image ), file_name, 'jpg');
    
    % Calculate compressed image size and compression ratio
    fileinfo = dir(file_name);
    new_file_size = fileinfo(1).bytes;
    ratio = new_file_size / original_size;
    compression_ratios(end+1) = ratio;    
    
    % Plot the compressed image
    figure(rank);
    title_text = sprintf('Rank %d Approximation | Size: %d Bytes | Compression Ratio: %f', rank, new_file_size, ratio);
    imshow(uint8(approximated_image));
    title(title_text);
    
    % Compute MSE
    errors(end+1) = sum(sum((input_image - approximated_image).^2));

end
disp('-----------');
disp(ranks_to_be_tested);
disp('-----------');
disp(compression_ratios);
disp('-----------');
disp(errors);
end