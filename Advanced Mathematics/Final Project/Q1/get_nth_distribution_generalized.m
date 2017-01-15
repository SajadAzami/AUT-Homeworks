function [ nth_distribution ] = get_nth_distribution_generalized( transition, today, n )
%GET_NTH_TRANSITION Calculating N-th distribution vector for a Markov Chain
%and Initialization
nth_distribution = today;
for k = 1:n
    nth_distribution = transition * nth_distribution;
end
end
