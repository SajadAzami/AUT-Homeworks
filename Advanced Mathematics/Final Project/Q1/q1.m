%% Question 1.A: Calculating N-th Distribution Matrix for a Markov Chain
transition_matrix = [ 0.4 0.3 0.1 ; 0.4 0.3 0.6 ; 0.2 0.4 0.3 ];
today = [ 0 ; 1 ; 0 ];
disp( get_nth_distribution(transition_matrix, today, 2) );
%% Question 1.B: 

%% Question 1.C