function [D,blocks] = compute_color_features ( I, szBlock, nBins, imgpath,iscolor)
%   COMPUTE_COLOR_FEATURES computes the color histogram for image blocks
%
%   Firstly, it divides the image into blocks
%   Each block is extracted a color histogram with nBins
%   The output features is stored in D
%   Finally, it stores blocks into individual image files for further visualization
%
%   INPUT
%       I - input image (satellite image)
%       szBlock - the size for block
%       nBins - number of bins in a histogram
%       imgpath - the directory to store block images
%
%   OUTPUT
%       D - features output nBlocks x nBins
J = I;
if ndims(I) ~= 2 && nargin < 5
    J = rgb2gray(I);
end

nBlocksY = floor(size(J,1)/szBlock(1));
nBlocksX = floor(size(J,2)/szBlock(2));

thumbnail_ratio  =.25;
block_thumbnail = szBlock*thumbnail_ratio;
% Here we try the WLD descriptor
C = 30; % nb of excitation levels
T = 8; % nb of excitation levels
M = 6; % nb of excitation levels

% D = zeros(nBlocksY*nBlocksX,nBins*3); %for grayscale histogram
D = zeros(nBlocksY*nBlocksX,C*T*3);
blocks = zeros(nBlocksY*nBlocksX,block_thumbnail(1)*block_thumbnail(2)*3);

count = 1;

for y = 1:nBlocksY
    for x = 1:nBlocksX
        left = (x - 1) * szBlock(2) + 1;
        top = (y - 1) * szBlock(1) + 1;
        right = left + szBlock(2) - 1;
        bottom = top + szBlock(1) - 1;
       
        block = J(top:bottom,left:right,:);   % extract the block
%         D(count,1:nBins) = imhist(block(:,:,1),nBins)/(szBlock(1)*szBlock(2));   % save it as thumbnail
%         D(count,nBins+1:2*nBins) = imhist(block(:,:,2),nBins)/(szBlock(1)*szBlock(2));   % save it as thumbnail
%         D(count,2*nBins+1:end) = imhist(block(:,:,3),nBins)/(szBlock(1)*szBlock(2));   % save it as thumbnail
        
%         D(count,:) = WLD(block,C,T,M);
        D(count,1:C*T) = WLD(block(:,:,1),C,T,M);
        D(count,C*T+1:2*C*T) = WLD(block(:,:,2),C,T,M);
        D(count,2*C*T+1:end) = WLD(block(:,:,3),C,T,M);
        
        block = imresize(block,thumbnail_ratio);
        % draw  thumbnail border
        block(:,1,1) = 255;
        block(:,end,1) = 255;
        block(1,:,1) = 255;
        block(end,:,1) = 255;
        
        block(:,1,2) = 255;
        block(:,end,2) = 255;
        block(1,:,2) = 255;
        block(end,:,2) = 255;
        
        block(:,1,3) = 255;
        block(:,end,3) = 255;
        block(1,:,3) = 255;
        block(end,:,3) = 255;
        
        
        blocks(count,:) = reshape(block, 1, []);
        
%         if strcmp ( imgpath, '' ) ~= 1
%             block_name = sprintf ('%d', count);
%             imwrite (block, [imgpath '/' block_name '.png']);
%         end
        
        count = count + 1;
    end
end

