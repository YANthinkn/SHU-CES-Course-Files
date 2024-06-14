function B= InverseMatrix (A)
[m,n] = size(A);
if m~=n
    disp('A is not a square matrix');
    return
end
if rank(A) < n
    disp('A is not a full rank matrix');
    return
end
C = [A ;eye(n)];
% Loop over the entire matrix.
i = 1;
j = 1;

while j <= n
   % Find value and index of largest element in the remainder of row i.
   [p,k] = max(abs(C(i,j:n))); k = k+j-1;  
   %%%%注意代码并没有考虑A接近奇异情况，即p很小，这时求逆误差很大  
   %%%%数值计算中，除非是整形，否则不太可能出现一个变量等于零，而是小于某个很小的数eps就认为该变量等于零。
   %%%%eps的选取和所讨论的问题的数量级有关系，比如图像数量范围0-255，则eps可取10^-3，而有些问题数值范围在
   %%%%10^-3次的时候，eps可能就要取10^-9.除法一定不能除0,
   %有时候不方便判断一个矩阵A里面哪些数可能接近于0，而又要求不太严格的时候，则可利用1./(A+eps)近似1./A
   % Swap i-th and k-th columns.
   C(i:end,[j, k]) = C(i:end,[k j]);
   % Divide the pivot column by the pivot element.
   C(i:end,j) = C(i:end,j)/C(i,j);
   % Subtract multiples of the pivot column from all the other columns.
   for k = [1:j-1 j+1:n]
      C(i:end,k) = C(i:end,k) - C(i,k)*C(i:end,j);
   end
   i = i + 1;
   j = j + 1;   
end
B = C(n+1:end,:);
end


