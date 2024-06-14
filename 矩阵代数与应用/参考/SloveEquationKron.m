function X = SloveEquationKron(A,B,D)
[m,p] = size(A);
[q,n] = size(B);
[m,n] = size(D);

C=zeros(n*m,q*p);
% Loop over the entire matrix.
BT = B';
for i = 1:n
    for j=1:q
        C((i-1)*m+1:(i-1)*m+m,(j-1)*p+1:(j-1)*p+p) = BT(i,j)*A;
    end
end
XX = C\D(:);
X = reshape(XX,[p,q]);
end