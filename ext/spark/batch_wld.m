function f = batch_wld(dirpath,filelist,nchannels,C,T,M)

if nargin < 4
    C = 30;
end

if nargin < 5
    T = 8;
end

if nargin < 6
    M = 6;
end

f = zeros(length(filelist),nchannels*C*T);

for i=1:length(filelist)
    
    if mod(i,50) == 0
        fprintf('%f processed...\n',i/length(filelist)*100);
    end
    
    I = imread(fullfile(dirpath,strcat(filelist{i},'.tif')));
    if ndims(I) ~= nchannels && nchannels == 3
        error '3-channel image is required!';
    end
    
    f(i,1:C*T) = WLD(I(:,:,1),C,T,M);
    
    if nchannels == 3
        f(i,C*T+1:2*C*T) = WLD(I(:,:,2),C,T,M);
        f(i,2*C*T+1:end) = WLD(I(:,:,3),C,T,M);
    end
end