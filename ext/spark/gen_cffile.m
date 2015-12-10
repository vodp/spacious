function gen_cffile(filepath,filename,Xnd,gridsize,speckfile,cmapfile,mapfile,prevfile,texturedir)

SCREENSIZE = [1024 768];
WINSIZE = 0;          % Use if you want this to be a certain winsize

GLYPHSIZE = 1;    % factor by which you want to multiply glyphs
MAXGLYPHSIZE = 1; % factor by which you want to multiply maximum glyph size 
LABELSIZE = 1;    % factor by which you want to multiply label sizes

fid = fopen(fullfile(filepath,filename),'wt');

fprintf(fid,['filepath +:.:../images:./images:./data:' texturedir '\n']);

uselogaxes = 0;
psize = 10;
ptsizemin = 1; 
ptsizemax = 5;
slum=1;
polyminmin = 0.1;
polysize = -1;  % to be changed
lsize = 0.05/4;             % normalized later on... was 0.05
labelmin = -10;            % was 2
clipnear = 1;      
clipfar = 1e8;
fov = 45;
eyeseparation = 0.005;   % for geowall, isnt used otherwise
polycansee = 3;             % the length of the smallest square polygon that can be seen (if textures are used)
pointscansee = 1;   
polyminmax = min(64,polycansee * 8) * MAXGLYPHSIZE;
lumest = 1;


if (length(SCREENSIZE)>=1)
  winsize_numcols = SCREENSIZE(1);
end
if (length(SCREENSIZE)>=2)
  winsize_numrows = SCREENSIZE(2);
end

% radius of sphere centered at (0,0,0) containing all points
[R,r,s] = analpoints2 (Xnd(:,1:3), mean(Xnd(:,1:3)) , 0.95); 
if ~R
   R = 1;         % probably no data
end
if ~r
  r = R/10;
end
if ~s
  s = R/100;
end

clipnear = r/10; % min (opts.clipnear,r/10);
clipfar = R*500; % max (opts.clipfar,R*5);              % change to deal with different fields of view
polysize = (s/2) * GLYPHSIZE ; 

THATCONST = (1/tan(fov*pi/360)) * atan (pointscansee * tan(fov*pi/(360*winsize_numrows)));
numpointsseeatonce = winsize_numrows / pointscansee;
psize = 1000 * numpointsseeatonce*s*THATCONST;


% We should implement group-data here,...
fprintf(fid,'\nobject g1=g1\n');
fprintf(fid,'  include %s\n', speckfile);
fprintf(fid,'eval psize %0.10f\n',psize);
fprintf(fid,'eval ptsize %0.10f %0.10f\n',ptsizemin,ptsizemax);
fprintf(fid,'eval polylumvar onescol radius\n');

fprintf(fid,'eval lum const %0.10f\n',lumest);
fprintf(fid,'eval poly on\n');
fprintf(fid,'eval points off\n');
fprintf(fid,'eval polysides 4\n');
fprintf(fid,'eval textures on\n');
fprintf(fid,'eval polymin %0.10f %0.10f\n',polyminmin,polyminmax);
fprintf(fid,'eval polysize %0.10f\n',polysize);
fprintf(fid,'eval alpha %0.3f\n',1);
fprintf(fid,'eval cmap %s\n',cmapfile);
%fprintf(fid,'eval color %d\n',offset);
fprintf(fid,'eval focalpoint on\n');
fprintf(fid,'eval fov %0.10f\n',fov);
fprintf(fid,'eval clip %0.10f %0.10f\n',clipnear,clipfar);
fprintf(fid,'eval censize %0.10f\n',10^floor(log10(R)));
fprintf(fid,'eval jump 0 0 %0.10f\n',1.5*R/tan(fov*pi/360));
fprintf(fid,'eval home 0 0 %0.10f\n',1.5*R/tan(fov*pi/360));
fprintf(fid,'eval stereo %0.10f off\n',-1*min(r,1)*eyeseparation);
fprintf(fid, 'eval grid %d %d\n',gridsize(1),gridsize(2));
fprintf(fid, 'eval imread %s\n',mapfile);
fprintf(fid, 'eval previmread %s\n',prevfile);
fprintf(fid, 'eval color onescol 1 1 1\n');

fclose(fid);
