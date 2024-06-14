function B = InverseMatrixCramer (A)
[m,n] = size(A);
if m~=n
    disp('A is not a square matrix');
    return
end
if rank(A) < n
    disp('A is not a full rank matrix');
    return
end
% Loop over the entire matrix.
j = 1;
detA = det(A);
B = zeros(size(A));

while j <= n 
    b = zeros(n,1);
    b(j) = 1;    
    for i = 1 : n
        C = A;
        C(:,i) = b;
        B(i,j) = det(C)/detA;        
    end
    %%%B(:,j) = A\b;
    j = j + 1;   
end

end



