function [R,r,s,E,ave_nearest] = analyzepoints (positions, center,fracpoints, blocksize)

% ANALPOINTS computes inner and outer radius of the sphere (centered at center) 
%[R,r,s] = analyzepoints (positions, center,fracpoints, blocksize)
%
% R is radius of smallest sphere containing at least a fraction fracpoints of the points 
% r is radius of largest sphere containing at most a fraction 1-fracpoints of the points 
% fracpoints is a real number between 0 and 1 inclusive
% positions is a N x K matrix
% center is a 1 x K matrix
% Also returns the radius of the sphere 
% Also returns the a representative value for the separation of a point from its nearest neighbor
%
% Computations are based only on the first 3 dimensions of positions

if nargin<2,center=[0 0 0];end
if nargin<3,fracpoints=1;end

R = 0;
r = 0;
s = 0;
[N,K] = size(positions);
if ~N,return;end

if K > 3
  positions = positions(:,1:3);
elseif K < 3       % shouldnt happen (already corrected)
  positions = horzcat(positions,zeros(size(positions,1),3-K));
end

if ~N
  return;
end  
AA = positions - repmat(center,N,1);
AA = (sum(AA.^2,2)).^.5;
AA = sort (AA);


R = AA(ceil(fracpoints*N));
r = AA(1+ceil((1-fracpoints)*N));

blocksize = 1000;


numsome = 100;
if N < numsome
  some=[1:N];
  numsome=N;
else
  some = round(1+(N-1)*rand(numsome,1));       % indices of some particles
end

% E is a numsome x q matrix with distances
% q is the number of nearest neighbors (of nonzero distance away) we wish to keep track of

q=5;

E = zeros(numsome,q);
if N<=blocksize
  F = L2_distance(positions(some,:)',positions');
  for n=1:numsome
    tmp = sort(F(n,:));
    tmp = tmp(tmp>0);
    if (length(tmp)>0)
      E(n,1:min(length(tmp),q)) = tmp(1:min(q,length(tmp)));
    end
  end
else
  numblocks = ceil(N/blocksize);
  for i = 1 : numblocks
    b1 = (i-1)*blocksize + 1;
    b2 = min(N,i*blocksize);
    F = L2_distance (positions(some,:)',positions(b1:b2,:)');     % E is length(some) x length(b1:b2)

    for n=1:numsome
      tmp = sort([E(n,:), F(n,:)]);
      tmp = tmp(tmp>0);
      if (length(tmp)>0)
        E(n,1:min(length(tmp),q)) = tmp(1:min(q,length(tmp)));
      end
    end
  end
end

ave_nearest_q = mean(E,2);         % numsome x 1 vector with the distance of the q nearest nbrs to the numsome randomly chosen points

ave_nearest = sort(ave_nearest_q);         % now these distances are in increasing order
s = ave_nearest(ceil(0.05*numsome));



