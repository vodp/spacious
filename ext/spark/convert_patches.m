function convert_patches(INPATH,inlist,OUTPATH,outlist)

for i=1:length(inlist)
    if mod(i,1000) == 0
        disp(num2str(i));
    end
    I = imread(fullfile(INPATH,[inlist{i} '.tif']));
    
    I(:,1,1) = 255;
    I(:,end,1) = 255;
    I(1,:,1) = 255;
    I(end,:,1) = 255;
    
    I(:,1,2) = 255;
    I(:,end,2) = 255;
    I(1,:,2) = 255;
    I(end,:,2) = 255;
    
    I(:,1,3) = 255;
    I(:,end,3) = 255;
    I(1,:,3) = 255;
    I(end,:,3) = 255;
    
    sgiwrite(I,fullfile(OUTPATH,[outlist{i} '.sgi']));
end