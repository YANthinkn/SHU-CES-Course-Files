function [U,D,V] = SVD_my(A)
[m,n] = size(A);

D = zeros(m,n);
V = zeros(n,n);

W = A'*A;
[ve,de] = eig(W);
dd = diag(de);
[dd,index] = sort(dd,1,'descend') ;
V = ve(:,index);
D(1:n,1:n) = diag(sqrt(dd));

%%% U
pnum = sum(dd>0);
%U(:,1:pnum) = A*V(:,1:pnum)./repmat(sqrt(dd(1:pnum))',m,1);
U(:,1:pnum) = A*V(:,1:pnum)*(inv(D(1:pnum,1:pnum)));
T = null(A');
U = [U T];

end