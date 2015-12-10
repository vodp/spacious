%% Example
%
% gen_spacdata('..',...
%               '128955',...
%               {'hog'},...
%               64,...
%               '/data/vo/mlis/dat/images_cnes/000000128955_01_P001_MUL.png',...
%               '/data/vo/mlis/dat/images_cnes/000000128955_01_P001-BROWSE.png',...
%               'images',...
%               '/data/vo/mlis/dat/images_cnes/000000128955_01_P001_MUL/features',...
%               '/home/vo/spacious-0.2/src/spacious',...
%               'LLE',...
%               6,12,'Matlab');
%
% NOTICE
%  Spacious can just load PNG files.
function gen_spacdata2(...
    dirpath,... % where to put the data
    dirname,... % name of the data
    features,...% chosen features (a subset of Venise features)
    patch_size,...% the dimension of the patch
    mapfile,... % the fullpath of satellite image file (in RGB colorspace)
    prevfile,...% the fullpath of tiny version of the satellite image used for preview
    texturedir,...% the directory will contains .sgi texture patches
    datadir,...% the fullpath of directory contains feature files (output of Venise)
    binfile,... % the fullpath to the executable file of Spacious
    dralg,...
    varargin) % additional parameters for DRTOOLBOX

addpath(genpath('../'));
mkdir(fullfile(dirpath,dirname));
mkdir(fullfile(dirpath,dirname,'data'));

% load texture/feature list
filelist = textread(fullfile(datadir,'list.txt'),'%s');
if isempty(filelist)
    disp 'empty directory';
    return;
end

if isempty(features)
    disp 'none of features chosen';
    return;
end

% load features
disp 'Step 1/6. Loading features...';
if (~exist(fullfile(dirpath,dirname,strcat(dirname,'.mat')),'file'))
    % load features generated by VenisePreprocessing
    [histo,flusser,haralick,fmellin,hog] = load_venisefeatures(datadir,filelist);
    % compute WLD too
    wld = batch_wld(datadir,filelist,3);
    save(fullfile(dirpath,dirname,strcat(dirname,'.mat')),'histo','flusser','haralick','fmellin','hog','wld');
else
    for i=1:length(features)
        load(fullfile(dirpath,dirname,strcat(dirname,'.mat')),features{i});
    end
end

% convert TIF into SGI texture format
% but first check whether SGI's files already there
disp 'Step 2/6. Converting textures to SGI files...'
if (~exist(fullfile(dirpath,dirname,texturedir),'dir'))
    mkdir(fullfile(dirpath,dirname,texturedir));
    convert_patches(datadir,filelist,fullfile(dirpath,dirname,texturedir),filelist);
end

% learn the manifold mapping
disp 'Step 3/6. Learning embedding...'
%mapping = cell(1,length(features));
% concatenate
X = cell(1,length(features));
for i=1:length(features)
    X{i} = eval(features{i});
end

X = cell2mat(X);

switch dralg
    case {'Isomap','LandmarkIsomap','Laplacian','LaplacianEig',...
            'LaplacianEigen','LaplacianEigenmaps','LLE','ManifoldChart',...
            'ManifoldCharting','Charting','Chart','LLTSA','LMVU','LandmarkMVU',...
            'FastMVU','Conformal','ConformalEig','ConformalEigen','ConformalEigenmaps',...
            'CCA','MVU','LPP','NPE','KPCA','KernelPCA','LDA','FDA','NCA','PCA','KLM',...
            'SPCA','SimplePCA','PPCA','ProbPCA','EMPCA','FactorAnalysis','FA'}
        [mapping,map] = compute_mapping(zscore(X),dralg,varargin{:});
    otherwise
        mapping = compute_mapping(zscore(X),dralg,varargin{:});
        map = [];
end

% check if learning method lost some points
if ~isempty(map)
    filelist = filelist(map.conn_comp);
    patchids = map.conn_comp;
else
    patchids = 1:length(filelist);
end

% guess the grid size
info = imfinfo(mapfile);
ncols = floor(info.Width/patch_size);
nrows = floor(info.Height/patch_size);

% copy executable file into the directory
disp 'Step 4/6. Copying spacious executable file...'
system(['cp ' binfile ' ' fullfile(dirpath,dirname)],'-echo');

% extract the binary file name (without path)
[~,binname] = fileparts(binfile);

% generate colormap
disp 'Step 5/6. Generating colormap file...'
gen_cmapfile(fullfile(dirpath,dirname,'data'),strcat(dirname,'.cmap'));

% generate speck files
disp 'Step 6/6. Generating speck & config files...'

speckfname = strcat(dirname,'_',dralg,'_',features{:},'.speck');
gen_speckfile(...
    fullfile(dirpath,dirname,'data'),...
    speckfname,...
    mapping,...
    patchids,...
    filelist);

cffname = strcat(dirname,'_',dralg,'_',features{:},'.cf');
gen_cffile(...
    fullfile(dirpath,dirname,'data'),...
    cffname,...
    mapping,...
    [ncols nrows],...
    speckfname,...
    strcat(dirname,'.cmap'),...
    mapfile,...
    prevfile,...
    texturedir);

fid = fopen(fullfile(dirpath,dirname,strcat(dirname,'_',dralg,'_',features{:},'.csh')),'wt');
fprintf(fid,'chmod +x %s; ',binname);
fprintf(fid,'./%s data/%s',binname,cffname);
fclose(fid);
system(['chmod +x ',fullfile(dirpath,dirname,strcat(dirname,'_',dralg,'_',features{:},'.csh'))]);


disp '...Finished.';
