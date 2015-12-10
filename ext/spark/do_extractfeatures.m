DATA_HOME = '/data/vo/mlis/dat/images_cnes/052397518010_01_P001_MUL/features/';
featureList  = dir(DATA_HOME);

histogram = zeros(length(featureList)-2,100);
flusser = zeros(length(featureList)-2,11);
haralick = zeros(length(featureList)-2,8);
fmellin = zeros(length(featureList)-2,16);
hog = zeros(length(featureList)-2,90);
for i=1:length(featureList)-2
    i
    %fileName = [originaFeatureSpaceDir, '/', fileList{i}];   
    
    fid = fopen([DATA_HOME featureList(i+2).name],'r');
    
    vec = zeros(1,25);
    tmp = textscan(fid,'%s','delimiter',' ','endofline','\r\n');
    line1 = textscan(tmp{1,1}{1},'%s');
    for j=1:length(line1{1,1})-1
        vec(j) = str2double(line1{1,1}{1+j});
    end
    histogram(i,1:25) = vec;
    
    vec = zeros(1,25);
    line2 = textscan(tmp{1,1}{2},'%s');
    for j=1:length(line1{1,1})-1
        vec(j) = str2double(line2{1,1}{1+j});
    end
    histogram(i,26:50) = vec;
    
    vec = zeros(1,25);
    line3 = textscan(tmp{1,1}{3},'%s');
    for j=1:length(line1{1,1})-1
        vec(j) = str2double(line3{1,1}{1+j});
    end
    histogram(i,51:75) = vec;
    
    vec = zeros(1,25);
    line4 = textscan(tmp{1,1}{4},'%s');
    for j=1:length(line1{1,1})-1
        vec(j) = str2double(line4{1,1}{1+j});
    end
    histogram(i,76:100) = vec;
    
    vec = zeros(1,11);
    line5 = textscan(tmp{1,1}{5},'%s');
    for j=1:length(line5{1,1})-1
        vec(j) = str2double(line5{1,1}{1+j});
    end
    flusser(i,:) = vec;
    
    vec = zeros(1,8);
    line6 = textscan(tmp{1,1}{6},'%s');
    for j=1:length(line6{1,1})-1
        vec(j) = str2double(line6{1,1}{1+j});
    end
    haralick(i,:) = vec;
    
    vec = zeros(1,16);
    line7 = textscan(tmp{1,1}{7},'%s');
    for j=1:length(line7{1,1})-1
        vec(j) = str2double(line7{1,1}{1+j});
    end
    fmellin(i,:) = vec;
    
    vec = zeros(1,90);
    line8 = textscan(tmp{1,1}{8},'%s');
    for j=1:length(line8{1,1})-1
        vec(j) = str2double(line8{1,1}{1+j});
    end
    hog(i,:) = vec;

    fclose(fid);
end
