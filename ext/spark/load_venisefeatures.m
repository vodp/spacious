function [histo,flusser,haralick,fmellin,hog] = load_venisefeatures(dirpath,filelist)

histo = zeros(length(filelist),100);
flusser = zeros(length(filelist),11);
haralick = zeros(length(filelist),8);
fmellin = zeros(length(filelist),16);
hog = zeros(length(filelist),90);

for i=1:length(filelist)
    if mod(i,100) == 0
        disp(strcat(num2str(i),'/',num2str(length(filelist))));
    end
    
    fid = fopen(fullfile(dirpath,strcat(filelist{i},'.txt')),'r');
    
    vec = textscan(fid,'%f');
    vec = vec{1,1};
    histo(i,:) = vec(1:100);
    flusser(i,:) = vec(101:111);
    haralick(i,:) = vec(112:119);
    fmellin(i,:) = vec(120:135);
    hog(i,:) = vec(136:end);

    fclose(fid);
end
