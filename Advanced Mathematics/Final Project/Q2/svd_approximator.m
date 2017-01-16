function [ approximated_image ] = svd_approximator( input_image )
%SVD_APPROXIMATOR Approximates an Image by given rank using SVD
rank = 50;
[U,S,V]=svd( input_image );
dispEr = [];
numSVals = [];

for rank = [ 5, 20 ]
    C = S;
    C(rank + 1:end, :) = 0;
    C(:, rank + 1:end) = 0;
    % Reconstruct Image
    approximated_image = U*C*V';
    
    figure;
    title_text = sprintf('Rank %d Approximation', rank);
    imshow(uint8( approximated_image ));
    title( title_text );
    error=sum(sum((input_image-approximated_image).^2));

    % store vals for display
    dispEr = [dispEr; error];
    numSVals = [numSVals; rank];

end
disp(dispEr);
disp(numSVals);
% dislay the error graph
figure;
plot(numSVals, dispEr);
%figure(5); 
%title('Error in compression');
%plot(numSVals, dispEr);
%grid on
%xlabel('Number of Singular Values used');
%ylabel('Error between compress and original image');

end
