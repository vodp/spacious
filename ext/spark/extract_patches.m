function blocks = extract_patches ( I, szBlock)
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
% if ndims(I) ~= 2 && nargin < 5
%     J = rgb2gray(I);
% end

nBlocksY = floor(size(J,1)/szBlock(1));
nBlocksX = floor(size(J,2)/szBlock(2));

thumbnail_ratio  =1;
block_thumbnail = szBlock*thumbnail_ratio;

% D = zeros(nBlocksY*nBlocksX,nBins*3); %for grayscale histogram
blocks = zeros(nBlocksY*nBlocksX,block_thumbnail(1)*block_thumbnail(2)*3);

count = 1;

for y = 1:nBlocksY
    for x = 1:nBlocksX
        left = (x - 1) * szBlock(2) + 1;
        top = (y - 1) * szBlock(1) + 1;
        right = left + szBlock(2) - 1;
        bottom = top + szBlock(1) - 1;
       
        block = J(top:bottom,left:right,:);   % extract the block       
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
        count = count + 1;
    end
end

