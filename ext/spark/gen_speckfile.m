function gen_speckfile (filepath,filename,Xnd,patchids,texturelist)

fid = fopen(fullfile(filepath,filename),'wt');
for i=1:size(Xnd,2)
    fprintf(fid,'datavar %d a%d\n',i-1,i);
end

fprintf(fid,'datavar %d onescol\n',i);
fprintf(fid,'datavar %d txnum\n',i+1);
fprintf(fid,'datavar %d patchid\n',i+2);
fprintf(fid,'datavar %d size\n',i);
fprintf(fid,'texturevar txnum\n');

if nargin == 5
    for i=1:size(Xnd,1)
        fprintf(fid,'texture -MO %d %s.sgi\n',i,texturelist{i});
    end
elseif nargin == 4
    for i=1:size(Xnd,1)
        fprintf(fid,'texture -MO %d bigsat%d.sgi\n',i,i);
    end    
end

X3d = Xnd(:,1:3);
%szMx = ones(size(Xnd,1),1);
%txnum = [1:size(Xnd,1)]';
for i=1:size(Xnd,1)
    fprintf(fid,'%f ',X3d(i,:));
    fprintf(fid,'%f ', Xnd(i,:));
    fprintf(fid,'%d ',1);
    fprintf(fid,'%d ',i);
    fprintf(fid,'%d #\n',patchids(i));
end

fclose(fid);
